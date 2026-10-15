/// @file
/// @brief Screen implementation: laid-out pages kept, and replayed onto a
///        canvas.
///
/// A page's description is the composer's, the one a PDF carries, and it
/// uses few of the operators a PDF may: a transform, colors and an opacity,
/// rectangles, straight lines and filled regions, a clip, runs of glyphs, and
/// pictures. Replaying it is reading those back in order and telling the
/// target what each one draws. Where a PDF reader would look a glyph up in
/// the font the file embeds, this has the glyph's outline, taken from the
/// face when the page was kept.
#include "render/screen.hpp"

#include "render/composer.hpp"
#include "render/graphics/image.hpp"

#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ot.h>

#include <charconv>
#include <cmath>
#include <tuple>
#include <utility>

namespace render {
    /// A map from one space to another, as a PDF and a canvas both state it:
    /// a, b, c, d, e and f.
    using Matrix = std::array<float, 6>;

    /// @brief One map, then another: the point through @p first, then
    ///        through @p second, as a PDF's `cm` puts a new map in front of
    ///        the one in force.
    /// @complexity O(1).
    [[nodiscard]] static Matrix compose(const Matrix &first, const Matrix &second) noexcept {
        return {
            first[0] * second[0] + first[1] * second[2],
            first[0] * second[1] + first[1] * second[3],
            first[2] * second[0] + first[3] * second[2],
            first[2] * second[1] + first[3] * second[3],
            first[4] * second[0] + first[5] * second[2] + second[4],
            first[4] * second[1] + first[5] * second[3] + second[5],
        };
    }

    /// @brief Appends a coordinate of an outline, to a tenth of a unit.
    /// @param text  Outline to append to.
    /// @param value Coordinate to write.
    /// @complexity O(1).
    static void coordinate(std::string &text, const float value) {
        const long tenths = std::lround(value * 10.0f);
        const long whole = tenths / 10;
        const long part = tenths % 10;
        if (tenths < 0 && whole == 0) text += '-';
        char buffer[24];
        if (const auto [stop, failure] = std::to_chars(buffer, buffer + sizeof buffer, whole);
            failure == std::errc{}) {
            text.append(buffer, stop);
        }
        if (part != 0) {
            text += '.';
            text += static_cast<char>('0' + (part < 0 ? -part : part));
        }
    }

    /// @brief The pen HarfBuzz draws a glyph's outline with, writing it as
    ///        SVG path data into the string it is handed.
    /// @return The same pen on every call; made once, and never changed.
    [[nodiscard]] static hb_draw_funcs_t *pen() {
        static hb_draw_funcs_t *const made = [] {
            hb_draw_funcs_t *funcs = hb_draw_funcs_create();
            hb_draw_funcs_set_move_to_func(funcs, [](hb_draw_funcs_t *, void *data, hb_draw_state_t *,
                                                     const float x, const float y, void *) {
                auto &text = *static_cast<std::string *>(data);
                text += 'M';
                coordinate(text, x);
                text += ' ';
                coordinate(text, y);
            }, nullptr, nullptr);
            hb_draw_funcs_set_line_to_func(funcs, [](hb_draw_funcs_t *, void *data, hb_draw_state_t *,
                                                     const float x, const float y, void *) {
                auto &text = *static_cast<std::string *>(data);
                text += 'L';
                coordinate(text, x);
                text += ' ';
                coordinate(text, y);
            }, nullptr, nullptr);
            hb_draw_funcs_set_quadratic_to_func(funcs, [](hb_draw_funcs_t *, void *data, hb_draw_state_t *,
                                                          const float across, const float up, const float x,
                                                          const float y, void *) {
                auto &text = *static_cast<std::string *>(data);
                text += 'Q';
                for (const float value: {across, up, x}) {
                    coordinate(text, value);
                    text += ' ';
                }
                coordinate(text, y);
            }, nullptr, nullptr);
            hb_draw_funcs_set_cubic_to_func(funcs, [](hb_draw_funcs_t *, void *data, hb_draw_state_t *,
                                                      const float first, const float rise, const float second,
                                                      const float lift, const float x, const float y, void *) {
                auto &text = *static_cast<std::string *>(data);
                text += 'C';
                for (const float value: {first, rise, second, lift, x}) {
                    coordinate(text, value);
                    text += ' ';
                }
                coordinate(text, y);
            }, nullptr, nullptr);
            hb_draw_funcs_set_close_path_func(funcs, [](hb_draw_funcs_t *, void *data, hb_draw_state_t *, void *) {
                *static_cast<std::string *>(data) += 'Z';
            }, nullptr, nullptr);
            hb_draw_funcs_make_immutable(funcs);
            return funcs;
        }();
        return made;
    }

    void Screen::keep(const std::string_view content, const std::array<float, 4> &extent,
                      const layout::Document::Configuration &page) {
        Sheet &sheet = sheets.emplace_back();
        sheet.content = content;
        sheet.height = page.height;

        // What a fitted page's PDF box holds -- what it put ink on and its
        // border -- or the whole sheet, as the PDF writer has it.
        if (page.fitted && extent[0] <= extent[2]) {
            sheet.box = {
                extent[0] - page.border, extent[1] - page.border,
                extent[2] - extent[0] + 2.0f * page.border, extent[3] - extent[1] + 2.0f * page.border
            };
        } else {
            sheet.box = {0.0f, 0.0f, page.width, page.height};
        }
    }

    void Screen::take(const Composer &composer) {
        // Each face's glyphs, outlined at its own units so the outline is
        // the same at every size the pages set it in.
        faces.clear();
        faces.reserve(composer.faces.size());
        for (const Composer::Entry &entry: composer.faces) {
            Typeface &face = faces.emplace_back();
            face.widths = entry.widths;
            face.outlines.resize(entry.glyphs.size());

            const typography::Face *source = entry.font ? entry.font->face() : nullptr;
            hb_face_t *handle = source ? source->handle() : nullptr;
            if (!handle) continue;

            const unsigned int units = hb_face_get_upem(handle);
            if (units > 0) face.units = static_cast<float>(units);
            hb_font_t *font = hb_font_create(handle);
            hb_font_set_scale(font, static_cast<int>(units), static_cast<int>(units));
            hb_ot_font_set_funcs(font);
            for (std::size_t index = 0; index < entry.glyphs.size(); ++index) {
                hb_font_draw_glyph(font, entry.glyphs[index], pen(), &face.outlines[index]);
            }
            hb_font_destroy(font);
        }

        opacities = composer.opacities;

        // Each picture decoded, a JPEG the PDF would carry as it came among
        // them: a canvas is handed pixels.
        pictures.clear();
        pictures.reserve(composer.pictures.size());
        for (const graphics::Image *image: composer.pictures) {
            Picture &picture = pictures.emplace_back();
            if (!image) continue;
            picture.pixels = image->raster();
            if (picture.pixels.size() != static_cast<std::size_t>(image->width) * image->height * 3) {
                picture.pixels.clear();
                continue;
            }
            picture.width = image->width;
            picture.height = image->height;
        }

        // Each link's areas, its anchor read as the place it was drawn.
        links.clear();
        links.reserve(composer.links.size());
        for (const std::vector<Composer::Link> &drawn: composer.links) {
            std::vector<Link> &page = links.emplace_back();
            for (const Composer::Link &link: drawn) {
                Link made{.target = std::string(link.target)};
                if (made.target.empty()) {
                    if (link.anchor >= composer.places.size()) continue;
                    made.page = composer.places[link.anchor].page;
                    made.down = composer.places[link.anchor].down;
                }
                for (const std::array<float, 4> &area: link.areas) {
                    made.area = area;
                    page.push_back(made);
                }
            }
        }

        about = composer.document.metadata;
    }

    void Screen::draw(Target &target, const std::size_t page, const float scale) const {
        if (page >= sheets.size()) return;
        const Sheet &sheet = sheets[page];
        const std::string_view content = sheet.content;

        /// What paints as it is set, kept and given back by `q` and `Q`.
        struct State {
            Matrix matrix{}; ///< The map in force.
            std::array<float, 3> filling{}; ///< The fill color.
            std::array<float, 3> stroking{}; ///< The stroke color.
            float opacity{1.0f}; ///< The opacity.
            float width{1.0f}; ///< A stroke's width.
            bool dashed{false}; ///< Whether a stroke is dashed.
        };

        // The description runs up from the bottom of the whole sheet, as a
        // PDF's does; a canvas runs down from the top of what is shown, in
        // pixels. The description's first map flips it the other way.
        const auto &[left, top, wide, high] = sheet.box;
        State state{.matrix = {scale, 0.0f, 0.0f, -scale, -scale * left, scale * (sheet.height - top)}};

        // What the target was last told, so a page in one color tells it
        // once. A `Q` takes the target back to what it was at the `q`, and
        // this with it. Nothing is known at first.
        State told{.opacity = -1.0f, .width = -1.0f};
        told.filling = told.stroking = {-1.0f, -1.0f, -1.0f};
        std::vector<std::pair<State, State> > kept;

        const auto tell = [&](const bool stroked) {
            if (told.opacity != state.opacity) target.alpha(told.opacity = state.opacity);
            if (!stroked) {
                if (told.filling != state.filling) {
                    told.filling = state.filling;
                    target.fill(state.filling[0], state.filling[1], state.filling[2]);
                }
                return;
            }
            if (told.stroking != state.stroking) {
                told.stroking = state.stroking;
                target.stroke(state.stroking[0], state.stroking[1], state.stroking[2]);
            }
            if (told.width != state.width) target.width(told.width = state.width);
            if (told.dashed != state.dashed) target.dash(told.dashed = state.dashed);
        };

        // The path being built, and the clip a `W` asks for at its end.
        bool open = false;
        bool clipping = false;
        const auto begin = [&] {
            if (open) return;
            target.place(state.matrix);
            target.begin();
            open = true;
        };

        // The rectangle last added and the map it was in: the window a page
        // of another PDF is drawn through.
        std::array<float, 4> frame{};
        Matrix framed{};

        // The run of glyphs being read: its face, its size, its map onto the
        // page, and how far along it its pen has gone.
        std::size_t font = 0;
        float size = 0.0f;
        Matrix text{};
        float run = 0.0f;

        /// One operand: a number, a name without its slash, a string of
        /// hexadecimal digits, or one bracket of an array.
        struct Operand {
            enum class Kind : std::uint8_t { Number, Name, Hex, Open, Shut } kind{Kind::Number};
            float number{0.0f};
            std::string_view text{};
        };
        std::vector<Operand> operands;
        operands.reserve(16);

        const auto number = [&operands](const std::size_t back) {
            return back < operands.size() ? operands[operands.size() - 1 - back].number : 0.0f;
        };
        // The number in a resource's name, as `/F3` names face 3, so many
        // operands from the last; none when it is not a name so begun.
        const auto slot = [&operands](const std::string_view prefix, const std::size_t back = 0) -> std::size_t {
            if (back >= operands.size()) return static_cast<std::size_t>(-1);
            const Operand &operand = operands[operands.size() - 1 - back];
            if (operand.kind != Operand::Kind::Name) return static_cast<std::size_t>(-1);
            std::string_view name = operand.text;
            if (!name.starts_with(prefix)) return static_cast<std::size_t>(-1);
            name.remove_prefix(prefix.size());
            std::size_t value = 0;
            if (const auto [stop, failure] = std::from_chars(name.data(), name.data() + name.size(), value);
                failure != std::errc{} || stop != name.data() + name.size()) {
                return static_cast<std::size_t>(-1);
            }
            return value;
        };

        const auto delimiter = [](const char letter) {
            return letter == ' ' || letter == '\n' || letter == '\r' || letter == '\t' || letter == '/' ||
                   letter == '[' || letter == ']' || letter == '<' || letter == '>';
        };

        for (std::size_t at = 0; at < content.size();) {
            const char letter = content[at];
            if (letter == ' ' || letter == '\n' || letter == '\r' || letter == '\t') {
                ++at;
                continue;
            }
            if (letter == '/') {
                const std::size_t start = ++at;
                while (at < content.size() && !delimiter(content[at])) ++at;
                operands.push_back({.kind = Operand::Kind::Name, .text = content.substr(start, at - start)});
                continue;
            }
            if (letter == '<') {
                const std::size_t start = ++at;
                while (at < content.size() && content[at] != '>') ++at;
                operands.push_back({.kind = Operand::Kind::Hex, .text = content.substr(start, at - start)});
                ++at;
                continue;
            }
            if (letter == '[' || letter == ']') {
                operands.push_back({.kind = letter == '[' ? Operand::Kind::Open : Operand::Kind::Shut});
                ++at;
                continue;
            }
            if (letter == '-' || letter == '.' || (letter >= '0' && letter <= '9')) {
                // A number as the composer writes one: a sign, digits, and a
                // point with up to three more.
                const bool negative = letter == '-';
                if (negative) ++at;
                double value = 0.0;
                double place = 0.0;
                for (; at < content.size(); ++at) {
                    const char digit = content[at];
                    if (digit == '.') {
                        place = 1.0;
                    } else if (digit >= '0' && digit <= '9') {
                        if (place > 0.0) {
                            place /= 10.0;
                            value += (digit - '0') * place;
                        } else {
                            value = value * 10.0 + (digit - '0');
                        }
                    } else {
                        break;
                    }
                }
                operands.push_back({.number = static_cast<float>(negative ? -value : value)});
                continue;
            }

            // An operator: what the operands before it are for.
            const std::size_t start = at;
            while (at < content.size() && !delimiter(content[at])) ++at;
            const std::string_view word = content.substr(start, at - start);

            if (word == "cm") {
                state.matrix = compose({number(5), number(4), number(3), number(2), number(1), number(0)},
                                       state.matrix);
            } else if (word == "q") {
                kept.emplace_back(state, told);
                target.save();
            } else if (word == "Q") {
                if (!kept.empty()) {
                    std::tie(state, told) = kept.back();
                    kept.pop_back();
                    target.restore();
                }
            } else if (word == "rg") {
                state.filling = {number(2), number(1), number(0)};
            } else if (word == "RG") {
                state.stroking = {number(2), number(1), number(0)};
            } else if (word == "gs") {
                if (const std::size_t index = slot("GS"); index < opacities.size()) state.opacity = opacities[index];
            } else if (word == "w") {
                state.width = number(0);
            } else if (word == "d") {
                // [3 3] 0 d dashes; [] 0 d is solid.
                state.dashed = operands.size() >= 3 && operands[operands.size() - 3].kind != Operand::Kind::Open;
            } else if (word == "m") {
                begin();
                target.move(number(1), number(0));
            } else if (word == "l") {
                begin();
                target.line(number(1), number(0));
            } else if (word == "re") {
                begin();
                frame = {number(3), number(2), number(1), number(0)};
                framed = state.matrix;
                target.rectangle(frame[0], frame[1], frame[2], frame[3]);
            } else if (word == "h") {
                if (open) target.close();
            } else if (word == "f") {
                if (open) {
                    tell(false);
                    target.paint();
                }
                open = false;
            } else if (word == "S") {
                if (open) {
                    tell(true);
                    target.trace();
                }
                open = false;
            } else if (word == "W") {
                clipping = true;
            } else if (word == "n") {
                if (open && clipping) target.clip();
                open = clipping = false;
            } else if (word == "BT") {
                run = 0.0f;
            } else if (word == "Tf") {
                font = slot("F", 1);
                size = number(0);
            } else if (word == "Tm") {
                text = compose({number(5), number(4), number(3), number(2), number(1), number(0)}, state.matrix);
                run = 0.0f;
            } else if (word == "TJ") {
                // Each glyph through its own map: scaled from its face's
                // units to the run's size and moved along the run by the pen,
                // then through the run's. A number between two strings moves
                // the pen back by that many thousandths of the em.
                const Typeface *face = font < faces.size() ? &faces[font] : nullptr;
                const float unit = face && face->units > 0.0f ? size / face->units : 0.0f;
                bool colored = false;
                for (const Operand &item: operands) {
                    if (item.kind == Operand::Kind::Number) {
                        run -= item.number / 1000.0f * size;
                        continue;
                    }
                    if (item.kind != Operand::Kind::Hex || !face) continue;
                    for (std::size_t digit = 0; digit + 4 <= item.text.size(); digit += 4) {
                        std::uint32_t code = 0;
                        std::from_chars(item.text.data() + digit, item.text.data() + digit + 4, code, 16);
                        if (code == 0 || code > face->outlines.size()) continue;
                        if (!face->outlines[code - 1].empty()) {
                            if (!colored) {
                                tell(false);
                                colored = true;
                            }
                            target.place({
                                unit * text[0], unit * text[1], unit * text[2], unit * text[3],
                                run * text[0] + text[4], run * text[1] + text[5]
                            });
                            target.glyph(font, code, face->outlines[code - 1]);
                        }
                        if (code <= face->widths.size()) run += face->widths[code - 1] / 1000.0f * size;
                    }
                }
            } else if (word == "Do") {
                if (const std::size_t index = slot("Im"); index < pictures.size()) {
                    // The picture's unit square runs up from its bottom row;
                    // the target draws its top row at 0.
                    if (!pictures[index].pixels.empty()) {
                        tell(false);
                        target.place(compose({1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f}, state.matrix));
                        target.picture(index, pictures[index]);
                    }
                } else if (slot("Fm") != static_cast<std::size_t>(-1)) {
                    // A page of another PDF fills the window it was clipped to.
                    target.place(framed);
                    target.form(frame[0], frame[1], frame[2], frame[3]);
                }
            }
            operands.clear();
        }
    }
}

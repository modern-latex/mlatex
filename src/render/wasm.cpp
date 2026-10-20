/// @file
/// @brief The engine bound for JavaScript: see render/wasm.hpp.
///
/// Compiled into the `wasm` target alone, under Emscripten. Embind does the
/// binding: latex::Session's operations are handed to JavaScript under their
/// own names, each through a small adapter where JavaScript's types differ
/// from C++'s -- embind has no string view, reads a Uint8Array or a string
/// into a std::string, and would read a PDF's bytes back as UTF-8 text if
/// they went out as one.
#include "render/wasm.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#if defined(__EMSCRIPTEN__)
#include <emscripten/bind.h>
#endif

namespace render {
    Wasm::Wasm() : Session(std::string(root)) {
    }

#if defined(__EMSCRIPTEN__)

    emscripten::val Wasm::bytes() const {
        const std::string &made = pdf;
        const auto *data = reinterpret_cast<const unsigned char *>(made.data());

        // A view onto the module's own memory would be invalidated by the
        // next document, or by the memory growing; slice() copies it into a
        // Uint8Array of its own.
        return emscripten::val(emscripten::typed_memory_view(made.size(), data)).call<emscripten::val>("slice");
    }

    void Wasm::attach(const std::string &name, const std::size_t arity, emscripten::val function) {
        define({
            .name = name,
            .arity = arity,
            .handler = [function = std::move(function)](const std::span<const std::string> arguments) {
                emscripten::val list = emscripten::val::array();
                for (const std::string &argument: arguments) list.call<void>("push", argument);

                const emscripten::val answer = function.call<emscripten::val>("apply", emscripten::val::null(), list);
                if (answer.isUndefined() || answer.isNull()) return std::string{};
                return emscripten::val::global("String")(answer).as<std::string>();
            },
        });
    }

    /// @brief A canvas's 2D context -- a page's or a worker's offscreen one --
    ///        as a Screen draws on it.
    ///
    /// Each operation is the context's own of the same meaning. A glyph's
    /// outline becomes a Path2D the first time the page draws it and is
    /// filled from there after, and a picture becomes a canvas of its own
    /// once, drawn into the unit square as often as the page asks.
    class Context final : public Screen::Target {
    public:
        explicit Context(emscripten::val context) : context(std::move(context)) {
        }

        void save() override { context.call<void>("save"); }

        void restore() override { context.call<void>("restore"); }

        void place(const std::array<float, 6> &matrix) override {
            context.call<void>("setTransform", matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5]);
        }

        void fill(const float red, const float green, const float blue) override {
            context.set("fillStyle", color(red, green, blue));
        }

        void stroke(const float red, const float green, const float blue) override {
            context.set("strokeStyle", color(red, green, blue));
        }

        void alpha(const float value) override { context.set("globalAlpha", value); }

        void width(const float value) override { context.set("lineWidth", value); }

        void dash(const bool dashed) override {
            emscripten::val pattern = emscripten::val::array();
            if (dashed) {
                pattern.call<void>("push", 3);
                pattern.call<void>("push", 3);
            }
            context.call<void>("setLineDash", pattern);
        }

        void begin() override { context.call<void>("beginPath"); }

        void move(const float x, const float y) override { context.call<void>("moveTo", x, y); }

        void line(const float x, const float y) override { context.call<void>("lineTo", x, y); }

        void rectangle(const float x, const float y, const float wide, const float high) override {
            context.call<void>("rect", x, y, wide, high);
        }

        void close() override { context.call<void>("closePath"); }

        void paint() override { context.call<void>("fill"); }

        void trace() override { context.call<void>("stroke"); }

        void clip() override { context.call<void>("clip"); }

        void glyph(const std::size_t face, const std::uint32_t code, const std::string_view outline) override {
            const std::uint64_t key = static_cast<std::uint64_t>(face) << 32 | code;
            auto found = outlines.find(key);
            if (found == outlines.end()) {
                found = outlines.emplace(key, emscripten::val::global("Path2D").new_(std::string(outline))).first;
            }
            context.call<void>("fill", found->second);
        }

        void picture(const std::size_t slot, const Screen::Picture &picture) override {
            auto found = images.find(slot);
            if (found == images.end()) {
                // Where there is no canvas to draw it into -- Node -- it is left out.
                const emscripten::val made = emscripten::val::global("OffscreenCanvas");
                if (made.isUndefined()) return;

                // Its pixels with an alpha channel, opaque, as ImageData has them.
                const std::size_t count = static_cast<std::size_t>(picture.width) * picture.height;
                std::vector<std::uint8_t> pixels(count * 4, 255);
                for (std::size_t index = 0; index < count; ++index) {
                    pixels[index * 4] = picture.pixels[index * 3];
                    pixels[index * 4 + 1] = picture.pixels[index * 3 + 1];
                    pixels[index * 4 + 2] = picture.pixels[index * 3 + 2];
                }
                const emscripten::val data = emscripten::val::global("ImageData").new_(
                    emscripten::val::global("Uint8ClampedArray").new_(
                        emscripten::val(emscripten::typed_memory_view(pixels.size(), pixels.data()))),
                    picture.width, picture.height);
                emscripten::val canvas = made.new_(picture.width, picture.height);
                canvas.call<emscripten::val>("getContext", std::string("2d")).call<void>("putImageData", data, 0, 0);
                found = images.emplace(slot, std::move(canvas)).first;
            }
            context.call<void>("drawImage", found->second, 0, 0, 1, 1);
        }

        void form(const float x, const float y, const float wide, const float high) override {
            // A page of another PDF, which only a PDF reader draws: its place,
            // shaded and framed.
            context.call<void>("save");
            context.set("globalAlpha", 1);
            context.set("fillStyle", std::string("rgb(238, 238, 238)"));
            context.call<void>("fillRect", x, y, wide, high);
            context.set("strokeStyle", std::string("rgb(180, 180, 180)"));
            context.set("lineWidth", 0.5f);
            context.call<void>("strokeRect", x, y, wide, high);
            context.call<void>("restore");
        }

    private:
        /// @brief A color as CSS writes one.
        [[nodiscard]] static std::string color(const float red, const float green, const float blue) {
            const auto channel = [](const float value) {
                const float clamped = value <= 0.0f ? 0.0f : value >= 1.0f ? 1.0f : value;
                return std::to_string(static_cast<int>(clamped * 255.0f + 0.5f));
            };
            return "rgb(" + channel(red) + ", " + channel(green) + ", " + channel(blue) + ")";
        }

        emscripten::val context; ///< The context drawn on.
        std::unordered_map<std::uint64_t, emscripten::val> outlines{}; ///< Each glyph's Path2D, by face and code.
        std::unordered_map<std::size_t, emscripten::val> images{}; ///< Each picture's canvas, by slot.
    };

    /// @brief Hands latex::Session to JavaScript under its own names.
    EMSCRIPTEN_BINDINGS (latex) {
        emscripten::class_<Wasm>("Session")
                .constructor<>()
                .function("set", emscripten::optional_override([](Wasm &self, const std::string &name,
                                                                  const std::string &value) {
                    self.set(name, value);
                }))
                .function("unset", emscripten::optional_override(
                              [](Wasm &self, const std::string &name) { self.unset(name); }))
                .function("define", &Wasm::attach)
                .function("forget", emscripten::optional_override(
                              [](Wasm &self, const std::string &name) { self.forget(name); }))
                .function("provide", emscripten::optional_override([](Wasm &self, const std::string &name,
                                                                      std::string bytes) {
                    self.provide(name, std::move(bytes));
                }))
                .function("withdraw", emscripten::optional_override(
                              [](Wasm &self, const std::string &name) { self.withdraw(name); }))
                .function("typeset", emscripten::optional_override(
                              [](Wasm &self, const std::string &document) { return self.typeset(document); }))
                .function("snippet", emscripten::optional_override(
                              [](Wasm &self, const std::string &text) { return self.snippet(text); }))
                .function("pdf", &Wasm::bytes)
                .function("error", emscripten::optional_override(
                              [](const Wasm &self) { return self.error; }))
                .function("screen", emscripten::optional_override(
                              [](const Wasm &self) { return self.screen; }));

        // The pages of the last PDF made, to draw on a canvas: a copy of the
        // session's, which the next document leaves as it is, so the pages
        // before can be drawn beside the pages after.
        emscripten::class_<Screen>("Screen")
                .function("count", emscripten::optional_override(
                              [](const Screen &self) { return self.sheets.size(); }))
                .function("width", emscripten::optional_override([](const Screen &self, const std::size_t page) {
                    return page < self.sheets.size() ? self.sheets[page].box[2] : 0.0f;
                }))
                .function("height", emscripten::optional_override([](const Screen &self, const std::size_t page) {
                    return page < self.sheets.size() ? self.sheets[page].box[3] : 0.0f;
                }))
                .function("draw", emscripten::optional_override(
                              [](const Screen &self, emscripten::val context, const std::size_t page,
                                 const float scale) {
                                  Context target(std::move(context));
                                  self.draw(target, page, scale);
                              }))
                .function("links", emscripten::optional_override([](const Screen &self, const std::size_t page) {
                    emscripten::val list = emscripten::val::array();
                    if (page >= self.links.size() || page >= self.sheets.size()) return list;
                    // Each area from the top left of what is shown, as the page's own size is.
                    const std::array<float, 4> &box = self.sheets[page].box;
                    for (const Screen::Link &link: self.links[page]) {
                        emscripten::val made = emscripten::val::object();
                        made.set("left", link.area[0] - box[0]);
                        made.set("top", link.area[1] - box[1]);
                        made.set("right", link.area[2] - box[0]);
                        made.set("bottom", link.area[3] - box[1]);
                        if (!link.target.empty()) {
                            made.set("target", link.target);
                        } else {
                            made.set("page", link.page);
                            made.set("down", link.page < self.sheets.size()
                                                 ? link.down - self.sheets[link.page].box[1]
                                                 : link.down);
                        }
                        list.call<void>("push", made);
                    }
                    return list;
                }))
                .function("spots", emscripten::optional_override([](const Screen &self, const std::size_t page) {
                    emscripten::val list = emscripten::val::array();
                    if (page >= self.spots.size() || page >= self.sheets.size()) return list;
                    // Each area from the top left of what is shown, as a link's
                    // is, with the line and the file it was written in.
                    const std::array<float, 4> &box = self.sheets[page].box;
                    for (const Composer::Spot &spot: self.spots[page]) {
                        emscripten::val made = emscripten::val::object();
                        made.set("left", spot.area[0] - box[0]);
                        made.set("top", spot.area[1] - box[1]);
                        made.set("right", spot.area[2] - box[0]);
                        made.set("bottom", spot.area[3] - box[1]);
                        made.set("line", spot.origin.line);
                        made.set("file", spot.origin.file < self.files.size()
                                             ? self.files[spot.origin.file]
                                             : std::string{});
                        list.call<void>("push", made);
                    }
                    return list;
                }))
                .function("about", emscripten::optional_override([](const Screen &self) {
                    emscripten::val made = emscripten::val::object();
                    made.set("title", self.about.title);
                    made.set("author", self.about.author);
                    made.set("subject", self.about.subject);
                    made.set("keywords", self.about.keywords);
                    return made;
                }));
    }

#endif
}

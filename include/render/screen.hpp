#pragma once

#include "render/composer.hpp"
#include "render/layout/document.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace render {
    /// @brief Laid-out pages kept to be drawn on a screen: a canvas, with
    ///        nothing between the engine and the pixels.
    ///
    /// The PDF writer and this are handed the same thing -- each page's
    /// description, as the composer writes it, and the faces, opacities and
    /// pictures it names -- and do two things with it. The writer wraps it in
    /// a file for a reader to open. This keeps it, with the outline of every
    /// glyph the pages drew, and replays it onto a #Target whenever a page is
    /// wanted at a size: a canvas in a browser, which draws it as vectors, as
    /// sharp at any zoom as the file would be, without a PDF reader in
    /// between.
    ///
    /// @par Use
    /// @code
    /// render::Screen screen;
    /// const std::string pdf = render::Pdf::render(composer, pages, &screen);
    /// screen.draw(target, 0, 2.0f); // the first page, two pixels to the point
    /// @endcode
    class Screen {
    public:
        /// @brief One page: its description, and the part of it a screen shows.
        struct Sheet {
            std::string content{}; ///< Its description, as the composer wrote it.
            float height{0.0f}; ///< The whole sheet's height, which the description is flipped by.

            /// What is shown: left, top, width and height from the sheet's
            /// top left. The whole sheet, or what a fitted page holds and
            /// its border.
            std::array<float, 4> box{};
        };

        /// @brief One face the pages drew from, cut to the glyphs they drew.
        struct Typeface {
            float units{1000.0f}; ///< Units to the em, which its outlines are in.
            std::vector<std::string> outlines{}; ///< Each glyph's outline as SVG path data, by its number less one.
            std::vector<float> widths{}; ///< Each glyph's width in thousandths of the em, as the PDF has it.
        };

        /// @brief One picture the pages drew, decoded.
        struct Picture {
            int width{0}; ///< Pixels across.
            int height{0}; ///< Pixels down.
            std::vector<std::uint8_t> pixels{}; ///< Three bytes a pixel, top row first.
        };

        /// @brief A link on a page: an area, and where it goes.
        struct Link {
            std::array<float, 4> area{}; ///< Left, top, right and bottom, from the sheet's top left.
            std::string target{}; ///< The address it goes to; empty when it goes to a place.
            std::size_t page{0}; ///< The page it goes to, from 0, when it has no address.
            float down{0.0f}; ///< How far down that page, in points.
        };

        /// @brief Where a page is drawn: the operations a canvas's 2D context
        ///        offers, in the order the page asks for them.
        ///
        /// Every coordinate is in pixels once #place has set the transform
        /// it is read through, as a canvas reads them.
        class Target {
        public:
            virtual ~Target() = default;

            /// @brief Keeps the clip, to be given back by #restore.
            virtual void save() = 0;

            /// @brief Gives back the clip kept by the last #save.
            virtual void restore() = 0;

            /// @brief Sets the transform what follows is read through, from
            ///        scratch: a point (x, y) lands at (a x + c y + e, b x + d y + f).
            /// @param matrix a, b, c, d, e and f.
            virtual void place(const std::array<float, 6> &matrix) = 0;

            /// @brief Sets the color a fill paints in.
            virtual void fill(float red, float green, float blue) = 0;

            /// @brief Sets the color a stroke paints in.
            virtual void stroke(float red, float green, float blue) = 0;

            /// @brief Sets how opaque everything painted from here is, 0 to 1.
            virtual void alpha(float value) = 0;

            /// @brief Sets a stroke's width.
            virtual void width(float value) = 0;

            /// @brief Sets a stroke dashed, three on and three off, or solid.
            virtual void dash(bool dashed) = 0;

            /// @brief Starts a new path.
            virtual void begin() = 0;

            /// @brief Starts a piece of the path at a point.
            virtual void move(float x, float y) = 0;

            /// @brief Runs the path straight on to a point.
            virtual void line(float x, float y) = 0;

            /// @brief Adds a rectangle to the path, as a piece of its own.
            virtual void rectangle(float x, float y, float width, float height) = 0;

            /// @brief Closes the piece of the path being drawn.
            virtual void close() = 0;

            /// @brief Fills the path, nonzero.
            virtual void paint() = 0;

            /// @brief Strokes the path.
            virtual void trace() = 0;

            /// @brief Clips everything after to the path, until #restore.
            virtual void clip() = 0;

            /// @brief Fills a glyph's outline, in its face's own units, y up.
            /// @param face    Which face, as Screen::faces numbers them.
            /// @param code    Which glyph of it, as the page numbers them, from 1.
            /// @param outline Its outline as SVG path data; the same for the
            ///                same face and code, so it may be kept by them.
            virtual void glyph(std::size_t face, std::uint32_t code, std::string_view outline) = 0;

            /// @brief Draws a picture over the unit square, its top row at 0.
            /// @param slot    Which picture, as Screen::pictures numbers them;
            ///                the same picture for the same slot.
            /// @param picture Its pixels.
            virtual void picture(std::size_t slot, const Picture &picture) = 0;

            /// @brief Marks where a page of another PDF stands, which only a
            ///        PDF reader draws.
            virtual void form(float x, float y, float width, float height) = 0;
        };

        /// @brief Keeps one page's description as the composer just drew it.
        /// @param content Its description.
        /// @param extent  What it put ink on, as Composer::extent has it.
        /// @param page    The document's page.
        void keep(std::string_view content, const std::array<float, 4> &extent,
                  const layout::Document::Configuration &page);

        /// @brief Takes what the pages kept name from the composer that drew
        ///        them: the outline of every glyph, the opacities, the pictures,
        ///        the links and what the document says of itself.
        /// @param composer The composer, once every page has been drawn.
        void take(const Composer &composer);

        /// @brief Draws one page onto a target.
        /// @param target Where to draw.
        /// @param page   Which page, from 0; nothing is drawn for one past the last.
        /// @param scale  Pixels to the point.
        /// @complexity O(n) in the page's description.
        void draw(Target &target, std::size_t page, float scale) const;

        std::vector<Sheet> sheets{}; ///< Every page, in order.
        std::vector<Typeface> faces{}; ///< Every face, as a page names it: entry `n` is `/F<n>`.
        std::vector<float> opacities{}; ///< Every opacity, as a page names it: entry `n` is `/GS<n>`.
        std::vector<Picture> pictures{}; ///< Every picture, as a page names it: entry `n` is `/Im<n>`.
        std::vector<std::vector<Link> > links{}; ///< Every link, by page.
        /// Where each line of the source was drawn, by page: what an editor
        /// jumps by, from a click on a page to its line and back. Areas are
        /// measured as the sheet is, from its top left, not #Sheet::box's.
        std::vector<std::vector<Composer::Spot> > spots{};
        /// The name of each file a spot's origin numbers, as
        /// syntax::Mouth::files gives them: the document's own first.
        std::vector<std::string> files{};
        /// Every character the pages lack because no face drew it, once each:
        /// what a page in a browser fetches a face for, then sets them again.
        std::vector<std::uint32_t> missing{};
        layout::Document::Metadata about{}; ///< What the document says of itself.
    };
}

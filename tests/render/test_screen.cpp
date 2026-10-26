#include "latex.hpp"

#include <cassert>
#include <cstdio>
#include <filesystem>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

// The screen: each page kept as the PDF has it, its every glyph's outline
// with it, and replayed onto a target -- a canvas -- glyph by glyph, rule by
// rule, picture by picture, the size the target asks for, and what the
// pages link to.

/// One document as the engine set it, and its pages kept for a screen.
struct Result {
    bool clean{false};
    std::string errors{};
    std::string pdf{};
    render::Screen screen{};
};

/// Typesets a whole document, as written, with what a program hands in.
static Result typeset(const std::string_view document, const latex::Host &host = {}) {
    static const std::filesystem::path assets = latex::locate(__FILE__);
    Result result;
    std::ostringstream errors;
    result.clean = latex::typeset(assets, document, result.pdf, host, errors, nullptr, &result.screen);
    result.errors = errors.str();
    if (!result.clean) std::fprintf(stderr, "%s", result.errors.c_str());
    return result;
}

/// A target that remembers what it was told, in order, as words.
class Recorder final : public render::Screen::Target {
public:
    std::vector<std::string> said{}; ///< Each operation, named.
    std::vector<std::array<float, 6> > maps{}; ///< Each map placed.
    std::vector<std::string> outlines{}; ///< Each glyph's outline, as it was filled.
    std::vector<std::array<float, 3> > fills{}; ///< Each fill color set.
    std::size_t pictures{0}; ///< How many pictures were drawn.

    void save() override { said.emplace_back("save"); }
    void restore() override { said.emplace_back("restore"); }
    void place(const std::array<float, 6> &matrix) override { maps.push_back(matrix); }
    void fill(const float red, const float green, const float blue) override { fills.push_back({red, green, blue}); }
    void stroke(float, float, float) override { said.emplace_back("stroke"); }
    void alpha(float) override { said.emplace_back("alpha"); }
    void width(float) override { said.emplace_back("width"); }
    void dash(const bool dashed) override { said.emplace_back(dashed ? "dashed" : "solid"); }
    void begin() override { said.emplace_back("begin"); }
    void move(float, float) override { said.emplace_back("move"); }
    void line(float, float) override { said.emplace_back("line"); }
    void rectangle(float, float, float, float) override { said.emplace_back("rectangle"); }
    void close() override { said.emplace_back("close"); }
    void paint() override { said.emplace_back("paint"); }
    void trace() override { said.emplace_back("trace"); }
    void clip() override { said.emplace_back("clip"); }

    void glyph(std::size_t, std::uint32_t, const std::string_view outline) override {
        said.emplace_back("glyph");
        outlines.emplace_back(outline);
    }

    void picture(std::size_t, const render::Screen::Picture &picture) override {
        if (picture.width > 0 && picture.pixels.size() == static_cast<std::size_t>(picture.width) * picture.height * 3) {
            ++pictures;
        }
    }

    void form(float, float, float, float) override { said.emplace_back("form"); }

    /// How many times it was told something.
    [[nodiscard]] std::size_t count(const std::string_view word) const {
        std::size_t found = 0;
        for (const std::string &item: said) found += item == word;
        return found;
    }
};

/// A one-pixel PNG, for a picture handed in from memory.
static std::string dot() {
    static constexpr unsigned char bytes[] = {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
        0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x08, 0x06, 0x00, 0x00, 0x00, 0x1F, 0x15, 0xC4,
        0x89, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x44, 0x41, 0x54, 0x78, 0xDA, 0x63, 0x64, 0x60, 0xF8, 0x5F,
        0x0F, 0x00, 0x02, 0x87, 0x01, 0x80, 0xEB, 0x47, 0xBA, 0x92, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
        0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82,
    };
    return std::string(reinterpret_cast<const char *>(bytes), sizeof bytes);
}

int main() {
    {
        const Result result = typeset("\\documentclass{article}\\begin{document}Hello.\\end{document}");
        assert((result.clean && result.screen.sheets.size() == 1) && "a page kept for each page of the PDF");
        const std::array<float, 4> &box = result.screen.sheets[0].box;
        assert((box[0] == 0.0f && box[1] == 0.0f && box[2] == 612.0f && box[3] == 792.0f) &&
               "the whole sheet shown, as large as the PDF's box");

        Recorder recorder;
        result.screen.draw(recorder, 0, 1.0f);
        // H, e, l, l, o, the full stop, and the page's number.
        assert((recorder.count("glyph") == 7) && "each glyph of the page filled, and nothing more");
        for (const std::string &outline: recorder.outlines) {
            assert((outline.starts_with('M') && outline.ends_with('Z')) && "each from its outline, closed");
        }
        assert((recorder.fills.size() == 1 && recorder.fills[0] == std::array{0.0f, 0.0f, 0.0f}) &&
               "a page in one color tells the target the color once");
    }
    {
        const Result result = typeset("\\documentclass{article}\\begin{document}Hello.\\end{document}");
        Recorder once;
        Recorder twice;
        result.screen.draw(once, 0, 1.0f);
        result.screen.draw(twice, 0, 2.0f);
        assert((once.maps.size() == twice.maps.size() && !once.maps.empty()) && "the same marks at any size");
        for (std::size_t index = 0; index < once.maps.size(); ++index) {
            for (std::size_t entry = 0; entry < 6; ++entry) {
                const float doubled = once.maps[index][entry] * 2.0f;
                const float difference = twice.maps[index][entry] - doubled;
                assert((difference < 0.01f && difference > -0.01f) && "each twice as far and as large at twice the scale");
            }
        }
        Recorder none;
        result.screen.draw(none, 1, 1.0f);
        assert((none.said.empty() && none.maps.empty()) && "a page past the last draws nothing");
    }
    {
        const Result result = typeset("\\documentclass{article}\\usepackage{xcolor}\\begin{document}"
            "\\textcolor{red}{Red} \\rule{2cm}{1pt}\\end{document}");
        Recorder recorder;
        result.screen.draw(recorder, 0, 1.0f);
        bool red = false;
        for (const auto &color: recorder.fills) red = red || color == std::array{1.0f, 0.0f, 0.0f};
        assert((red && recorder.count("rectangle") >= 1 && recorder.count("paint") >= 1) &&
               "a colored word in its color, and a rule filled as a rectangle");
    }
    {
        const Result result = typeset("\\documentclass{standalone}\\begin{document}$x^2$\\end{document}");
        const std::array<float, 4> &box = result.screen.sheets[0].box;
        assert((result.clean && box[2] > 0.0f && box[2] < 50.0f && box[3] > 0.0f && box[3] < 50.0f) &&
               "a fitted page shown as what it holds, as the PDF's box is");
    }
    {
        latex::Host host;
        host.files["dot.png"] = dot();
        const Result result = typeset("\\documentclass{article}\\usepackage{graphicx}\\begin{document}"
                                      "\\includegraphics{dot.png}\\end{document}",
                                      host);
        Recorder recorder;
        result.screen.draw(recorder, 0, 1.0f);
        assert((result.screen.pictures.size() == 1 && recorder.pictures == 1) && "a picture drawn from its pixels");
    }
    {
        const Result result = typeset("\\documentclass{article}\\usepackage{tikz}\\begin{document}"
            "\\tikz \\draw[dashed] (0,0) -- (1,0);\\end{document}");
        Recorder recorder;
        result.screen.draw(recorder, 0, 1.0f);
        assert((recorder.count("dashed") == 1 && recorder.count("trace") >= 1) && "a dashed line stroked dashed");
    }
    {
        const Result result = typeset("\\documentclass{article}\\usepackage{hyperref}"
            "\\hypersetup{pdftitle={Linked}}\\begin{document}\\section{One}\\label{one}"
            "\\href{https://example.com}{A site}, Section~\\ref{one}.\\end{document}");
        const auto &links = result.screen.links;
        assert((links.size() == 1 && links[0].size() == 2) && "each link on its page");
        assert((links[0][0].target == "https://example.com" && links[0][1].target.empty() &&
                links[0][1].page == 0 && links[0][1].down > 0.0f) &&
               "one to its address, one to the place its anchor was drawn");
        assert((result.screen.about.title == "Linked") && "and what the document says of itself");
    }
    {
        latex::Session session(latex::locate(__FILE__));
        assert((session.snippet("$\\int_0^1 x\\,dx$") && session.screen.sheets.size() == 1) &&
               "a session keeps its last PDF's pages for a screen");
        const std::size_t glyphs = session.screen.faces.empty() ? 0 : session.screen.faces[0].outlines.size();
        assert((glyphs > 0) && "with the outlines of what they drew");
        assert((session.typeset("\\documentclass{article}\\begin{document}One.\\newpage Two.\\end{document}") &&
                session.screen.sheets.size() == 2) && "and the next document's in their place");
    }

    return 0;
}

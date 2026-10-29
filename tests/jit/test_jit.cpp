#include "jit/jit.hpp"
#include "latex.hpp"

#include <cassert>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// The jit target's session: today the ahead-of-time run behind a session
// kept alive, so a document set through it reads as latex::typeset sets it,
// run after run. Each piece the JIT gains adds an edit here, followed by
// the same comparison -- the test src/jit/implementation.md describes.

int main() {
    const std::filesystem::path assets = latex::locate(__FILE__);
    const std::filesystem::path folder = std::filesystem::temp_directory_path() / "mlatex-test-jit";
    std::filesystem::create_directories(folder);
    const std::filesystem::path source = folder / "paper.mtex";
    const std::filesystem::path destination = folder / "paper.pdf";

    const std::string text =
            R"(\documentclass{article}\begin{document}\section{One}Hello, world.\section{Two}Again.\end{document})";
    {
        std::ofstream file(source, std::ios::binary);
        file << text;
    }

    // What the ahead-of-time target makes of the same text.
    std::string pdf;
    std::vector<std::string> expected;
    std::ostringstream ahead;
    assert(latex::typeset(assets, text, pdf, latex::Host{}, ahead, &expected) && "the document sets ahead of time");

    jit::Jit jit(assets);
    {
        std::ostringstream errors;
        std::vector<std::string> texts;
        std::filesystem::remove(destination);
        const bool ok = jit.typeset(source, destination, nullptr, errors, &texts);
        if (!ok) std::fprintf(stderr, "%s", errors.str().c_str());
        assert(ok && "a clean document sets cleanly through the Jit");
        assert(std::filesystem::exists(destination) && "and its PDF is written where it was asked for");
        assert(texts == jit.pages && "the pages handed back are the session's own");
        assert(texts == expected && "the Jit sets the pages the ahead-of-time target sets");
    }
    {
        // The same session again, as --watch runs it after a save.
        std::ostringstream errors;
        std::vector<std::string> texts;
        assert(jit.typeset(source, destination, nullptr, errors, &texts) && texts == expected &&
               "a second run of one session sets the same pages");
    }
    {
        // The session's own in-memory typeset is still there beside the
        // Jit's, and is the ahead-of-time one.
        assert(jit.typeset(text) && jit.pages == expected && "the in-memory typeset is latex::Session's");
    }

    // The steps to add, one per piece, each an edit to `paper.mtex` and the
    // comparison above after it:
    //
    //     type inside a paragraph               -- pieces 2, 5 and 8
    //     add a \tableofcontents, then a section -- piece 3: one pass, then two
    //     add a \label and a \pageref to it     -- pieces 3 and 8
    //     take the \label away                  -- piece 8's journal: the \pageref is ?? again
    //     add \usepackage{amsmath}              -- piece 7: the snapshot is not used
    //     edit a file the document \inputs      -- pieces 1 and 7
    //     cite a \bibitem written further on    -- piece 8's journal

    std::filesystem::remove_all(folder);
    return 0;
}

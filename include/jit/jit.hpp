#pragma once

#include "latex.hpp"

#include <filesystem>
#include <ostream>
#include <string>
#include <vector>

/// @brief Just in time: the engine kept warm between runs, so a document
///        changed and set again costs only what changed.
///
/// Everything here is a child of the ahead-of-time pipeline in latex.hpp and
/// never a second engine: whatever a run cannot shorten, it does the way
/// latex::compose() does it. src/jit/implementation.md is the overview --
/// what a run costs today, the order to build the pieces in, and how the
/// JIT reaches WebAssembly. Each class here says what to write in it.
namespace jit {
    /// @brief A latex::Session kept alive between documents, which sets a
    ///        document again as its files change: the `jit` target.
    ///
    /// Today it runs the ahead-of-time pipeline on every call, so
    /// `mlatex --target=jit` makes the same PDF as `--target=aot`, and
    /// `--watch` keeps one Jit alive from one save to the next. What makes it
    /// faster is added here a piece at a time, each one a member this class
    /// keeps between runs. The pieces are numbered in the order to build
    /// them, which is the order of what each saves on build/main.mtex (eleven
    /// pages, 43 ms a launch today).
    ///
    /// @par Use
    /// @code
    /// jit::Jit jit(latex::locate(program));
    /// jit.host.directories.emplace_back("styles");
    ///
    /// std::ostringstream errors;
    /// jit.typeset("paper.mtex", "paper.pdf", nullptr, errors); // the first run: as aot
    /// // ... paper.mtex is saved ...
    /// jit.typeset("paper.mtex", "paper.pdf", nullptr, errors); // warm, once the pieces below exist
    /// @endcode
    ///
    /// @par What to write
    /// 1. **Notice a save at once** -- jit::Watcher, used by `--watch` in
    ///    src/main.cpp. Saves about 125 ms of waiting per save.
    /// 2. **Keep the engine warm.** Move what `run()` in src/latex.cpp
    ///    builds for every document, but which no document changes, into
    ///    members here: the font Collection and Registry, the Shaper, the
    ///    hyphenation patterns, and an arena they live in. Saves 1 to 2 ms a
    ///    run, and every piece after this one stands on it. See
    ///    src/jit/jit.cpp.
    /// 3. **Set the document once, not twice.** Keep the page each anchor
    ///    landed on last time (`folios`), and run again only when this run
    ///    moved one. Saves about 15 ms -- half of a run. See src/jit/jit.cpp.
    /// 4. **Cut each face once** -- jit::Cache, beside the PDF writer.
    /// 5. **Shape each word once** -- jit::Cache, beside the Shaper.
    /// 6. **Work out a plot's formula in machine code** -- jit::Formula,
    ///    with asmjit, for the plots that evaluate one thousands of times.
    /// 7. **Read the preamble once** -- jit::Snapshot, taken when
    ///    `\\begin{document}` opens and put back while the preamble and
    ///    every file it read are unchanged. Saves about 3 ms.
    /// 8. **Set only what changed** -- jit::Snapshot again, as checkpoints
    ///    through the body: a run starts from the last checkpoint before the
    ///    first byte that changed.
    /// 9. **Start warm after a restart** -- jit::Format, the whole state on
    ///    disk beside the document, as TeX's `.fmt` keeps a preamble.
    ///
    /// Each piece should leave the pages exactly as the ahead-of-time target
    /// sets them; a test that edits a document step by step and compares
    /// this class's `pages` with latex::typeset()'s after every edit is what
    /// proves it (see tests/jit/test_jit.cpp).
    ///
    /// @par Names
    /// The house rules hold here too: one real word for every name, the
    /// verbs get, set, post, compose and dispose, a public field rather than
    /// an accessor, no anonymous namespaces, and a function's code written
    /// in the one place that calls it.
    ///
    /// @par WebAssembly
    /// This file compiles into the WebAssembly module as it is: src/jit/ is
    /// part of the engine library there too. To hand the JIT to JavaScript,
    /// make render::Wasm a child of this class instead of latex::Session --
    /// `class Wasm : public jit::Jit` in render/wasm.hpp -- and give this
    /// class a warm `typeset(std::string_view)` of its own: every page that
    /// already uses `new engine.Session()` is then warm with no change to
    /// latex.js or latex.d.ts. The steps are in src/jit/implementation.md.
    class Jit : public latex::Session {
    public:
        using latex::Session::Session;

        /// The in-memory latex::Session::typeset(), which runs ahead of time:
        /// a call through a `latex::Session&` reaches that one whatever this
        /// class adds, since nothing in Session is virtual. Give this class
        /// its own `typeset(std::string_view)` when piece 2 exists, and the
        /// bindings' sessions are warm too.
        using latex::Session::typeset;

        /// @brief Sets a document from disk into a PDF on disk -- what the
        ///        command line's `jit` target calls, once per run.
        ///
        /// For now this is latex::compose() with this session's #host: the
        /// ahead-of-time run, whole. The pieces listed above shorten it from
        /// the inside, and its signature stays as it is.
        ///
        /// @param source      The document to read.
        /// @param destination Where to write the PDF; empty for a draft, which writes none.
        /// @param report      Where the statistics and timings go, or null for nowhere.
        /// @param errors      Where every error goes, one per line.
        /// @param texts       Receives each page's text as well as #pages does, or null.
        /// @return True when the document compiled with nothing left broken.
        /// @complexity Today a whole run: O(n) in the document, twice when it
        ///             asks for a page number.
        bool typeset(const std::filesystem::path &source, const std::filesystem::path &destination,
                     std::ostream *report, std::ostream &errors, std::vector<std::string> *texts = nullptr);

        // What this class keeps between runs goes here, one member per piece,
        // in the order above. Each is shown with its reason in src/jit/jit.cpp;
        // as a sketch:
        //
        //     memory::Arena arena{16 * 1024 * 1024};          // 2: what outlives a document
        //     render::typography::Collection collection{arena}; // 2: the font tree, indexed once
        //     render::typography::Registry registry{arena, collection};
        //     render::typography::Shaper shaper{arena, &registry};
        //     render::typography::Hyphenator hyphenator{};     // 2: English, built once
        //     std::vector<std::string> folios{};               // 3: the page each anchor was on
        //     Cache cache{};                                   // 4 and 5
        //     std::string text{};                              // 8: what was set last
        //     std::vector<Snapshot> checkpoints{};             // 7 and 8
        //
        // Declared in that order, since each is built from the ones before it.
    };
}

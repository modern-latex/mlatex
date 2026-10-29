/// @file
/// @brief The `jit` target: see jit/jit.hpp, and src/jit/implementation.md
///        for the whole plan.
///
/// What runs today is the ahead-of-time pipeline, unchanged. The comments
/// below are the pieces jit/jit.hpp lists that live in this class, each with
/// where it goes, what to write, and how the code should look. The examples
/// are sketches in the house style -- one-word names, the five verbs,
/// designated initialisers, std::format -- not code to paste unread: the
/// engine's own functions they name are real, and their lines are where to
/// look.
#include "jit/jit.hpp"

#include <filesystem>
#include <ostream>
#include <string>
#include <vector>

namespace jit {
    bool Jit::typeset(const std::filesystem::path &source, const std::filesystem::path &destination,
                      std::ostream *report, std::ostream &errors, std::vector<std::string> *texts) {
        // ---------------------------------------------------------------
        // Piece 2: keep the engine warm.
        //
        // `run()` in src/latex.cpp builds everything a run needs as locals
        // and lets them go at its end: two arenas, the font Collection, the
        // Registry, the Shaper, the Typesetter, the Composer, the English
        // Hyphenator, the Lexicon, the Mouth, the Parser and both Wrappers
        // with their Contexts. Measured with --time-statistics on
        // build/main.mtex, the ones no document changes cost about a
        // millisecond a run, and the fresh 20 MB of arenas a page fault for
        // every 4 KB the run touches.
        //
        // 1. Make `run()` a protected member of latex::Session -- declared in
        //    latex.hpp under `protected:`, its body where it is -- so this
        //    class, a child, can call it. The free latex::compose() and
        //    latex::typeset() call it through a Session as they call it now.
        //
        // 2. Hand it what this class keeps, and let it build only what is
        //    missing. One struct of pointers does it -- the part of the
        //    engine a session keeps -- each null for the ahead-of-time path:
        //
        //        struct Engine {
        //            memory::Arena *arena{nullptr};                         // fonts, faces, patterns
        //            render::typography::Collection *collection{nullptr};
        //            render::typography::Registry *registry{nullptr};
        //            const render::typography::Shaper *shaper{nullptr};
        //            const render::typography::Hyphenator *hyphenator{nullptr};
        //        };
        //
        //    and in run(), where each is built today:
        //
        //        render::typography::Collection local(arena);
        //        render::typography::Collection &collection = engine.collection ? *engine.collection : local;
        //
        //    Font aliases are the one thing a document changes in them: put
        //    `collection.set("text", ...)` and `collection.set("expression",
        //    ...)` back at the start of every run, as run() does now.
        //
        // 3. Give memory::Arena a mark and a rewind, so the arenas a document
        //    fills are reused instead of mapped again:
        //
        //        /// @brief Where the arena stands: what set() rewinds to.
        //        [[nodiscard]] Position get() const noexcept;
        //        /// @brief Forgets everything allocated since @p position; its blocks stay mapped.
        //        void set(Position position) noexcept;
        //
        //    where Position is the block's index and the cursor in it. Pieces
        //    7 and 8 rewind to positions inside a run with the same two calls.
        //
        // 4. The faces opened on another thread while the first document
        //    reads (`likely`, in run()) are open from then on: start that
        //    thread for the first document only.
        //
        // 5. Other languages' patterns are read into a std::deque inside the
        //    Languages module (src/render/primitives/typesetting/
        //    languages.cpp) and lost with it; keep them here, by language, so
        //    a Russian document reads its patterns once a session.
        //
        // ---------------------------------------------------------------
        // Piece 3: set the document once, not twice.
        //
        // A document that asks for a page number -- `\pageref`,
        // `\tableofcontents`, `\printindex`, which set `rendering.paged` --
        // is set twice by run(): once only to learn the page each anchor
        // lands on (`composer.anchors`), and again with those as `folios`.
        // Between two saves the pages hardly ever move, so the last run's are
        // nearly always right:
        //
        //        std::vector<std::string> folios{}; // a member: the page each anchor was on last time
        //
        //        std::vector<std::string> anchors;  // what this run drew
        //        bool ok = run(..., folios.empty() ? nullptr : &folios, &anchors);
        //        if (anchors != folios) {           // a page moved: once more, as aot does
        //            folios = anchors;
        //            ok = run(..., &folios, &anchors);
        //        }
        //        folios = std::move(anchors);
        //
        // run() takes `folios` today as "this is the second pass" and skips
        // its own first pass when given them, which is what this wants; it
        // needs an out-parameter for the anchors it drew. Anchors are
        // numbered in the order they are met (`context.anchors++` in
        // sections.cpp, references.cpp, citations.cpp, floats.cpp), so a
        // heading added near the top moves every number after it, and that
        // run takes two passes -- correct, only slower once. Report the
        // errors of the last pass alone, as run() does: hold the first pass's
        // in a std::ostringstream and drop them when there is a second.
        //
        // ---------------------------------------------------------------
        // Pieces 7 and 8: start from a snapshot.
        //
        // For a snapshot to be put back, the objects it was taken from must
        // be the same objects next time: handlers capture `this` and
        // `&context`, so the Lexicon, Mouth, Parser, both Wrappers, both
        // Contexts, the Typesetter and the Composer become members here,
        // built once, in the order run() builds them. Then, per run (the
        // detail is in jit/snapshot.hpp):
        //
        //        const std::size_t changed = ...;   // the first byte that differs from `text`
        //        const Snapshot *start = nullptr;   // the last checkpoint before it
        //        for (const Snapshot &checkpoint: checkpoints) {
        //            if (checkpoint.offset <= changed) start = &checkpoint;
        //        }
        //        if (start) { /* put it back, rewind the arenas, read on from start->offset */ }
        //        else       { /* a whole run, taking checkpoints as it goes */ }
        //
        // ---------------------------------------------------------------
        // Piece 9: the snapshot on disk (jit::Format).
        //
        // Two calls, once the format exists: on the first run of a session,
        // before anything is built, read the file beside the document and,
        // when its key matches, start from it; after a run that took a new
        // snapshot at `\begin{document}`, write it back. Here, and nowhere
        // else, so a Jit that never finds the file runs exactly as it does
        // now.
        //
        // ---------------------------------------------------------------
        // Handing the JIT to other languages.
        //
        // The C library (protocols/ffi.hpp) adds operations only after the
        // last one, `snippet`, so a program built against an older header
        // finds each where it was: a warm session there is a new
        // constructor at the end of struct Latex, returning a Session that is
        // a jit::Jit. WebAssembly is in jit/jit.hpp and implementation.md.
        const bool ok = latex::compose(assets, source, destination, host, report, errors, &pages);
        if (texts) *texts = pages;
        return ok;
    }
}

#pragma once

namespace jit {
    /// @brief Tells the moment a file a document reads is saved, from the
    ///        operating system rather than by asking: piece 1 of jit::Jit.
    ///
    /// `--watch` in src/main.cpp looks at the document's time four times a
    /// second, so a save waits 125 ms on average -- up to 250 -- before
    /// anything starts. That wait is longer than a whole run of
    /// build/main.mtex, and it is the first thing a person notices of hot
    /// reload. It also looks at the document alone, so a change to a file
    /// it inputs, a picture or the bibliography sets nothing.
    ///
    /// Empty for now; what to write is below and in src/jit/watcher.cpp.
    ///
    /// @par Use (planned)
    /// @code
    /// jit::Watcher watcher;
    /// watcher.post(source.parent_path());              // and each folder the run read from
    /// for (const std::filesystem::path &folder: folders) watcher.post(folder);
    ///
    /// for (;;) {
    ///     const std::vector<std::filesystem::path> changed = watcher.get(std::chrono::milliseconds(250));
    ///     if (changed.empty()) continue;                // nothing yet: Ctrl+C is still heard
    ///     ok = run(Clock::now());
    /// }
    /// @endcode
    ///
    /// @par What to write
    /// 1. **Members**: one handle per folder posted, and what has changed
    ///    since get() last returned. On Windows each folder is a directory
    ///    handle with an OVERLAPPED and a buffer the system writes into; on
    ///    Linux one inotify descriptor and a watch per folder; on macOS one
    ///    FSEvents stream over all of them.
    /// 2. **`void post(const std::filesystem::path &folder)`** -- watches a
    ///    folder, once however often it is posted. A folder and not a file,
    ///    because editors save by writing a new file and renaming it over the
    ///    old one: a watch on the old file's handle would see nothing.
    /// 3. **`std::vector<std::filesystem::path> get(std::chrono::milliseconds timeout)`**
    ///    -- waits for a change under a posted folder, then waits on until
    ///    nothing has changed for about 15 ms, so a save written in two steps
    ///    sets the document once; returns every path that changed, or nothing
    ///    when the timeout passed first.
    /// 4. **`~Watcher()`** closes every handle. It owns them, so copying is
    ///    deleted with a reason, as memory::Arena does.
    /// 5. **Which folders.** latex::compose() should say which files the run
    ///    read: everything the `disk` reader in src/latex.cpp found (its
    ///    `nearby` table, minus the names it cached as missing), and the
    ///    document. A public `inputs` field on latex::Session and an
    ///    out-parameter on latex::compose() carry it. plots.cpp reads its
    ///    tables from disk directly (`std::ifstream` in plots.cpp); route
    ///    those through `disk` too, or a table's change goes unseen.
    /// 6. **The loop in src/main.cpp.** Replace the `sleep_for(250ms)` and
    ///    `last_write_time` with get(); post the folders again after every
    ///    run, since an edit may input a new file; keep the old loop as the
    ///    fallback when the Watcher cannot start, as on some network shares.
    ///
    /// @par WebAssembly
    /// There is no file system to watch in a page: the page has the text
    /// and calls `typeset` when it changes, after its own short pause while
    /// the person types. Compile this class's body out under Emscripten --
    /// `#if !defined(__EMSCRIPTEN__)` around everything in watcher.cpp --
    /// and leave the class itself, so code that names it still compiles.
    class Watcher {
    };
}

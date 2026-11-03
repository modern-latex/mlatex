#pragma once

namespace jit {
    /// @brief The engine's whole state at one point of a document, kept to
    ///        start from instead of from the first byte: pieces 7 and 8 of
    ///        jit::Jit.
    ///
    /// Taken when `\\begin{document}` opens, a snapshot is the preamble read
    /// once: the prelude, the class, every package and every definition,
    /// about 3 ms of build/main.mtex's run, put back while none of it has
    /// changed. Taken again every so often through the body, snapshots are
    /// checkpoints: an edit on page nine starts from the last checkpoint
    /// before it, and the pages before keep what they were.
    ///
    /// Empty for now; what to write is below and in src/jit/snapshot.cpp.
    ///
    /// @par Use (planned)
    /// @code
    /// // Taking one, from the hook \begin{document} calls:
    /// checkpoints.push_back(Snapshot{
    ///     .key = key, .offset = offset,
    ///     .positions = {arena.get(), scratch.get()},
    ///     .state = state, .table = mouth.table, .core = core, .visuals = visuals,
    ///     .selection = selection, .document = composer.document.state,
    /// });
    ///
    /// // Putting one back, before reading on from snapshot.offset:
    /// state = snapshot.state;
    /// mouth.table = snapshot.table;
    /// core = snapshot.core;                  // copied into the live object: its address stays
    /// visuals = snapshot.visuals;
    /// arena.set(snapshot.positions.front());
    /// @endcode
    ///
    /// @par What to write
    /// 1. **Make the state values.** Every module in both Wrappers holds
    ///    only values -- the references are in the Contexts, Mouth and
    ///    Document, never in a module -- so a whole syntax::primitives::Wrapper
    ///    copies with `=`, and assigning a copy back into the live one keeps
    ///    its address, which the handlers captured. syntax::semantics::Union
    ///    copies already. syntax::Mouth and render::layout::Document hold
    ///    references, so what they change goes into one member each that is
    ///    a value: for the Mouth, `macros`, `levels`, `records` and `lent`
    ///    (macros are `shared_ptr`, so the copy only counts references); for
    ///    the Document, its configuration, furniture, metadata, paragraph
    ///    state and where its list of blocks ends.
    /// 2. **Leave the handlers out.** Mouth's `handlers` are `unique_ptr`
    ///    and bound before the document starts; a snapshot keeps their count
    ///    and asserts it on the way back rather than copying them.
    /// 3. **The key.** A snapshot is good while nothing it was built from
    ///    has changed: the engine's version, the document's bytes before the
    ///    point it was taken, every file read until then with a hash of its
    ///    bytes, and the host's variables, commands and files. One 64-bit
    ///    FNV-1a over all of it does; the offset basis is
    ///    14695981039346656037 (collection.cpp and ledger.cpp drop its last
    ///    digit, which still hashes but is not FNV).
    /// 4. **Where to take the first.** In
    ///    syntax::primitives::logic::Environments, where `\\begin` opens a
    ///    block's scope (`mouth.push(semantics::Scope::Type::Environment)`
    ///    in environments.cpp): when the block is `document`, call a
    ///    `std::function<void()>` the syntax Context holds, empty unless a
    ///    Jit set it. The ahead-of-time path never sets it.
    /// 5. **Reading on from it.** Mouth::ingest lexes a whole buffer and its
    ///    `origin` gives every token one place, so it needs a way to start
    ///    at a line and column: lex the text from `offset` on and add the
    ///    lines before it to each token's line, or errors after an edit name
    ///    the wrong line. The catcodes in force are the snapshot's own, in
    ///    its Union.
    /// 6. **Checkpoints** (piece 8). Take one only where reading could
    ///    start from scratch: the parser at the top level, the document's
    ///    own group open and no other, no `\\input` open (no
    ///    `\\include:leave` waiting in the cursor), and nothing expanded
    ///    waiting to be read. About every 2 KB of source, or at each
    ///    `\\section`, and at most 64. Each also keeps how many parse outputs,
    ///    blocks, anchors and contents entries there were, so what came
    ///    after is cut off when it is put back.
    /// 7. **The patch journal** (piece 8). Some code changes nodes made
    ///    before it: a `\\label` writes its number into every `\\ref` that
    ///    came first, and its anchor into their links (references.cpp), and
    ///    a citation is set again when its `\\bibitem` arrives
    ///    (citations.hpp). Each such write goes into a list in the render
    ///    Context -- the node and what it held -- and a checkpoint keeps the
    ///    list's length; putting it back undoes everything after. A write
    ///    left out of the journal is a stale `\\ref` after an edit, which
    ///    the comparison test in tests/jit/test_jit.cpp catches.
    /// 8. **Host commands.** run() binds each with a reference into
    ///    `host.commands` (latex.cpp), and Session::define() may move that
    ///    vector. A Jit whose Mouth outlives a run binds them from a
    ///    container that never moves -- a std::deque -- and binds again on
    ///    define() and forget().
    ///
    /// @par Cost
    /// Copying the macro table is one reference count per symbol, a few
    /// thousand; everything else is small. Measure a snapshot with
    /// `--time-statistics` before choosing how often to take checkpoints.
    ///
    /// @par WebAssembly
    /// Nothing here differs in the module: a snapshot is plain memory. The
    /// module's memory only grows, so keep fewer checkpoints there -- 16 --
    /// and drop all of them when a document is set from scratch.
    class Snapshot {
    };
}

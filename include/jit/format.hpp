#pragma once

namespace jit {
    /// @brief The JIT's whole state on disk, beside the document, so the
    ///        first run after the program starts is warm too: piece 9 of
    ///        jit::Jit, as TeX's `.fmt` keeps a preamble already read.
    ///
    /// Everything else in the JIT lives in memory and is gone when the
    /// program ends: the first run of every session reads the preamble,
    /// sets the document twice, cuts every face and shapes every word. This
    /// writes what those runs worked out -- a jit::Snapshot at
    /// `\\begin{document}`, the page each anchor landed on, the glyph
    /// numbers and cuts of jit::Cache, the shaped words -- to one file, and
    /// reads it back at the start of the next session when nothing it was
    /// made from has changed.
    ///
    /// Empty for now, and yours to write; what it takes is below. The Jit
    /// runs without it: a session that finds no file, or a file that does
    /// not match, starts cold, exactly as it does today.
    ///
    /// @par Use (planned)
    /// @code
    /// // At the first run of a session, before anything is built:
    /// if (std::optional<Snapshot> kept = Format::get(place, key)) {
    ///     checkpoints.push_back(std::move(*kept));
    /// }
    ///
    /// // After a run that took a new snapshot at \begin{document}:
    /// Format::compose(place, checkpoints.front(), folios, cache);
    /// @endcode
    ///
    /// @par What the file holds, in order
    /// 1. **A header.** A magic number; the engine's version (VERSION's
    ///    first line); a hash of the list of modules in both Wrappers, in
    ///    order, since a module added or moved changes every symbol number;
    ///    and the snapshot's key (jit/snapshot.hpp). Any of them different
    ///    and the file is not read at all.
    /// 2. **The Lexicon**, every name in symbol order. Symbols are numbers
    ///    handed out in the order names are first interned, so a table
    ///    indexed by symbol means nothing without the names that numbered
    ///    it; read back, the names are interned again in the same order and
    ///    get the same numbers.
    /// 3. **The macro table.** Each macro's parameters, prefix and body are
    ///    tokens, and a token is a symbol, a category, a place and a view of
    ///    text in memory (syntax::Token). Write the symbol, the category and
    ///    the place, and the text as an offset into a string table written
    ///    once; read back, point the views into that table, kept in an arena
    ///    for the session.
    /// 4. **The Union**: catcodes, registers and fonts, which are numbers
    ///    and can be written as they are, save the fonts, which are written
    ///    by family, weight, slant and size and looked up again.
    /// 5. **Each module's state**, syntax first, then render, each behind
    ///    its own length, so a reader can skip one it does not know. Most
    ///    are maps of strings to strings; the render modules that hold
    ///    `layout::Node *` hold nodes made before the snapshot, which are
    ///    written once, in a list of their own, and named by their place in
    ///    it.
    /// 6. **The document**: its configuration, furniture and metadata.
    /// 7. **The caches**: the anchors' pages (piece 3), each face's glyph
    ///    numbers and cut (piece 4), the shaped words (piece 5). These are
    ///    plain bytes and are worth writing even before sections 2 to 6 are:
    ///    a file of only the caches already makes the second session's first
    ///    run a single pass.
    ///
    /// @par What to write
    /// 1. **`static std::optional<Snapshot> get(const std::filesystem::path &place, std::uint64_t key)`**
    ///    -- reads the file; nothing when it is missing, damaged, or for
    ///    another key or version.
    /// 2. **`static bool compose(const std::filesystem::path &place, const Snapshot &snapshot, ...)`**
    ///    -- writes it: to a temporary name first, renamed over the old one,
    ///    so a run interrupted halfway never leaves half a file to be read.
    /// 3. **Where it goes**: beside the document, as `paper.mtex` gives
    ///    `paper.fmt` -- or wherever the output directory is, beside the PDF.
    ///    Which, and the extension, are yours to choose.
    /// 4. **Little-endian, fixed widths** (`std::uint32_t`, `std::uint64_t`,
    ///    doubles as their bits), so a file written on one machine reads on
    ///    another of the same version.
    ///
    /// @par WebAssembly
    /// A page's module has a file system only in memory, gone on reload.
    /// Either hand the bytes to JavaScript -- a `format()` on the bound
    /// session returning a Uint8Array, as render::Wasm::bytes() returns the
    /// PDF, and a way to give them back -- and let the page keep them in
    /// IndexedDB or the browser's private file storage; or mount Emscripten's
    /// IDBFS where the file is written and call `FS.syncfs` after a run.
    /// The first leaves the choice to the page, and needs nothing linked.
    class Format {
    };
}

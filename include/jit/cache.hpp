#pragma once

namespace jit {
    /// @brief What a run worked out that the next run would work out the
    ///        same: each face's cut for the PDF, and each word's glyphs --
    ///        pieces 4 and 5 of jit::Jit.
    ///
    /// Writing build/main.mtex's PDF takes about 5 ms, and most of it is
    /// drawing every page and cutting eighteen faces down to the glyphs the
    /// document used, with HarfBuzz's subsetter, on as many threads as there
    /// are faces (render::Pdf, src/render/pdf.cpp). Shaping takes another
    /// 2.7 ms and more inside the parse. After an edit, nearly every face
    /// uses the glyphs it used before and nearly every word is a word it was
    /// before; a cache kept between runs hands both back.
    ///
    /// Empty for now; what to write is below and in src/jit/cache.cpp.
    ///
    /// @par Use (planned)
    /// @code
    /// // In the PDF writer, before cutting a face:
    /// const std::uint64_t hash = cache.hash(entry.glyphs);
    /// if (const Cache::Cut *kept = cache.get(face, hash)) {
    ///     program = kept->program;                         // the subset, ToUnicode and W as last time
    /// } else {
    ///     program = cut(face, entry.glyphs);               // hb_subset_or_fail, as pdf.cpp does now
    ///     cache.set(face, hash, {.program = program, .unicode = unicode, .widths = widths});
    /// }
    /// @endcode
    ///
    /// @par What to write
    /// 1. **Time it first.** --time-statistics counts the PDF as one line;
    ///    split it into drawing the pages and cutting the faces (around the
    ///    threads in pdf.cpp), and count HarfBuzz's shaping calls and their
    ///    time, including the shaping the parse does for headings and boxes.
    ///    Each cache below is worth what those lines say.
    /// 2. **Number glyphs the same way every run** (piece 4). The Composer
    ///    numbers each face's glyphs in the order they are first drawn
    ///    (`faces` in render::Composer, composer.cpp), so one new word on
    ///    page one renumbers every face after it and no cut can be kept.
    ///    Start each run's numbering from the last run's -- keyed by
    ///    `const render::typography::Face *`, which stays the same object
    ///    once piece 2 keeps the Registry -- and add new glyphs at the end.
    ///    The `/F` numbers of the faces follow the same rule.
    /// 3. **Keep each cut** (piece 4): by face and a hash of its glyphs in
    ///    order, the bytes `hb_subset_or_fail` made, the ToUnicode map and
    ///    the W array (pdf.cpp writes all three from the glyph list). Object
    ///    numbers are not part of it: the writer numbers objects as it goes.
    /// 4. **Let unused glyphs go.** A glyph a run no longer draws keeps its
    ///    number and stays in the cut, so a preview's file grows a little;
    ///    when more than a quarter of a face's glyphs are unused, number that
    ///    face afresh. The ahead-of-time target always numbers afresh.
    /// 5. **Shape each word once** (piece 5). render::layout::Document keeps
    ///    two tables already (`ledger` and `words`, src/render/layout/
    ///    ledger.cpp): keyed by font, size and a view of the text, emptied
    ///    when the language changes, and full at three quarters. Across runs
    ///    the key must own its text -- the run's text is gone -- so copy it
    ///    into this class's own arena, and add the features and the
    ///    hyphenator to the key instead of emptying on a change of language.
    ///    A hit is copied into the run's arena, never handed out as it is:
    ///    the line breaker adds a hyphen to the glyphs it breaks.
    /// 6. **When full**, empty it and start again: simpler than evicting,
    ///    and a document fills it again in one run.
    ///
    /// @par WebAssembly
    /// The same in the module. Its memory only grows, so size both tables
    /// smaller there -- under `#if defined(__EMSCRIPTEN__)` -- and empty them
    /// rather than let them grow past a few megabytes.
    class Cache {
    };
}

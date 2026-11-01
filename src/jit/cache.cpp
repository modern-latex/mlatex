/// @file
/// @brief Cuts and shaped words kept between runs: see jit/cache.hpp.
///
/// Empty for now. What follows is how its members and the two places that
/// call it should look.
#include "jit/cache.hpp"

namespace jit {
    // The members:
    //
    //     struct Cut {
    //         std::uint64_t hash{0};                     // the face's glyphs, in their order
    //         std::string program{};                     // the subset hb_subset_or_fail made
    //         std::string unicode{};                     // its ToUnicode CMap
    //         std::string widths{};                      // its W array
    //     };
    //     std::unordered_map<const render::typography::Face *, Cut> cuts{};
    //
    //     struct Word {
    //         const render::typography::Font *font{nullptr};
    //         std::string_view text{};                   // copied into `arena`, so it outlives the run
    //         memory::Slice<render::layout::Node *> glyphs{};  // as the Shaper made them, never handed out
    //     };
    //     memory::Arena arena{4 * 1024 * 1024};
    //     std::vector<Word> words{};                     // open addressing, as layout::Ledger does
    //
    //     std::unordered_map<const render::typography::Face *, std::vector<std::uint32_t>> numbers{};
    //                                                    // the last run's glyph numbers, piece 4
    //
    // Where the cut is looked up -- render::Pdf::compose, in the loop that
    // hands faces to threads (pdf.cpp, around hb_subset_or_fail): the
    // thread that takes a face asks the cache first, and only cuts on a
    // miss. The cache is read from several threads and written after they
    // join, so reading needs no lock.
    //
    // Where a word is looked up -- render::layout::Document, where `words`
    // is asked today (document.cpp): ask the session's table on a miss in
    // the run's own, and copy what it holds into the run's arena:
    //
    //     memory::Slice<layout::Node *> glyphs = arena.allocate<layout::Node *>(kept->glyphs.count);
    //     for (std::size_t index = 0; index < glyphs.count; ++index) {
    //         glyphs[index] = arena.compose<layout::Node>(*kept->glyphs[index]);
    //     }
    //
    // The PDF writer and the Document get the cache as a pointer, null on
    // the ahead-of-time path, so a run without a Jit is the run it is now.
    //
    // Tested in tests/jit/test_cache.cpp: set one document twice through a
    // Jit and assert the second run cut no face and shaped no word -- the
    // counters --time-statistics gains in step 1 -- and that the two PDFs'
    // pages read the same; then add a word with a new letter and assert one
    // face was cut again, and only one.
}

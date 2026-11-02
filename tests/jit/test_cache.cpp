#include "jit/cache.hpp"

#include <cassert>
#include <type_traits>

// The Cache, which keeps each face's cut and each word's glyphs between
// runs. It holds nothing yet, so this only shows the header stands on its
// own; once it holds them, the check below fails on purpose -- replace it
// with these:
//
//     set one document twice through a jit::Jit and assert the second run
//     cut no face and shaped no word, by the counters --time-statistics
//     gains, and that both runs' pages read the same;
//
//     add a word with a letter the document had not used, and assert one
//     face was cut again, and only one;
//
//     fill the word table past its limit and assert it starts again empty
//     rather than growing.

int main() {
    assert(std::is_empty_v<jit::Cache> && "empty for now: write the checks above once it holds something");
    return 0;
}

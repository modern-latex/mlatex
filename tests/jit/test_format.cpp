#include "jit/format.hpp"

#include <cassert>
#include <type_traits>

// Format, the JIT's state on disk beside the document. It holds nothing
// yet, so this only shows the header stands on its own; once it reads and
// writes the file, the check below fails on purpose -- replace it with
// these:
//
//     write one jit::Jit's snapshot, read it into a second Jit, set the
//     same document through both and assert their pages are the same;
//
//     change one byte of the preamble and assert the file is not used;
//
//     cut the file short, and write one with another version in its
//     header, and assert neither is used and neither crashes.

int main() {
    assert(std::is_empty_v<jit::Format> && "empty for now: write the checks above once it holds something");
    return 0;
}

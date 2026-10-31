#include "jit/watcher.hpp"

#include <cassert>
#include <type_traits>

// The Watcher, which tells the moment a file is saved. It holds nothing yet,
// so this only shows the header stands on its own; once it holds handles,
// the check below fails on purpose -- replace it with these:
//
//     post a folder under std::filesystem::temp_directory_path(), write a
//     file there from a std::jthread, and assert get() returns its path
//     within a second;
//
//     write a temporary file and std::filesystem::rename() it over the
//     first, as an editor saves, and assert that is reported once;
//
//     assert get() with nothing written returns nothing when its timeout
//     passes.

int main() {
    assert(std::is_empty_v<jit::Watcher> && "empty for now: write the checks above once it holds something");
    return 0;
}

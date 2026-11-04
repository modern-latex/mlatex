#include "jit/snapshot.hpp"

#include <cassert>
#include <type_traits>

// A Snapshot, the engine's state at one point of a document. It holds
// nothing yet, so this only shows the header stands on its own; once it
// holds the state, the check below fails on purpose -- replace it with these:
//
//     define a macro and set a register, take a snapshot, change both, put
//     the snapshot back and assert both are as they were;
//
//     a \ref before a \label, a checkpoint between them, the label taken
//     away and the run started from the checkpoint: assert the reference
//     reads ?? again, which is the journal undoing the label's patch;
//
//     change one byte before \begin{document} and assert the snapshot's
//     key no longer matches.

int main() {
    assert(std::is_empty_v<jit::Snapshot> && "empty for now: write the checks above once it holds something");
    return 0;
}

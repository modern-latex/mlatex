/// @file
/// @brief The engine's state at one point of a document: see
///        jit/snapshot.hpp.
///
/// Empty for now. A snapshot is a struct of values, so most of it needs no
/// code at all -- its members, copied in and copied back. What follows is
/// how those members should look, and the one place each comes from.
#include "jit/snapshot.hpp"

namespace jit {
    // The members, in the order they are taken:
    //
    //     std::uint64_t key{0};                          // what it was built from: see the header
    //     std::size_t offset{0};                         // the byte of the document it starts at
    //     std::uint32_t line{0};                         // and that byte's line, for ingest
    //     std::array<memory::Arena::Position, 2> positions{};  // arena and scratch, from get()
    //
    //     syntax::semantics::Union state{};              // registers, catcodes, fonts
    //     syntax::Mouth::Table table{};                  // macros, levels, records, lent
    //     std::size_t handlers{0};                       // how many were bound: asserted, not copied
    //     syntax::primitives::Wrapper core;              // every syntax module, by value
    //     render::primitives::Wrapper visuals;           // every render module, by value
    //     render::primitives::Selection selection{};
    //     render::layout::Document::State document{};
    //
    //     std::size_t outputs{0};                        // parse outputs so far
    //     std::size_t anchors{0};                        // the render Context's anchor count
    //     std::size_t entries{0};                        // contents entries so far
    //     std::size_t journal{0};                        // patches written so far
    //
    // `Table` and `State` are the value members jit/snapshot.hpp asks the
    // Mouth and the Document to gather what they change into; `Position` is
    // memory::Arena's mark (see piece 2 in src/jit/jit.cpp). The two
    // Wrappers have no default constructor -- each interns its names in a
    // Lexicon -- so a Snapshot is made by copying the live ones, never
    // empty.
    //
    // The journal, in render::primitives::Context:
    //
    //     struct Patch {
    //         layout::Node *node{nullptr};               // the node a later command changed
    //         layout::Node before{};                     // what it held until then
    //     };
    //     std::vector<Patch> journal{};
    //
    // written where references.cpp gives earlier references their text and
    // their links an index, and where a citation is set again:
    //
    //     context.journal.push_back({.node = reference, .before = *reference});
    //     reference->value = context.arena.copy(write(mark, form, context));
    //
    // and undone, newest first, down to a checkpoint's length:
    //
    //     while (context.journal.size() > snapshot.journal) {
    //         *context.journal.back().node = context.journal.back().before;
    //         context.journal.pop_back();
    //     }
    //
    // Tested in tests/jit/test_snapshot.cpp: define a macro and set a
    // register, take a snapshot, change both, put it back and assert they
    // are as they were; then a `\ref` before a `\label`, a checkpoint
    // between them, the label taken away, and the reference back to `??`.
}

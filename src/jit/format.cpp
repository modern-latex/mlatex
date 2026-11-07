/// @file
/// @brief The JIT's state on disk: see jit/format.hpp.
///
/// Empty for now, and yours to write. What follows is the shape a reader
/// and a writer of the file could take; the order of the sections and why
/// each is written the way it is are in the header.
#include "jit/format.hpp"

namespace jit {
    // Writing, section by section, each behind its length so a reader can
    // step over what it does not know:
    //
    //     std::string bytes;
    //     const auto number = [&bytes](const std::uint64_t value, const std::size_t width) {
    //         for (std::size_t index = 0; index < width; ++index) {
    //             bytes.push_back(static_cast<char>((value >> (8 * index)) & 0xFF));   // little-endian
    //         }
    //     };
    //     bytes += "mLaTeXjit";                          // the magic
    //     number(version, 4);
    //     number(modules, 8);                            // the hash of the module list
    //     number(snapshot.key, 8);
    //
    //     const std::size_t start = bytes.size();
    //     number(0, 8);                                  // the section's length, filled in below
    //     for (const std::string_view name: lexicon.names) {
    //         number(name.size(), 4);
    //         bytes += name;
    //     }
    //     ... write the length at `start` ...
    //
    // A token, with its text in the string table:
    //
    //     number(static_cast<std::uint32_t>(token.symbol), 4);
    //     number(static_cast<std::uint8_t>(token.category), 1);
    //     number(token.location.line, 4);
    //     number(token.location.column, 4);
    //     number(token.location.file, 4);
    //     number(table.get(token.text), 4);              // its offset in the string table
    //
    // Then the file, written whole and renamed into place:
    //
    //     const std::filesystem::path temporary = std::filesystem::path(place) += ".partial";
    //     if (std::ofstream file(temporary, std::ios::binary); file) file.write(bytes.data(), ...);
    //     std::filesystem::rename(temporary, place, failure);
    //
    // Reading is the same in reverse, every length checked against what is
    // left before it is trusted: a damaged file is a missing file, never a
    // crash.
    //
    // Tested in tests/jit/test_format.cpp: write a Jit's snapshot and read
    // it into a second Jit, set the same document through both, and assert
    // their pages are the same; then change one byte of the preamble and
    // assert the file is not used; then cut the file short and assert it is
    // not used either.
}

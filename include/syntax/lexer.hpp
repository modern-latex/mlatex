#pragma once

/// @file
/// @brief Reads source text into tokens, as TeX's eyes do.

#include "memory/location.hpp"
#include "syntax/catcodes.hpp"
#include "syntax/lexicon.hpp"
#include "syntax/tokens.hpp"
#include "syntax/traceback.hpp"

#include <cstdint>
#include <string_view>
#include <vector>

namespace syntax {
    /// @brief Reads source text into tokens, as TeX's eyes do: a character's category decides what it becomes.
    class Lexer {
    public:
        /// @brief Which of TeX's three reading states the lexer is in, and the one after a paragraph break.
        enum class Type {
            Newline, ///< State N: line start; an end-of-line here is \\par
            Skip,    ///< State S: skipping blanks; an end-of-line here starts a new line and nothing more
            Middle,  ///< State M: mid-line; an end-of-line here is a space
            Blank    ///< Just past a \\par; further empty lines add nothing
        };

        /// @brief Binds a lexer to a source buffer.
        /// @param source Text to lex; must outlive the lexer.
        /// @param codes  Category table, consulted per character and live to
        ///               `\\catcode` changes made while lexing.
        /// @param lexicon  Interning table for the tokens produced.
        /// @param file     The number Mouth::files gives the file @p source
        ///                 is, for every location handed out; zero for none.
        Lexer(std::string_view source, Catcodes &codes, Lexicon &lexicon, std::uint32_t file = 0);

        /// @brief Reads the next token.
        /// @return The token, or an end token when the text is finished.
        Token advance();

        /// @brief Whether the text is finished.
        /// @return Whether no character is left to read.
        [[nodiscard]] bool empty() const noexcept;

        /// @brief Errors the lexer has recorded.
        /// @return The errors, in the order they were found.
        [[nodiscard]] const std::vector<Traceback> &traceback() const noexcept { return tracebacks; }

    private:
        /// @brief How many bytes a UTF-8 character takes, from its first.
        /// @param lead Its first byte.
        /// @return 1 to 4.
        [[nodiscard]] static constexpr std::size_t length(const char lead) noexcept {
            const auto byte = static_cast<unsigned char>(lead);
            if ((byte & 0x80) == 0) return 1;
            if ((byte & 0xE0) == 0xC0) return 2;
            if ((byte & 0xF0) == 0xE0) return 3;
            if ((byte & 0xF8) == 0xF0) return 4;
            return 1;
        }

        /// @brief Whether a character ends a line.
        /// @param symbol The character.
        /// @return Whether it is a carriage return or a line feed.
        [[nodiscard]] static constexpr bool ending(const char symbol) noexcept {
            return symbol == '\n' || symbol == '\r';
        }

        /// @brief The text being read.
        std::string_view sources{};
        /// @brief The category of every character, as `\\catcode` last set it.
        Catcodes &table;
        /// @brief Where names are interned.
        Lexicon &lexicon;
        /// @brief How far into the text the lexer has read, in bytes.
        std::size_t offset = 0;
        /// @brief The line and column it has reached.
        memory::Location location{1, 1};
        /// @brief Which of TeX's reading states it is in.
        Type type = Type::Newline;

        /// @name Text read as it stands
        /// A \\verb's text, lexed along with the command and handed out as
        /// the next token; and a verbatim block's body, from #opening to
        /// #stop, handed out whole as one token when the scan reaches it.
        /// @{
        /// @brief A token read and not yet handed out.
        Token held{};
        /// @brief Where text read as it stands began, or npos when none is being read.
        std::size_t opening = std::string_view::npos;
        /// @brief Where that text stops.
        std::size_t stop = 0;
        /// @}
        std::vector<Traceback> tracebacks{}; ///< Illegal bytes, drained by Mouth::ingest.
    };
}

/// @file
/// @brief Color implementation: every format this engine reads into the
///        0-1 form PDF wants.
#include "render/graphics/color.hpp"
#include "patch.hpp"

#include <array>
#include <charconv>
#include <cstdint>

namespace render::graphics {
    /// @brief Reads one byte as two hex digits.
    /// @param text   Two-character slice to decode.
    /// @param value  Receives the byte on success.
    /// @return True when both characters were valid hex digits.
    [[nodiscard]] static bool byte(const std::string_view text, std::uint8_t &value) noexcept {
        unsigned parsed = 0;
        const auto [stop, failure] = std::from_chars(text.data(), text.data() + text.size(), parsed, 16);
        if (failure != std::errc{} || stop != text.data() + text.size()) return false;
        value = static_cast<std::uint8_t>(parsed);
        return true;
    }

    /// @brief Trims spaces from both ends.
    /// @param text Text to trim.
    /// @return The text without them.
    [[nodiscard]] static std::string_view trim(std::string_view text) noexcept {
        while (!text.empty() && text.front() == ' ')
            text.remove_prefix(1);
        while (!text.empty() && text.back() == ' ')
            text.remove_suffix(1);
        return text;
    }

    Color Color::hex(std::string_view text) noexcept {
        if (text.starts_with('#')) text.remove_prefix(1);
        if (text.size() != 6 && text.size() != 8) return black;

        std::uint8_t red = 0;
        std::uint8_t green = 0;
        std::uint8_t blue = 0;
        std::uint8_t alpha = 255;
        if (!byte(text.substr(0, 2), red) || !byte(text.substr(2, 2), green) || !byte(text.substr(4, 2), blue) ||
            (text.size() == 8 && !byte(text.substr(6, 2), alpha))) {
            return black;
        }

        return {.red = static_cast<float>(red) / 255.0f,
                .green = static_cast<float>(green) / 255.0f,
                .blue = static_cast<float>(blue) / 255.0f,
                .alpha = static_cast<float>(alpha) / 255.0f};
    }

    Color Color::parse(std::string_view text) noexcept {
        text = trim(text);

        if (const bool alpha = text.starts_with("rgba("); alpha || text.starts_with("rgb(")) {
            if (!text.ends_with(')')) return black;
            text.remove_prefix(alpha ? 5 : 4);
            text.remove_suffix(1);

            // `a,b,c` between the parentheses, each part trimmed; three or
            // four of them, and each wanted one a plain decimal number.
            std::array<std::string_view, 4> parts{};
            std::size_t count = 0;
            while (count < parts.size()) {
                const std::size_t comma = text.find(',');
                parts[count++] = trim(comma == std::string_view::npos ? text : text.substr(0, comma));
                if (comma == std::string_view::npos) break;
                text.remove_prefix(comma + 1);
            }
            if (count != 3 && count != 4) return black;

            std::array channel{0.0f, 0.0f, 0.0f, 1.0f};
            const std::size_t wanted = alpha ? 4 : 3;
            for (std::size_t index = 0; index < wanted; ++index) {
                const std::string_view part = parts[index];
                if (part.empty()) return black;
                if (const auto [stop, failure] = patch::decimal(part.data(), part.data() + part.size(), channel[index]);
                    failure != std::errc{} || stop != part.data() + part.size())
                    return black;
            }

            return {.red = channel[0] / 255.0f,
                    .green = channel[1] / 255.0f,
                    .blue = channel[2] / 255.0f,
                    .alpha = channel[3]};
        }

        // A color by the name xcolor gives it.
        struct Named {
            std::string_view name;
            Color color;
        };

        static constexpr std::array<Named, 20> table{{
                {.name = "black", .color = black},
                {.name = "white", .color = white},
                {"red", graphics::red},
                {"green", graphics::green},
                {.name = "blue", .color = graphics::blue},
                {.name = "cyan", .color = cyan},
                {"magenta", magenta},
                {"yellow", yellow},
                {.name = "gray", .color = gray},
                {.name = "grey", .color = gray},
                {"darkgray", darkgray},
                {"lightgray", lightgray},
                {.name = "brown", .color = brown},
                {.name = "lime", .color = lime},
                {"olive", olive},
                {"orange", orange},
                {.name = "pink", .color = pink},
                {.name = "purple", .color = purple},
                {"teal", teal},
                {"violet", violet},
        }};
        for (const auto &[name, color] : table) {
            if (text == name) return color;
        }

        return hex(text);
    }
}

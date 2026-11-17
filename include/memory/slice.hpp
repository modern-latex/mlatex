#pragma once

/// @file
/// @brief A pointer and a count: a view of memory an arena owns.

#include <cstddef>

namespace memory {
    /// @brief A pointer and a count: a view over storage owned elsewhere.
    ///
    /// Every run of objects the engine allocates from an Arena is handed out
    /// as a slice. A slice owns nothing and frees nothing; the arena does both
    /// and outlives every slice into it.
    ///
    /// Constness follows `std::span`: `const Slice<T>` fixes the view, not the
    /// elements. Use `Slice<const T>` to forbid writing through it.
    ///
    /// @tparam Type Element type.
    template <typename Type> struct Slice {
        Type *data = nullptr;  ///< First element, or nullptr when empty.
        std::size_t count = 0; ///< Number of elements.

        /// @return Whether the slice is empty.
        /// @brief Reports whether the slice has no elements.
        [[nodiscard]] constexpr bool empty() const noexcept { return count == 0; }

        /// @return The number of elements.
        /// @brief Number of elements.
        [[nodiscard]] constexpr std::size_t size() const noexcept { return count; }

        /// @return A pointer to the first element.
        /// @brief First element, for range-based iteration.
        [[nodiscard]] constexpr Type *begin() const noexcept { return data; }

        /// @return A pointer one past the last element.
        /// @brief One past the last element, for range-based iteration.
        [[nodiscard]] constexpr Type *end() const noexcept { return data + count; }

        /// @brief Unchecked element access.
        /// @param index Element index; out of range is undefined behaviour.
        /// @return The element.
        [[nodiscard]] constexpr Type &operator[](const std::size_t index) const noexcept { return data[index]; }
    };
}

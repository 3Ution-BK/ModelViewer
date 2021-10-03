
#include <type_traits>

namespace Event
{

constexpr bool operator==(const InputModifierFlags &lhs,
                          const InputModifierFlags &rhs) noexcept
{
    return static_cast<std::underlying_type<InputModifierFlags>::type>(lhs) ==
           static_cast<std::underlying_type<InputModifierFlags>::type>(rhs);
}

constexpr bool operator!=(const InputModifierFlags &lhs,
                          const InputModifierFlags &rhs) noexcept
{
    return static_cast<std::underlying_type<InputModifierFlags>::type>(lhs) !=
           static_cast<std::underlying_type<InputModifierFlags>::type>(rhs);
}

constexpr InputModifierFlags &operator&=(InputModifierFlags &lhs,
                                         const InputModifierFlags &rhs) noexcept
{
    lhs = static_cast<InputModifierFlags>(
        static_cast<std::underlying_type<InputModifierFlags>::type>(lhs) &
        static_cast<std::underlying_type<InputModifierFlags>::type>(rhs));
    return lhs;
}

constexpr InputModifierFlags &operator|=(InputModifierFlags &lhs,
                                         const InputModifierFlags &rhs) noexcept
{
    lhs = static_cast<InputModifierFlags>(
        static_cast<std::underlying_type<InputModifierFlags>::type>(lhs) |
        static_cast<std::underlying_type<InputModifierFlags>::type>(rhs));
    return lhs;
}

constexpr InputModifierFlags &operator^=(InputModifierFlags &lhs,
                                         const InputModifierFlags &rhs) noexcept
{
    lhs = static_cast<InputModifierFlags>(
        static_cast<std::underlying_type<InputModifierFlags>::type>(lhs) ^
        static_cast<std::underlying_type<InputModifierFlags>::type>(rhs));
    return lhs;
}

constexpr InputModifierFlags operator&(InputModifierFlags lhs, // Pass by value
                                       const InputModifierFlags &rhs) noexcept
{
    lhs &= rhs;
    return lhs;
}

constexpr InputModifierFlags operator|(InputModifierFlags lhs, // Pass by value
                                       const InputModifierFlags &rhs) noexcept
{
    lhs |= rhs;
    return lhs;
}

constexpr InputModifierFlags operator^(InputModifierFlags lhs, // Pass by value
                                       const InputModifierFlags &rhs) noexcept
{
    lhs ^= rhs;
    return lhs;
}

constexpr InputModifierFlags operator~(InputModifierFlags x) noexcept
{
    return static_cast<InputModifierFlags>(
        ~(static_cast<std::underlying_type<InputModifierFlags>::type>(x)));
}

constexpr InputModifierFlags &operator<<=(InputModifierFlags &x,
                                          size_t pos) noexcept
{
    x = static_cast<InputModifierFlags>(
        static_cast<std::underlying_type<InputModifierFlags>::type>(x) << pos);
    return x;
}

constexpr InputModifierFlags &operator>>=(InputModifierFlags &x,
                                          size_t pos) noexcept
{
    x = static_cast<InputModifierFlags>(
        static_cast<std::underlying_type<InputModifierFlags>::type>(x) >> pos);
    return x;
}

constexpr InputModifierFlags operator<<(InputModifierFlags x, // Pass by value
                                        size_t pos) noexcept
{
    x <<= pos;
    return x;
}

constexpr InputModifierFlags operator>>(InputModifierFlags x, // Pass by value
                                        size_t pos) noexcept
{
    x >>= pos;
    return x;
}

} // namespace Event

#ifndef MODELVIEWER_EVENT_INPUTMODIFIERFLAGS_HPP_
#define MODELVIEWER_EVENT_INPUTMODIFIERFLAGS_HPP_

#include "OpenGL/OpenGLLib.hpp"

namespace Event
{

enum InputModifierFlags : int
{
    NoModifier = 0x0000,
    Shift = GLFW_MOD_SHIFT,
    Control = GLFW_MOD_CONTROL,
    Alt = GLFW_MOD_ALT,
    Super = GLFW_MOD_SUPER,
    CapsLock = GLFW_MOD_CAPS_LOCK,
    NumLock = GLFW_MOD_NUM_LOCK
};

constexpr bool operator==(const InputModifierFlags &lhs,
                          const InputModifierFlags &rhs) noexcept;

constexpr bool operator!=(const InputModifierFlags &lhs,
                          const InputModifierFlags &rhs) noexcept;

constexpr InputModifierFlags &
operator&=(InputModifierFlags &lhs, const InputModifierFlags &rhs) noexcept;

constexpr InputModifierFlags &
operator|=(InputModifierFlags &lhs, const InputModifierFlags &rhs) noexcept;

constexpr InputModifierFlags &
operator^=(InputModifierFlags &lhs, const InputModifierFlags &rhs) noexcept;

constexpr InputModifierFlags operator&(InputModifierFlags lhs,
                                       const InputModifierFlags &rhs) noexcept;

constexpr InputModifierFlags operator|(InputModifierFlags lhs,
                                       const InputModifierFlags &rhs) noexcept;

constexpr InputModifierFlags operator^(InputModifierFlags lhs,
                                       const InputModifierFlags &rhs) noexcept;

constexpr InputModifierFlags operator~(InputModifierFlags x) noexcept;

constexpr InputModifierFlags &operator<<=(InputModifierFlags &x,
                                          size_t pos) noexcept;

constexpr InputModifierFlags &operator>>=(InputModifierFlags &x,
                                          size_t pos) noexcept;

constexpr InputModifierFlags operator<<(InputModifierFlags x,
                                        size_t pos) noexcept;

constexpr InputModifierFlags operator>>(InputModifierFlags x,
                                        size_t pos) noexcept;

} // namespace Event

#include "InputModifierFlags-inl.hpp"

#endif // MODELVIEWER_EVENT_INPUTMODIFIERFLAGS_HPP_

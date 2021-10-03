#include "KeyboardEvent.hpp"

namespace Event
{

KeyboardEvent::KeyboardEvent(int key, int action, int scanCode,
                             TimeType timestamp, const GLFWwindow *window,
                             int modifier)
    : KeyboardEvent{static_cast<KeyboardCode>(key),
                    static_cast<InputAction>(action),
                    scanCode,
                    timestamp,
                    window,
                    static_cast<InputModifierFlags>(modifier)}
{
}

KeyboardEvent::KeyboardEvent(KeyboardCode key, InputAction action, int scanCode,
                             TimeType timestamp, const GLFWwindow *window,
                             InputModifierFlags modifier)
    : InputEvent{timestamp, window, modifier}, key_{key}, scanCode_{scanCode},
      action_{action}
{
}

KeyboardEvent::KeyboardEvent(KeyboardEvent &&other) noexcept = default;

KeyboardEvent &
KeyboardEvent::operator=(KeyboardEvent &&other) noexcept = default;

KeyboardEvent::~KeyboardEvent() = default;

} // namespace Event

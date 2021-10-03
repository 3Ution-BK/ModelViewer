#include "MouseEvent.hpp"

namespace Event
{

MouseEvent::MouseEvent(int button, const PositionType &position, int action,
                       Event::TimeType timestamp, const GLFWwindow *window,
                       int modifier)
    : MouseEvent{static_cast<MouseCode>(button),
                 position,
                 static_cast<InputAction>(action),
                 timestamp,
                 window,
                 static_cast<InputModifierFlags>(modifier)}
{
}

MouseEvent::MouseEvent(MouseCode button, const PositionType &position,
                       InputAction action, Event::TimeType timestamp,
                       const GLFWwindow *window, InputModifierFlags modifier)
    : InputEvent{timestamp, window, modifier}, button_{button}, action_{action},
      position_{position}
{
}

MouseEvent::MouseEvent(MouseEvent &&other) noexcept = default;

MouseEvent &MouseEvent::operator=(MouseEvent &&other) noexcept = default;

MouseEvent::~MouseEvent() = default;

} // namespace Event

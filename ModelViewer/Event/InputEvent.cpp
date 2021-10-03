#include "InputEvent.hpp"

namespace Event
{

InputEvent::InputEvent(TimeType timestamp, const GLFWwindow *window,
                       int modifier)
    : InputEvent{timestamp, window, static_cast<InputModifierFlags>(modifier)}
{
}

InputEvent::InputEvent(TimeType timestamp, const GLFWwindow *window,
                       InputModifierFlags modifier)
    : Event{timestamp, window}, modifier_{modifier}
{
}

InputEvent::InputEvent(InputEvent &&other) noexcept = default;

InputEvent &InputEvent::operator=(InputEvent &&other) noexcept = default;

InputEvent::~InputEvent() = default;

} // namespace Event

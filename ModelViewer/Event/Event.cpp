#include "Event.hpp"

namespace Event
{

Event::Event(Event::TimeType timestamp, const GLFWwindow *window)
    : window_{window}, timestamp_{timestamp}
{
}

Event::Event(Event &&other) noexcept = default;

Event &Event::operator=(Event &&other) noexcept = default;

Event::~Event() = default;

} // namespace Event

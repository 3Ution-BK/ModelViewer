#include "MoveEvent.hpp"

namespace Event
{

MoveEvent::MoveEvent(const PositionType &position,
                     const PositionType &oldPosition, Event::TimeType timestamp,
                     const GLFWwindow *window)
    : Event{timestamp, window}, position_{position}, oldPosition_{oldPosition}
{
}

MoveEvent::MoveEvent(MoveEvent &&other) noexcept = default;

MoveEvent &MoveEvent::operator=(MoveEvent &&other) noexcept = default;

MoveEvent::~MoveEvent() = default;

} // namespace Event

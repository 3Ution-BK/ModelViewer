#include "ResizeEvent.hpp"

namespace Event
{

ResizeEvent::ResizeEvent(const SizeType &size, const SizeType &oldSize,
                         Event::TimeType timestamp, const GLFWwindow *window)
    : Event{timestamp, window}, size_{size}, oldSize_{oldSize}
{
}

ResizeEvent::ResizeEvent(ResizeEvent &&other) noexcept = default;

ResizeEvent &ResizeEvent::operator=(ResizeEvent &&other) noexcept = default;

ResizeEvent::~ResizeEvent() = default;

} // namespace Event

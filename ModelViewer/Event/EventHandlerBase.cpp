#include "EventHandlerBase.hpp"

namespace Event
{

EventHandlerBase::EventHandlerBase() {}

EventHandlerBase::EventHandlerBase(const EventHandlerBase &other) = default;

EventHandlerBase::EventHandlerBase(EventHandlerBase &&other) noexcept = default;

EventHandlerBase &
EventHandlerBase::operator=(const EventHandlerBase &other) = default;

EventHandlerBase &
EventHandlerBase::operator=(EventHandlerBase &&other) noexcept = default;

EventHandlerBase::~EventHandlerBase() = default;

} // namespace Event

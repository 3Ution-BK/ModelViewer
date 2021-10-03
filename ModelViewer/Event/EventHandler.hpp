#ifndef MODELVIEWER_EVENT_HANDLER_HPP_
#define MODELVIEWER_EVENT_HANDLER_HPP_

#include "Event.hpp"
#include "EventHandlerBase.hpp"

#include <functional>
#include <type_traits>

namespace Event
{

template <typename WindowType, typename EventType,
          void (WindowType::*respondFunction)(EventType *)>
class EventHandler : public EventHandlerBase
{
    static_assert(std::is_base_of<Event, EventType>::value,
                  "'EventType' is not derived from Event::Event.");

public:
    explicit EventHandler(WindowType &window);

    EventHandler(const EventHandler &other);
    EventHandler(EventHandler &&other) noexcept;
    EventHandler &operator=(const EventHandler &other);
    EventHandler &operator=(EventHandler &&other) noexcept;

    virtual ~EventHandler();

    virtual bool handle(Event *event) override;

    WindowType *window_;
};

} // namespace Event

#include "EventHandler-inl.hpp"

#endif // MODELVIEWER_EVENT_HANDLER_HPP_

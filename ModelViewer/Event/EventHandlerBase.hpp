#ifndef MODELVIEWER_EVENT_HANDLERBASE_HPP_
#define MODELVIEWER_EVENT_HANDLERBASE_HPP_

namespace Event
{

class Event;

class EventHandlerBase
{
public:
    explicit EventHandlerBase();

    EventHandlerBase(const EventHandlerBase &other);
    EventHandlerBase(EventHandlerBase &&other) noexcept;
    EventHandlerBase &operator=(const EventHandlerBase &other);
    EventHandlerBase &operator=(EventHandlerBase &&other) noexcept;

    virtual ~EventHandlerBase();

    virtual bool handle(Event *event) = 0;
};

} // namespace Event

#endif // MODELVIEWER_EVENT_HANDLERBASE_HPP_

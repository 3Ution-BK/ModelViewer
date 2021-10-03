namespace Event
{

template <typename WindowType, typename EventType,
          void (WindowType::*respondFunction)(EventType *)>
EventHandler<WindowType, EventType, respondFunction>::EventHandler(
    WindowType &window)
    : window_{&window}
{
}

template <typename WindowType, typename EventType,
          void (WindowType::*respondFunction)(EventType *)>
EventHandler<WindowType, EventType, respondFunction>::EventHandler(
    const EventHandler<WindowType, EventType, respondFunction> &other) =
    default;

template <typename WindowType, typename EventType,
          void (WindowType::*respondFunction)(EventType *)>
EventHandler<WindowType, EventType, respondFunction>::EventHandler(
    EventHandler &&other) noexcept = default;

template <typename WindowType, typename EventType,
          void (WindowType::*respondFunction)(EventType *)>
EventHandler<WindowType, EventType, respondFunction> &
EventHandler<WindowType, EventType, respondFunction>::operator=(
    const EventHandler &other) = default;

template <typename WindowType, typename EventType,
          void (WindowType::*respondFunction)(EventType *)>
EventHandler<WindowType, EventType, respondFunction> &
EventHandler<WindowType, EventType, respondFunction>::operator=(
    EventHandler &&other) noexcept = default;

template <typename WindowType, typename EventType,
          void (WindowType::*respondFunction)(EventType *)>
EventHandler<WindowType, EventType, respondFunction>::~EventHandler() = default;

template <typename WindowType, typename EventType,
          void (WindowType::*respondFunction)(EventType *)>
bool EventHandler<WindowType, EventType, respondFunction>::handle(Event *event)
{
    if (auto e{dynamic_cast<EventType *>(event)})
    {
        (window_->*respondFunction)(e);
        return true;
    }
    return false;
}

} // namespace Event

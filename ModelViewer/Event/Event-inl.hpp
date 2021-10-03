namespace Event
{

inline void Event::setTimestamp(Event::TimeType t) { timestamp_ = t; }

inline Event::TimeType Event::timestamp() const { return timestamp_; }

inline const GLFWwindow *Event::window() const { return window_; }

} // namespace Event

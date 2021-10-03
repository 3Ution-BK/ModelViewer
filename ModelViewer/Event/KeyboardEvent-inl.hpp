namespace Event
{

inline InputAction KeyboardEvent::action() const { return action_; }

inline int KeyboardEvent::scanCode() const { return scanCode_; }

inline KeyboardCode KeyboardEvent::key() const { return key_; }

} // namespace Event

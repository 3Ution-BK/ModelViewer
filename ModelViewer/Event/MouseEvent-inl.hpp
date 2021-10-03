namespace Event
{

inline InputAction MouseEvent::action() const { return action_; }

inline MouseCode MouseEvent::button() const { return button_; }

inline MouseEvent::PositionType MouseEvent::position() const
{
    return position_;
}

} // namespace Event

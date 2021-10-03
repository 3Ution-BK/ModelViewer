namespace Event
{

inline MoveEvent::PositionType MoveEvent::oldPosition() const
{
    return oldPosition_;
}

inline MoveEvent::PositionType MoveEvent::position() const { return position_; }

} // namespace Event

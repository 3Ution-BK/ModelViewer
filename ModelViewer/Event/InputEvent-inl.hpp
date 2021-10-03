namespace Event
{

inline InputModifierFlags InputEvent::modifier() const { return modifier_; }

inline void InputEvent::setModifier(InputModifierFlags m) { modifier_ = m; }

} // namespace Event

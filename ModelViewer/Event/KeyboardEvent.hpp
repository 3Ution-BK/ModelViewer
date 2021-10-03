#ifndef MODELVIEWER_EVENT_KEYBOARDEVENT_HPP_
#define MODELVIEWER_EVENT_KEYBOARDEVENT_HPP_

#include "InputAction.hpp"
#include "InputEvent.hpp"
#include "KeyboardCode.hpp"

namespace Event
{

class KeyboardEvent : public InputEvent
{
public:
    explicit KeyboardEvent(int key, int action, int scanCode,
                           TimeType timestamp, const GLFWwindow *window,
                           int modifier = 0);

    explicit KeyboardEvent(
        KeyboardCode key, InputAction action, int scanCode, TimeType timestamp,
        const GLFWwindow *window,
        InputModifierFlags modifier = InputModifierFlags::NoModifier);

    KeyboardEvent(KeyboardEvent &&other) noexcept;
    KeyboardEvent &operator=(KeyboardEvent &&other) noexcept;
    virtual ~KeyboardEvent() override;

    KeyboardEvent(const KeyboardEvent &other) = delete;
    KeyboardEvent &operator=(const KeyboardEvent &other) = delete;

    inline KeyboardCode key() const;
    inline int scanCode() const;
    inline InputAction action() const;

protected:
    KeyboardCode key_;
    int scanCode_;
    InputAction action_;
};

} // namespace Event

#include "KeyboardEvent-inl.hpp"

#endif // MODELVIEWER_EVENT_KEYBOARDEVENT_HPP_

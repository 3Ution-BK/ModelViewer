#ifndef MODELVIEWER_EVENT_MOUSEEVENT_HPP_
#define MODELVIEWER_EVENT_MOUSEEVENT_HPP_

#include "InputAction.hpp"
#include "InputEvent.hpp"
#include "MouseCode.hpp"

#include "glm/vec2.hpp"

namespace Event
{

class MouseEvent : public InputEvent
{
public:
    using PositionType = glm::dvec2;

    explicit MouseEvent(int button, const PositionType &position, int action,
                        Event::TimeType timestamp, const GLFWwindow *window,
                        int modifier = 0);

    explicit MouseEvent(
        MouseCode button, const PositionType &position, InputAction action,
        Event::TimeType timestamp, const GLFWwindow *window,
        InputModifierFlags modifier = InputModifierFlags::NoModifier);

    MouseEvent(MouseEvent &&other) noexcept;
    MouseEvent &operator=(MouseEvent &&other) noexcept;
    virtual ~MouseEvent() override;

    MouseEvent(const MouseEvent &other) = delete;
    MouseEvent &operator=(const MouseEvent &other) = delete;

    inline MouseCode button() const;
    inline InputAction action() const;
    inline PositionType position() const;

protected:
    MouseCode button_;
    InputAction action_;
    PositionType position_;
};

} // namespace Event

#include "MouseEvent-inl.hpp"

#endif // MODELVIEWER_EVENT_MOUSEEVENT_HPP_

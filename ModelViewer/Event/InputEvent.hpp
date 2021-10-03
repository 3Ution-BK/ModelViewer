#ifndef MODELVIEWER_INPUT_INPUTEVENT_HPP_
#define MODELVIEWER_INPUT_INPUTEVENT_HPP_

#include "Event.hpp"

#include "InputModifierFlags.hpp"

#include "OpenGL/OpenGLLib.hpp"

namespace Event
{

class InputEvent : public Event
{
public:
    explicit InputEvent(TimeType timestamp, const GLFWwindow *window = nullptr,
                        int modifier = 0);

    explicit InputEvent(
        TimeType timestamp, const GLFWwindow *window = nullptr,
        InputModifierFlags modifier = InputModifierFlags::NoModifier);

    InputEvent(InputEvent &&other) noexcept;
    InputEvent &operator=(InputEvent &&other) noexcept;
    virtual ~InputEvent() override;

    InputEvent(const InputEvent &other) = delete;
    InputEvent &operator=(const InputEvent &other) = delete;

    inline InputModifierFlags modifier() const;
    inline void setModifier(InputModifierFlags m);

protected:
    InputModifierFlags modifier_;
};

} // namespace Event

#include "InputEvent-inl.hpp"

#endif // MODELVIEWER_INPUT_INPUTEVENT_HPP_

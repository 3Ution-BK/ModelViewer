#ifndef MODELVIEWER_EVENT_MOVEEVENT_HPP_
#define MODELVIEWER_EVENT_MOVEEVENT_HPP_

#include "Event.hpp"

#include "glm\vec2.hpp"

namespace Event
{

class MoveEvent : public Event
{
public:
    using PositionType = glm::ivec2;

    explicit MoveEvent(const PositionType &position,
                       const PositionType &oldPosition, TimeType timestamp,
                       const GLFWwindow *window = nullptr);

    MoveEvent(MoveEvent &&other) noexcept;
    MoveEvent &operator=(MoveEvent &&other) noexcept;
    virtual ~MoveEvent() override;

    inline PositionType position() const;
    inline PositionType oldPosition() const;

protected:
    PositionType position_;
    PositionType oldPosition_;

private:
    MoveEvent(const MoveEvent &other) = delete;
    MoveEvent &operator=(const MoveEvent &other) = delete;
};

} // namespace Event

#include "MoveEvent-inl.hpp"

#endif // MODELVIEWER_EVENT_MOVEEVENT_HPP_

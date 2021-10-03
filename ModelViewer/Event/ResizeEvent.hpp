#ifndef MODELVIEWER_EVENT_RESIZEEVENT_HPP_
#define MODELVIEWER_EVENT_RESIZEEVENT_HPP_

#include "Event.hpp"

#include "glm/vec2.hpp"

namespace Event
{

class ResizeEvent : public Event
{
public:
    using SizeType = glm::ivec2;

    explicit ResizeEvent(const SizeType &size, const SizeType &oldSize,
                         TimeType timestamp,
                         const GLFWwindow *window = nullptr);

    ResizeEvent(ResizeEvent &&other) noexcept;
    ResizeEvent &operator=(ResizeEvent &&other) noexcept;
    virtual ~ResizeEvent() override;
    
    ResizeEvent(const ResizeEvent &other) = delete;
    ResizeEvent &operator=(const ResizeEvent &other) = delete;

    inline SizeType size() const;
    inline SizeType oldSize() const;

protected:
    SizeType size_;
    SizeType oldSize_;

};

class WindowResizeEvent : public ResizeEvent
{
    using ResizeEvent::ResizeEvent;
};

class FrameBufferResizeEvent : public ResizeEvent
{
    using ResizeEvent::ResizeEvent;
};

} // namespace Event

#include "ResizeEvent-inl.hpp"

#endif // MODELVIEWER_EVENT_RESIZEEVENT_HPP_

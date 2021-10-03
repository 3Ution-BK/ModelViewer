#ifndef MODELVIEWER_EVENT_EVENT_HPP_
#define MODELVIEWER_EVENT_EVENT_HPP_

#include "OpenGL/OpenGLLib.hpp"

namespace Event
{

class Event
{
public:
    using TimeType = uint64_t;

    explicit Event(TimeType timestamp, const GLFWwindow *window = nullptr);

    Event(Event &&other) noexcept;
    Event &operator=(Event &&other) noexcept;
    virtual ~Event();

    Event(const Event &other) = delete;
    Event &operator=(const Event &other) = delete;

    inline const GLFWwindow *window() const;

    inline TimeType timestamp() const;
    inline void setTimestamp(TimeType t);

protected:
    const GLFWwindow *window_;
    TimeType timestamp_;
};

} // namespace Event

#include "Event-inl.hpp"

#endif // MODELVIEWER_EVENT_EVENT_HPP_

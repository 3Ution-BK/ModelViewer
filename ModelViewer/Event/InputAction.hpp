#ifndef MODELVIEWER_EVENT_INPUTACTION_HPP_
#define MODELVIEWER_EVENT_INPUTACTION_HPP_

#include "OpenGL/OpenGLLib.hpp"

namespace Event
{

enum class InputAction : int
{
    Press = GLFW_PRESS,
    Release = GLFW_RELEASE,
    Repeat = GLFW_REPEAT
};

}

#endif // MODELVIEWER_EVENT_INPUTACTION_HPP_

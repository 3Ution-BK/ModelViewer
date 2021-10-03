#ifndef MODELVIEWER_INPUT_MOUSECODE_HPP_
#define MODELVIEWER_INPUT_MOUSECODE_HPP_

#include "OpenGL/OpenGLLib.hpp"

namespace Event
{

enum MouseCode
{
    Mouse1 = GLFW_MOUSE_BUTTON_1,      ///< Mouse button 1
    Mouse2 = GLFW_MOUSE_BUTTON_2,      ///< Mouse button 2
    Mouse3 = GLFW_MOUSE_BUTTON_3,      ///< Mouse button 3
    Mouse4 = GLFW_MOUSE_BUTTON_4,      ///< Mouse button 4
    Mouse5 = GLFW_MOUSE_BUTTON_5,      ///< Mouse button 5
    Mouse6 = GLFW_MOUSE_BUTTON_6,      ///< Mouse button 6
    Mouse7 = GLFW_MOUSE_BUTTON_7,      ///< Mouse button 7
    Mouse8 = GLFW_MOUSE_BUTTON_8,      ///< Mouse button 8
    Left = GLFW_MOUSE_BUTTON_LEFT,     ///< Left(Primary) mouse button.
    Right = GLFW_MOUSE_BUTTON_RIGHT,   ///< Right(Secondary) mouse button.
    Middle = GLFW_MOUSE_BUTTON_MIDDLE, ///< Middle(Third) mouse button.
    Last = GLFW_MOUSE_BUTTON_LAST
};

}

#endif // MODELVIEWER_INPUT_MOUSECODE_HPP_

#ifndef GLFWTUTORIAL_LOGGER_LOGGER_HPP_
#define GLFWTUTORIAL_LOGGER_LOGGER_HPP_

#include "OpenGL/OpenGLLib.hpp"

#include <iostream>
#include <ostream>
#include <string>

namespace Logger
{

void APIENTRY openGLDebugOutput(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam);

} // namespace Logger

#endif // GLFW-TUTORIAL_LOGGER_LOGGER_HPP_

#ifndef MODELVIEWER_OPENGL_OPENGLLIB_HPP_
#define MODELVIEWER_OPENGL_OPENGLLIB_HPP_

/*
 * OpenGL header should be the first import library among anyone else. We
 * decided to put it here since OpenGLWindow is the main entrypoint.
 *
 * Be warned that "glad" should be forward than "glfw".
 */
#include "glad/glad.h"

#include "GLFW/glfw3.h"

#endif // MODELVIEWER_OPENGL_OPENGLLIB_HPP_

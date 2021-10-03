#ifndef MODELVIEWER_WINDOW_HPP_
#define MODELVIEWER_WINDOW_HPP_

#include "OpenGL/OpenGLLib.hpp"

#include "Event/Event.hpp"
#include "Event/KeyboardEvent.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/MoveEvent.hpp"
#include "Event/ResizeEvent.hpp"
#include "Model/Mesh.hpp"
#include "OpenGL/OpenGLShaderProgram.hpp"
#include "OpenGL/OpenGLTexture.hpp"

#include "glm/vec2.hpp"

#include <memory>

class OpenGLWindowBuilder;

/**
 * \brief This class represents the OpenGLWindow.
 *
 * This class represent the OpenGL window. User can try to render the scene in
 * this application.
 *
 * \sa OpenGLWindowBuilder
 */
class OpenGLWindow final
{
public:
    /**
     * \brief Initializes a new instance of the OpenGLWindow class.
     *
     * \param builder Specified OpenGLWindowBuilder.
     *
     * \throw OpenGL::OpenGLException Failed to initialize OpenGL.
     * \throw OpenGL::OpenGLException Failed to create GLFW window.
     * \throw OpenGL::OpenGLException Failed to initialize GLAD.
     */
    explicit OpenGLWindow(const OpenGLWindowBuilder &builder);
    ~OpenGLWindow();

    OpenGLWindow(OpenGLWindow &&other) = delete;
    OpenGLWindow &operator=(OpenGLWindow &&other) = delete;
    OpenGLWindow(const OpenGLWindow &other) = delete;
    OpenGLWindow &operator=(const OpenGLWindow &other) = delete;

    /**
     * \brief Add model to this scene.
     *
     * \param modelSource Source of the model.
     * \param textureSource Texture of the model.
     * \param program ShaderProgram of the render process for this model.
     * \return Return \c true if the model is successfully loaded into the
     * scene. Otherwise, return \c false.
     */
    bool addModel(const char *modelSource, const char *textureSource,
                  OpenGL::OpenGLShaderProgram &program);

    /**
     * \brief Add shader to the scene.
     *
     * \param vertexShaderSource Source of the vertex shader.
     * \param fragmentShaderSource Source of the fragment shader.
     * \param geometryShaderSource Source of the geometry shader.
     * \return Requested shader program. Return nullptr if the program failed to
     * instantiate.
     */
    OpenGL::OpenGLShaderProgram *
    addShader(const char *vertexShaderSource, const char *fragmentShaderSource,
              const char *geometryShaderSource = nullptr);

    /**
     * \brief Start render the scene.
     */
    void startRender();

    /**
     * \brief Get the position of the OpenGLWindow.
     *
     * \return glm::ivec2
     */
    glm::ivec2 windowPosition() const;

    /**
     * \brief Sets the window position of the OpenGLWindow.
     *
     * \param position Specified window position.
     */
    void setWindowPosition(const glm::ivec2 &position);

    /**
     * \overload
     *
     * \param x Specified window position (x).
     * \param y Specified window position (y).
     */
    void setWindowPosition(int x, int y);

    /**
     * \brief Get the size of the OpenGLWindow.
     *
     * \return glm::ivec2
     */
    glm::ivec2 windowSize() const;

    /**
     * \brief Sets the window size of the OpenGLWindow.
     *
     * \param position Specified window size.
     */
    void setWindowSize(const glm::ivec2 &size);

    /**
     * \overload
     *
     * \param width Specified window width.
     * \param height Specified window height.
     */
    void setWindowSize(int width, int height);

    /**
     * \brief Get the size of the OpenGLWindow frame buffer.
     *
     * \return glm::ivec2
     */
    glm::ivec2 frameBufferSize() const;

    /**
     * \brief Get the GLFWwindow of the OpenGLWindow.
     *
     * This function is used for communicate the function in glfw.
     *
     * \par Warning:
     * Do not delete the GLFWWindow instance by youself. This class will delete
     * it when it destruct.
     * It will cause the program to crash if you delete it outside. You have
     * been warned.
     *
     * \return Specified GLFWwindow.
     */
    GLFWwindow &window();

    /**
     * \overload
     *
     * \return Specified GLFWwindow.
     */
    const GLFWwindow &window() const;

    /**
     * \brief Push the event to event queue.
     *
     * \param event Specified event.
     */
    void pushEvent(std::unique_ptr<Event::Event> &&event);

    /**
     * \brief EventHandler when framebuffer is resized.
     *
     * \param event Specified event
     */
    void frameBufferResizeEvent(Event::FrameBufferResizeEvent *event);

    /**
     * \brief EventHandler when keyboard is triggered.
     *
     * \param event Specified event
     */
    void keyboardEvent(Event::KeyboardEvent *event);

    /**
     * \brief EventHandler when mouse is triggered.
     *
     * \param event Specified event
     */
    void mouseEvent(Event::MouseEvent *event);

    /**
     * \brief EventHandler when window is moved.
     *
     * \param event Specified event
     */
    void windowMoveEvent(Event::MoveEvent *event);

    /**
     * \brief EventHandler when window is resized.
     *
     * \param event Specified event
     */
    void windowResizeEvent(Event::WindowResizeEvent *event);

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

#endif // MODELVIEWER_WINDOW_HPP_

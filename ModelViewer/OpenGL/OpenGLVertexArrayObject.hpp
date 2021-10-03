#ifndef GLFWTUTORIAL_OPENGL_VERTEXARRAYOBJECT_HPP_
#define GLFWTUTORIAL_OPENGL_VERTEXARRAYOBJECT_HPP_

#include "OpenGLLib.hpp"

#include <memory>

namespace OpenGL
{

/**
 * \brief This class represents the OpenGL vertex array object.
 *
 * \par Warning:
 * This class is not thread safe. Please use it under the same thread which
 * creates OpenGL content.
 */
class OpenGLVertexArrayObject
{
public:
    /**
     * \brief Initializes a new instance of the OpenGL Vertex Array Object
     * class.
     *
     * \exception OpenGLException Buffer failed to instantiate.
     */
    explicit OpenGLVertexArrayObject();

    /**
     * \brief Initializes a new instance of the OpenGLVertexArrayObject class
     * with the content of \p other.
     *
     * \param other Another object to assign with.
     */
    OpenGLVertexArrayObject(OpenGLVertexArrayObject &&other) noexcept;

    /**
     * \brief Initializes a new instance of the OpenGLVertexArrayObject class
     * with the content of \p other.
     *
     * \param other Another object to assign with.
     */
    OpenGLVertexArrayObject &
    operator=(OpenGLVertexArrayObject &&other) noexcept;

    /**
     * \brief Destroy the instance of the OpenGLVertexArrayObject class.
     */
    ~OpenGLVertexArrayObject();

    OpenGLVertexArrayObject(const OpenGLVertexArrayObject &other) = delete;
    OpenGLVertexArrayObject &
    operator=(const OpenGLVertexArrayObject &other) = delete;

    /**
     * \brief Bind the OpenGLVertexArrayObject to the current OpenGL content.
     *
     * \sa release
     */
    void bind() noexcept;

    /**
     * \brief Release the OpenGLVertexArrayObject from the current OpenGL
     * content.
     *
     * \par Note:
     * You don't need to call this function if you want to switch to another
     * OpenGLVertexArrayObject. It will automatically release if another
     * OpenGLVertexArrayObject is binding.
     * \code{.cpp}
     * bufferFoo.bind();
     * // bufferFoo.release(); No need to call this function
     * bufferBar.bind();
     * bufferBar.release();
     * \endcode
     *
     * \sa bind
     */
    void release() noexcept;

    /**
     * \brief Gets the id of the OpenGLVertexArrayObject
     *
     * \return The id value.
     */
    GLuint id() const noexcept;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

} // namespace OpenGL

#endif // GLFWTUTORIAL_OPENGL_VERTEXARRAYOBJECT_HPP_

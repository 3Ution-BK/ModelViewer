#ifndef GLFWTUTORIAL_OPENGL_SHADERPROGRAM_HPP_
#define GLFWTUTORIAL_OPENGL_SHADERPROGRAM_HPP_

#include "OpenGLShader.hpp"

#include "OpenGLLib.hpp"

#include "glm/detail/qualifier.hpp"

#include <memory>

namespace OpenGL
{

/**
 * \brief This class represents the OpenGL shader program.
 *
 * \details OpenGLShaderProgram allow the compiled shader to be linked and use.
 *
 * \par Warning:
 * This class is not thread safe. Please use it under the same thread which
 * creates OpenGL content.
 *
 * \sa OpenGLShader
 */
class OpenGLShaderProgram
{
public:
    /**
     * \brief Initializes a new instance of the OpenGLShaderProgram class.
     *
     */
    explicit OpenGLShaderProgram();

    /**
     * \brief Initializes a new instance of the OpenGLShaderProgram class with
     * the content of \p other.
     *
     * \param other Another object to assign with.
     */
    OpenGLShaderProgram(OpenGLShaderProgram &&other) noexcept;

    /**
     * \brief Initializes a new instance of the OpenGLShaderProgram class with
     * the content of \p other.
     *
     * \param other Another object to assign with.
     */
    OpenGLShaderProgram &operator=(OpenGLShaderProgram &&other) noexcept;
    
    /**
     * \brief Destroy the instance of the OpenGLShaderProgram class.
     */
    ~OpenGLShaderProgram();

    /**
     * \brief Link the shaders in the OpenGLShaderProgram together.
     */
    void link() noexcept;

    /**
     * \brief Compile the source code of the \p fileName to the specified \p
     * type OpenGL::OpenGLShader and add it to the OpenGLShaderProgram.
     *
     * \param type Shader type.
     * \param fileName File name of the source code.
     * \return Return \c true If the shader is compile and add successfully.
     * Otherwise return \c false.
     *
     * \sa OpenGLShaderProgram::addShaderFromSource
     */
    bool addShaderFromFile(OpenGLShader::Type type,
                           const char *fileName) noexcept;

    /**
     * \brief Compile the \p source content to the specified \p type
     * OpenGL::OpenGLShader and add it to the OpenGLShaderProgram.
     *
     * \param type Shader type.
     * \param source Source code content.
     * \return Return \c true If the shader is compile and add successfully.
     * Otherwise return \c false.
     *
     * \sa OpenGLShaderProgram::addShaderFromFile
     */
    bool addShaderFromSource(OpenGLShader::Type type,
                             const char *source) noexcept;

    /**
     * \brief Disable the vertex attribute at \p index in the
     * OpenGLShaderProgram.
     *
     * \param index Given index.
     *
     * \sa OpenGLShaderProgram::enableAttributeArray
     */
    void disableAttributeArray(GLuint index) noexcept;

    /**
     * \brief Enable the vertex attribute at \p index in the
     * OpenGLShaderProgram.
     *
     * \param index Given index.
     *
     * \sa OpenGLShaderProgram::disableAttributeArray
     */
    void enableAttributeArray(GLuint index) noexcept;

    /**
     * \brief Set the location and format of the array of attributes at \p index
     * in OpenGLShaderProgram.
     *
     * \param index The index location of the shader.
     * \param size The number of components per attribute. Must be 1, 2, 3, 4.
     * \param type The data type of the array of the attribute. Normally will be
     * \c GL_BYTE, \c GL_UNSIGNED_BYTE, \c GL_SHORT, \c GL_UNSIGNED_SHORT, \c
     * GL_INT, and \c GL_UNSIGNED_INT.
     * \param normalized \c GL_TRUE if the fixed-point data values should be
     * normalized. Or \c GL_FALSE if the data values is convert directly.
     * \param stride The number of bytes between each attributes.
     * \param offset The number of bytes offset of the first attributes.
     */
    void mapAttributePointer(GLuint index, GLint size, GLenum type,
                             GLboolean normalized, GLsizei stride,
                             int offset) noexcept;

    /**
     * \brief Use the OpenGLShaderProgram to the current rendering state.
     */
    void use() noexcept;

    /**
     * @brief Set the uniform value with the given \p name to \p value.
     *
     * \tparam T Must be \c bool, \c int, \c unsigned int, and \c float type.
     * \param name The name of the specified value.
     * \param value Specified value.
     */
    template <typename T>
    void setValue(const char *name, T value) const noexcept;

    /**
     * \overload
     *
     * \brief Set the uniform value with the given \p name to vector( \p x, \p y
     * ).
     *
     * \tparam T T Must be \c int, \c unsigned int, and \c float type.
     * \param name The name of the specified value.
     * \param x Specified value of the x component.
     * \param y Specified value of the y component.
     */
    template <typename T>
    void setValue(const char *name, T x, T y) const noexcept;

    /**
     * \overload
     *
     * \brief Set the uniform value with the given \p name to \p vector.
     *
     * \tparam T T Must be \c int, \c unsigned int, and \c float type.
     * \param name The name of the specified value.
     * \param vector Specified value.
     */
    template <typename T>
    void setValue(const char *name, glm::vec<2, T> vector) const noexcept;

    /**
     * \overload
     *
     * \brief Set the uniform value with the given \p name to vector( \p x, \p y
     * \p z).
     *
     * \tparam T T Must be \c int, \c unsigned int, and \c float type.
     * \param name The name of the specified value.
     * \param x Specified value of the x component.
     * \param y Specified value of the y component.
     * \param z Specified value of the z component.
     */
    template <typename T>
    void setValue(const char *name, T x, T y, T z) const noexcept;

    /**
     * \overload
     *
     * \brief Set the uniform value with the given \p name to \p vector.
     *
     * \tparam T T Must be \c int, \c unsigned int, and \c float type.
     * \param name The name of the specified value.
     * \param vector Specified value.
     */
    template <typename T>
    void setValue(const char *name, glm::vec<3, T> vector) const noexcept;

    /**
     * \overload
     *
     * \brief Set the uniform value with the given \p name to vector( \p x, \p y
     * \p z).
     *
     * \tparam T T Must be \c int, \c unsigned int, and \c float type.
     * \param name The name of the specified value.
     * \param x Specified value of the x component.
     * \param y Specified value of the y component.
     * \param z Specified value of the z component.
     */
    template <typename T>
    void setValue(const char *name, T x, T y, T z, T w) const noexcept;

    /**
     * \overload
     *
     * \brief Set the uniform value with the given \p name to \p vector.
     *
     * \tparam T T Must be \c int, \c unsigned int, and \c float type.
     * \param name The name of the specified value.
     * \param vector Specified value.
     */
    template <typename T>
    void setValue(const char *name, glm::vec<4, T> vector) const noexcept;

    /**
     * \overload
     *
     * \brief Set the uniform value with the given \p name to \p matrix with or
     * without \p transpose.
     *
     * @tparam row Must be 2, 3, 4.
     * @tparam column Must be 2, 3, 4.
     * @param name The name of the specified value.
     * @param matrix Specified matrix.
     * @param transpose The matrix should be transpose or not.
     */
    template <int row, int column>
    void setValue(const char *name, glm::mat<row, column, float> matrix,
                  bool transpose) const noexcept;

    /**
     * \brief Gets the link status of the OpenGLShader
     *
     * \return Requested link status.
     */
    bool linkStatus() const noexcept;

    /**
     * \brief Gets the id of the OpenGLShader
     *
     * \return The id value.
     */
    GLuint id() const noexcept;

private:
    OpenGLShaderProgram(const OpenGLShaderProgram &other) = delete;
    OpenGLShaderProgram &operator=(const OpenGLShaderProgram &other) = delete;

    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

} // namespace OpenGL

#include "OpenGLShaderProgram-inl.hpp"

#endif // GLFWTUTORIAL_OPENGL_SHADERPROGRAM_HPP_

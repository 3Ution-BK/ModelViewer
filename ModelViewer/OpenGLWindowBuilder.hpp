#ifndef MODELVIEWER_OPENGLWINDOWBUILDER_HPP_
#define MODELVIEWER_OPENGLWINDOWBUILDER_HPP_

#include "OpenGLWindow.hpp"

#include "glm/vec2.hpp"

#include <memory>
#include <string>

/**
 * \brief This class represents the OpenGLWindow builder.
 *
 * This class tend to create the OpenGLWindow based on the builder pattern.
 * Set the required info to the builder and build it.
 *
 * \sa OpenGLWindow
 */
class OpenGLWindowBuilder
{
public:
    /**
     * \brief Initializes a new instance of the OpenGLWindowBuilder class.
     */
    explicit OpenGLWindowBuilder();

    /**
     * \brief Destroy the instance of the OpenGLWindowBuilder class.
     */
    ~OpenGLWindowBuilder();

    OpenGLWindowBuilder(const OpenGLWindowBuilder &other) = delete;
    OpenGLWindowBuilder(OpenGLWindowBuilder &&other) noexcept = delete;
    OpenGLWindowBuilder &operator=(const OpenGLWindowBuilder &other) = delete;
    OpenGLWindowBuilder &
    operator=(OpenGLWindowBuilder &&other) noexcept = delete;

    /**
     * \brief Sets the OpenGL version of the OpenGLWindow.
     *
     * \param version Specified OpenGL version.
     *
     * \return itself.
     */
    OpenGLWindowBuilder &setVersion(const glm::ivec2 &version);

    /**
     * \overload
     *
     * \param major Specified OpenGL version (major).
     * \param minor Specified OpenGL version (minor).
     *
     * \return itself.
     */
    OpenGLWindowBuilder &setVersion(int major, int minor);

    /**
     * \brief Sets the window position of the OpenGLWindow.
     *
     * \param position Specified window position.
     *
     * \return itself.
     */
    OpenGLWindowBuilder &setPosition(const glm::ivec2 &position);

    /**
     * \overload
     *
     * \param x Specified window position (x).
     * \param y Specified window position (y).
     *
     * \return itself.
     */
    OpenGLWindowBuilder &setPosition(int x, int y);

    /**
     * \brief Sets the size of the OpenGLWindow
     *
     * \param size Specified window size.
     * \return itself.
     */
    OpenGLWindowBuilder &setSize(const glm::ivec2 &size);

    /**
     * \overload
     *
     * \param width Specified window width.
     * \param height Specified window height.
     * \return itself.
     */
    OpenGLWindowBuilder &setSize(int width, int height);

    /**
     * \brief Sets the title of the OpenGLWindow
     *
     * \param title Specified title name
     * \return itself
     */
    OpenGLWindowBuilder &setTitle(const std::string &title);

    /**
     * \brief Reset all the setting to the default setting.
     */
    void reset();

    /**
     * \brief Get the OpenGL version of the product when this class build it.
     *
     * \return Requested value.
     */
    glm::ivec2 productVersion() const;

    /**
     * \brief Get the position of the product when this class build it.
     *
     * \return Requested value.
     */
    glm::ivec2 productPosition() const;

    /**
     * \brief Get the size of the product when this class build it.
     *
     * \return Requested value.
     */
    glm::ivec2 productSize() const;

    /**
     * \brief Get the title of the product when this class build it.
     *
     * \return Requested value.
     */
    std::string productTitle() const;

    /**
     * \brief Build the OpenGLWindow based on the setting. Reset the class
     * setting to default once the product is built.
     *
     * \return Product.
     */
    std::unique_ptr<OpenGLWindow> build();

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

#endif // MODELVIEWER_OPENGLWINDOWBUILDER_HPP_

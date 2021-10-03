#ifndef GLFWTUTORIAL_OPENGL_OPENGLTEXTURE_HPP_
#define GLFWTUTORIAL_OPENGL_OPENGLTEXTURE_HPP_

#include "OpenGLLib.hpp"

#include <memory>
#include <vector>

namespace OpenGL
{

class OpenGLTexture
{
public:
    enum Filter
    {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
        NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST,
        LinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST,
        NearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR,
        LinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR
    };

    enum WrapOption
    {
        Repeat = GL_REPEAT,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        ClampToEdge = GL_CLAMP_TO_EDGE,
        ClampTOBorder = GL_CLAMP_TO_BORDER
    };

    explicit OpenGLTexture();
    explicit OpenGLTexture(GLsizei width, GLsizei height, GLenum format,
                           const std::vector<unsigned char> &buffer,
                           Filter minificationFilter = Filter::Nearest,
                           Filter magnificationFilter = Filter::Linear,
                           WrapOption wrapOption = WrapOption::Repeat);
    OpenGLTexture(OpenGLTexture &&other) noexcept;
    OpenGLTexture &operator=(OpenGLTexture &&other) noexcept;
    ~OpenGLTexture();

    OpenGLTexture(const OpenGLTexture &other) = delete;
    OpenGLTexture &operator=(const OpenGLTexture &other) = delete;

    void bind();
    void release();

    GLenum format() const;
    GLsizei height() const;
    GLuint id() const;
    Filter magnificationFilter() const;
    Filter minificationFilter() const;
    GLsizei width() const;
    WrapOption wrapOption() const;

    void setMagnificationFilter(Filter filter);
    void setMinificationFilter(Filter filter);
    void setWrapOption(WrapOption option);

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

} // namespace OpenGL

#endif // GLFWTUTORIAL_OPENGL_OPENGLTEXTURE_HPP_

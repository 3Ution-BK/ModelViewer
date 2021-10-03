#include "OpenGLTexture.hpp"

#include "OpenGLException.hpp"
#include "Utils/PreDefine.hpp"

PRAGMA_WARNING_PUSH
PRAGMA_WARNING_DISABLE_DOUBLEPROMOTION

#include "stb_image.h"

PRAGMA_WARNING_POP

namespace OpenGL
{

namespace Detail
{

namespace Constant
{

constexpr GLuint noId{0};

} // namespace Constant

GLenum rgbFormat(int channels);

GLenum rgbFormat(int channels)
{
    switch (channels)
    {
    case 1:
        return GL_RED;
    case 2:
        return GL_RG;
    case 4:
        return GL_RGBA;
    case 3:
    default:
        return GL_RGB;
    }
}

} // namespace Detail

class OpenGLTexture::Impl
{
public:
    explicit Impl();
    explicit Impl(GLsizei width, GLsizei height, GLenum format,
                  const std::vector<unsigned char> &buffer,
                  Filter minificationFilter, Filter magnificationFilter,
                  WrapOption wrapOption);
    ~Impl();

    Impl(Impl &&other) noexcept = delete;
    Impl &operator=(Impl &&other) noexcept = delete;
    Impl(const Impl &other) = delete;
    Impl &operator=(const Impl &other) = delete;

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
    void bindBuffer(const std::vector<unsigned char> &buffer) const;
    void create();
    void tidy();

    constexpr bool isCreated() const;

    GLuint id_;

    GLenum format_;
    GLsizei height_;
    GLsizei width_;

    GLuint mipmapCount_;

    Filter minificationFilter_;
    Filter magnificationFilter_;
    WrapOption wrapOption_;
};

OpenGLTexture::OpenGLTexture() : pimpl_{std::make_unique<Impl>()} {}

OpenGLTexture::OpenGLTexture(GLsizei width, GLsizei height, GLenum format,
                             const std::vector<unsigned char> &buffer,
                             Filter minificationFilter,
                             Filter magnificationFilter, WrapOption wrapOption)
    : pimpl_{std::make_unique<Impl>(width, height, format, buffer,
                                    minificationFilter, magnificationFilter,
                                    wrapOption)}
{
}

OpenGLTexture::OpenGLTexture(OpenGLTexture &&other) noexcept = default;

OpenGLTexture &
OpenGLTexture::operator=(OpenGLTexture &&other) noexcept = default;

OpenGLTexture::~OpenGLTexture() = default;

void OpenGLTexture::bind() { pimpl_->bind(); }

GLenum OpenGLTexture::format() const { return pimpl_->format(); }

GLsizei OpenGLTexture::height() const { return pimpl_->height(); }

GLuint OpenGLTexture::id() const { return pimpl_->id(); }

OpenGLTexture::Filter OpenGLTexture::magnificationFilter() const
{
    return pimpl_->magnificationFilter();
}

OpenGLTexture::Filter OpenGLTexture::minificationFilter() const
{
    return pimpl_->minificationFilter();
}

void OpenGLTexture::release() { pimpl_->release(); }

void OpenGLTexture::setMagnificationFilter(Filter filter)
{
    pimpl_->setMagnificationFilter(filter);
}

void OpenGLTexture::setMinificationFilter(Filter filter)
{
    pimpl_->setMinificationFilter(filter);
}

void OpenGLTexture::setWrapOption(WrapOption option)
{
    pimpl_->setWrapOption(option);
}

GLsizei OpenGLTexture::width() const { return pimpl_->width(); }

OpenGLTexture::WrapOption OpenGLTexture::wrapOption() const
{
    return pimpl_->wrapOption();
}

OpenGLTexture::Impl::Impl()
    : id_{Detail::Constant::noId}, format_{0}, height_{0}, width_{0},
      mipmapCount_{0}, minificationFilter_{Filter::Nearest},
      magnificationFilter_{Filter::Linear}, wrapOption_{WrapOption::Repeat}
{
}

OpenGLTexture::Impl::Impl(GLsizei width, GLsizei height, GLenum format,
                          const std::vector<unsigned char> &buffer,
                          Filter minificationFilter, Filter magnificationFilter,
                          WrapOption wrapOption)
    : id_{Detail::Constant::noId}, format_{format}, height_{height},
      width_{width}, minificationFilter_{minificationFilter},
      magnificationFilter_{magnificationFilter}, wrapOption_{wrapOption}
{
    create();

    bind();

    bindBuffer(buffer);
}

OpenGLTexture::Impl::~Impl() { tidy(); }

void OpenGLTexture::Impl::bind()
{
    PROGRAM_ASSERT(isCreated());

    glBindTexture(GL_TEXTURE_2D, id_);
}

void OpenGLTexture::Impl::bindBuffer(
    const std::vector<unsigned char> &buffer) const
{
    glBindTexture(GL_TEXTURE_2D, id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minificationFilter_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magnificationFilter_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapOption_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapOption_);

    glTexImage2D(GL_TEXTURE_2D, 0, format_, width_, height_, 0, format_,
                 GL_UNSIGNED_BYTE, buffer.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void OpenGLTexture::Impl::create()
{
    PROGRAM_ASSERT(!isCreated());

    glGenTextures(1, &id_);

    if (!isCreated())
    {
        throw OpenGLException(
            "OpenGLTexture instantiate failed at 'glGenTextures'.");
    }
}

GLenum OpenGLTexture::Impl::format() const { return format_; }

GLsizei OpenGLTexture::Impl::height() const { return height_; }

GLuint OpenGLTexture::Impl::id() const { return id_; }

constexpr bool OpenGLTexture::Impl::isCreated() const { return id_; }

OpenGLTexture::Filter OpenGLTexture::Impl::magnificationFilter() const
{
    return magnificationFilter_;
}

OpenGLTexture::Filter OpenGLTexture::Impl::minificationFilter() const
{
    return minificationFilter_;
}

void OpenGLTexture::Impl::release()
{
    PROGRAM_ASSERT(isCreated());

    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture::Impl::setMagnificationFilter(Filter filter)
{
    PROGRAM_ASSERT(isCreated());
    magnificationFilter_ = filter;

    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    release();
}

void OpenGLTexture::Impl::setMinificationFilter(Filter filter)
{
    PROGRAM_ASSERT(isCreated());
    minificationFilter_ = filter;

    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    release();
}

void OpenGLTexture::Impl::setWrapOption(WrapOption option)
{
    PROGRAM_ASSERT(isCreated());
    wrapOption_ = option;

    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, option);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, option);
    release();
}

void OpenGLTexture::Impl::tidy()
{
    PROGRAM_ASSERT(isCreated());

    glDeleteTextures(1, &id_);
    id_ = Detail::Constant::noId;
}

GLsizei OpenGLTexture::Impl::width() const { return width_; }

OpenGLTexture::WrapOption OpenGLTexture::Impl::wrapOption() const
{
    return wrapOption_;
}

} // namespace OpenGL

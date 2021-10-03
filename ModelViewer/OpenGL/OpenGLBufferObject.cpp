#include "OpenGLBufferObject.hpp"

#include "OpenGLException.hpp"
#include "Utils/PreDefine.hpp"

namespace OpenGL
{

namespace Detail
{

namespace Constant
{

constexpr GLuint noId{0};

} // namespace Constant

} // namespace Detail

class OpenGLBufferObject::Impl
{
public:
    explicit Impl(OpenGLBufferObject::Type type,
                  OpenGLBufferObject::UsagePattern usagePattern);
    ~Impl();

    Impl(const Impl &other) = delete;
    Impl &operator=(const Impl &other) = delete;
    Impl(Impl &&other) noexcept = delete;
    Impl &operator=(Impl &&other) noexcept = delete;

    void allocateBufferData(const void *data, GLsizeiptr size) noexcept;
    void bind() noexcept;
    void release() noexcept;

    GLuint id() const noexcept;
    OpenGLBufferObject::Type type() const;
    OpenGLBufferObject::UsagePattern usagePattern() const;

private:
    void create();
    void tidy();

    constexpr bool isCreated() const;

    GLuint id_;

    OpenGLBufferObject::Type type_;
    OpenGLBufferObject::UsagePattern usagePattern_;
};

OpenGLBufferObject::OpenGLBufferObject(
    OpenGLBufferObject::Type type,
    OpenGLBufferObject::UsagePattern usagePattern)
    : pimpl_{std::make_unique<Impl>(type, usagePattern)}
{
}

OpenGLBufferObject::OpenGLBufferObject(OpenGLBufferObject &&other) noexcept =
    default;

OpenGLBufferObject &
OpenGLBufferObject::operator=(OpenGLBufferObject &&other) noexcept = default;

OpenGLBufferObject::~OpenGLBufferObject() = default;

void OpenGLBufferObject::allocateBufferData(const void *data,
                                            GLsizeiptr size) noexcept
{
    pimpl_->allocateBufferData(data, size);
}

void OpenGLBufferObject::bind() noexcept { pimpl_->bind(); }

void OpenGLBufferObject::release() noexcept { pimpl_->release(); }

GLuint OpenGLBufferObject::id() const noexcept { return pimpl_->id(); }

OpenGLBufferObject::Type OpenGLBufferObject::type() const
{
    return pimpl_->type();
}

OpenGLBufferObject::UsagePattern OpenGLBufferObject::usagePattern() const
{
    return pimpl_->usagePattern();
}

OpenGLBufferObject::Impl::Impl(OpenGLBufferObject::Type type,
                               OpenGLBufferObject::UsagePattern usagePattern)
    : id_{Detail::Constant::noId}, type_{type}, usagePattern_{usagePattern}
{
    create();
}

OpenGLBufferObject::Impl::~Impl() { tidy(); }

void OpenGLBufferObject::Impl::allocateBufferData(const void *data,
                                                  GLsizeiptr size) noexcept
{
    PROGRAM_ASSERT(isCreated());

    glBufferData(type_, size, data, usagePattern_);
}

void OpenGLBufferObject::Impl::bind() noexcept
{
    PROGRAM_ASSERT(isCreated());

    glBindBuffer(type_, id_);
}

void OpenGLBufferObject::Impl::create()
{
    PROGRAM_ASSERT(!isCreated());

    glGenBuffers(1, &id_);

    if (!isCreated())
    {
        throw OpenGLException(
            "OpenGLBufferObject instantiate failed at 'glGenBuffers'.");
    }
}

GLuint OpenGLBufferObject::Impl::id() const noexcept { return id_; }

constexpr bool OpenGLBufferObject::Impl::isCreated() const { return id_; }

void OpenGLBufferObject::Impl::release() noexcept
{
    PROGRAM_ASSERT(isCreated());

    glBindBuffer(type_, 0);
}

void OpenGLBufferObject::Impl::tidy()
{
    PROGRAM_ASSERT(isCreated());

    glDeleteBuffers(1, &id_);
    id_ = Detail::Constant::noId;
}

OpenGLBufferObject::Type OpenGLBufferObject::Impl::type() const
{
    return type_;
}

OpenGLBufferObject::UsagePattern OpenGLBufferObject::Impl::usagePattern() const
{
    return usagePattern_;
}

} // namespace OpenGL

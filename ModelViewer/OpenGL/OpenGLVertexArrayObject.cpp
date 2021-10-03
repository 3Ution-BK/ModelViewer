#include "OpenGLVertexArrayObject.hpp"

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

class OpenGLVertexArrayObject::Impl
{
public:
    explicit Impl();
    ~Impl();

    Impl(Impl &&other) noexcept = delete;
    Impl &operator=(Impl &&other) noexcept = delete;
    Impl(const Impl &other) = delete;
    Impl &operator=(const Impl &other) = delete;

    void bind() noexcept;
    void release() noexcept;

    GLuint id() const noexcept;

private:
    void create();
    void tidy();

    constexpr bool isCreated() const;

    GLuint id_;
};

OpenGLVertexArrayObject::OpenGLVertexArrayObject()
    : pimpl_{std::make_unique<Impl>()}
{
}

OpenGLVertexArrayObject::OpenGLVertexArrayObject(
    OpenGLVertexArrayObject &&other) noexcept = default;

OpenGLVertexArrayObject &OpenGLVertexArrayObject::operator=(
    OpenGLVertexArrayObject &&other) noexcept = default;

OpenGLVertexArrayObject::~OpenGLVertexArrayObject() = default;

void OpenGLVertexArrayObject::bind() noexcept { pimpl_->bind(); }

GLuint OpenGLVertexArrayObject::id() const noexcept { return pimpl_->id(); }

void OpenGLVertexArrayObject::release() noexcept { pimpl_->release(); }

OpenGLVertexArrayObject::Impl::Impl() : id_{Detail::Constant::noId}
{
    create();
}

OpenGLVertexArrayObject::Impl::~Impl() { tidy(); }

void OpenGLVertexArrayObject::Impl::bind() noexcept
{
    PROGRAM_ASSERT(isCreated());

    glBindVertexArray(id_);
}

void OpenGLVertexArrayObject::Impl::create()
{
    PROGRAM_ASSERT(!isCreated());

    glGenVertexArrays(1, &id_);

    if (!isCreated())
    {
        throw OpenGLException("OpenGLVertexArrayObject instantiate failed at "
                              "'glGenVertexArrays'.");
    }
}

GLuint OpenGLVertexArrayObject::Impl::id() const noexcept { return id_; }

constexpr bool OpenGLVertexArrayObject::Impl::isCreated() const { return id_; }

void OpenGLVertexArrayObject::Impl::release() noexcept
{
    PROGRAM_ASSERT(isCreated());

    glBindVertexArray(Detail::Constant::noId);
}

void OpenGLVertexArrayObject::Impl::tidy()
{
    PROGRAM_ASSERT(isCreated());

    glDeleteVertexArrays(1, &id_);
    id_ = Detail::Constant::noId;
}

} // namespace OpenGL

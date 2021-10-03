#include "OpenGLShader.hpp"

#include "OpenGLException.hpp"

#include "FileIO/FileIn.hpp"
#include "Utils/PreDefine.hpp"

#include <cstring>

#include <string>

namespace OpenGL
{

namespace Detail
{

namespace Constant
{

constexpr GLuint noId{0};

} // namespace Constant

} // namespace Detail

class OpenGLShader::Impl
{
public:
    explicit Impl(OpenGLShader::Type type);
    ~Impl();

    Impl(Impl &&other) noexcept = delete;
    Impl &operator=(Impl &&other) noexcept = delete;
    Impl(const Impl &other) = delete;
    Impl &operator=(const Impl &other) = delete;

    bool compileFromFile(const char *fileName) noexcept;

    bool compileFromSource(const char *source) noexcept;

    GLuint id() const noexcept;

    OpenGLShader::Type type() const noexcept;

private:
    void create();
    void tidy();

    bool compileStatus() const;

    constexpr bool isCreated() const;
    constexpr GLenum typeCode() const;

    GLuint id_;
    OpenGLShader::Type type_;
};

OpenGLShader::OpenGLShader(OpenGLShader::Type type)
    : pimpl_{std::make_unique<Impl>(type)}
{
}

OpenGLShader::OpenGLShader(OpenGLShader &&other) noexcept = default;

OpenGLShader &OpenGLShader::operator=(OpenGLShader &&other) noexcept = default;

OpenGLShader::~OpenGLShader() = default;

bool OpenGLShader::compileFromFile(const char *fileName) noexcept
{
    return pimpl_->compileFromFile(fileName);
}

bool OpenGLShader::compileFromSource(const char *source) noexcept
{
    return pimpl_->compileFromSource(source);
}

GLuint OpenGLShader::id() const noexcept { return pimpl_->id(); }

OpenGLShader::Type OpenGLShader::type() const noexcept
{
    return pimpl_->type();
}

OpenGLShader::Impl::Impl(OpenGLShader::Type type)
    : id_{Detail::Constant::noId}, type_{type}
{
    create();
}

OpenGLShader::Impl::~Impl() { tidy(); }

bool OpenGLShader::Impl::compileFromFile(const char *fileName) noexcept
{
    std::string source{FileIO::ReadFileFullText(fileName)};

    return compileFromSource(source.c_str());
}

bool OpenGLShader::Impl::compileFromSource(const char *source) noexcept
{
    PROGRAM_ASSERT(isCreated());

    glShaderSource(id_, 1, &source, NULL);
    glCompileShader(id_);

    return compileStatus();
}

bool OpenGLShader::Impl::compileStatus() const
{
    GLint status;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &status);

    return (status == GL_TRUE);
}

void OpenGLShader::Impl::create()
{
    PROGRAM_ASSERT(!isCreated());

    id_ = glCreateShader(typeCode());

    if (!isCreated())
    {
        throw OpenGLException(
            "OpenGLShader instantiate failed at 'glCreateShader'.");
    }
}

GLuint OpenGLShader::Impl::id() const noexcept { return id_; }

constexpr bool OpenGLShader::Impl::isCreated() const { return id_; }

void OpenGLShader::Impl::tidy()
{
    PROGRAM_ASSERT(isCreated());

    glDeleteShader(id_);
    id_ = Detail::Constant::noId;
}

OpenGLShader::Type OpenGLShader::Impl::type() const noexcept { return type_; }

constexpr GLenum OpenGLShader::Impl::typeCode() const
{
    switch (type_)
    {
    case Vertex:
        return GL_VERTEX_SHADER;
    case Fragment:
        return GL_FRAGMENT_SHADER;
    case Geometry:
        return GL_GEOMETRY_SHADER;
    default:
        PROGRAM_UNREACHABLE;
    }
}

} // namespace OpenGL

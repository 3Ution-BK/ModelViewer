#include "OpenGLShaderProgram.hpp"

#include "OpenGLException.hpp"

#include "Utils/PreDefine.hpp"

#include <iostream>
#include <memory>
#include <vector>

namespace OpenGL
{

namespace Detail
{

namespace Constant
{

constexpr GLuint noId{0};

} // namespace Constant

} // namespace Detail

class OpenGLShaderProgram::Impl
{
public:
    explicit Impl();
    ~Impl();

    Impl(Impl &&other) noexcept = delete;
    Impl &operator=(Impl &&other) noexcept = delete;
    Impl(const Impl &other) = delete;
    Impl &operator=(const Impl &other) = delete;

    void link() noexcept;

    bool addShaderFromFile(OpenGLShader::Type type,
                           const char *fileName) noexcept;
    bool addShaderFromSource(OpenGLShader::Type type,
                             const char *source) noexcept;

    void disableAttributeArray(GLuint index) noexcept;
    void enableAttributeArray(GLuint index) noexcept;

    void mapAttributePointer(GLuint index, GLint size, GLenum type,
                             GLboolean normalized, GLsizei stride,
                             int offset) noexcept;

    bool linkStatus() const noexcept;

    void use() noexcept;

    GLuint id() const noexcept;

private:
    void attachShader(std::unique_ptr<OpenGLShader> &&shader);

    void create();
    void tidy();
    void destroyProgram();
    void destroyShaders();

    constexpr bool isCreated() const;

    GLuint id_;

    std::vector<std::unique_ptr<OpenGLShader>> shaders_;
};

OpenGLShaderProgram::OpenGLShaderProgram() : pimpl_{std::make_unique<Impl>()} {}

OpenGLShaderProgram::OpenGLShaderProgram(OpenGLShaderProgram &&other) noexcept =
    default;

OpenGLShaderProgram &
OpenGLShaderProgram::operator=(OpenGLShaderProgram &&other) noexcept = default;

OpenGLShaderProgram::~OpenGLShaderProgram() = default;

bool OpenGLShaderProgram::addShaderFromFile(OpenGLShader::Type type,
                                            const char *fileName) noexcept
{
    return pimpl_->addShaderFromFile(type, fileName);
}

bool OpenGLShaderProgram::addShaderFromSource(OpenGLShader::Type type,
                                              const char *source) noexcept
{
    return pimpl_->addShaderFromSource(type, source);
}

void OpenGLShaderProgram::disableAttributeArray(GLuint index) noexcept
{
    pimpl_->disableAttributeArray(index);
}

void OpenGLShaderProgram::enableAttributeArray(GLuint index) noexcept
{
    pimpl_->enableAttributeArray(index);
}

GLuint OpenGLShaderProgram::id() const noexcept { return pimpl_->id(); }

void OpenGLShaderProgram::link() noexcept { pimpl_->link(); }

bool OpenGLShaderProgram::linkStatus() const noexcept
{
    return pimpl_->linkStatus();
}

void OpenGLShaderProgram::mapAttributePointer(GLuint index, GLint size,
                                              GLenum type, GLboolean normalized,
                                              GLsizei stride,
                                              int offset) noexcept
{
    pimpl_->mapAttributePointer(index, size, type, normalized, stride, offset);
}

void OpenGLShaderProgram::use() noexcept { pimpl_->use(); }

OpenGLShaderProgram::Impl::Impl() : id_{Detail::Constant::noId} { create(); }

OpenGLShaderProgram::Impl::~Impl() { tidy(); }

bool OpenGLShaderProgram::Impl::addShaderFromFile(OpenGLShader::Type type,
                                                  const char *fileName) noexcept
{
    PROGRAM_ASSERT(isCreated());

    try
    {
        std::unique_ptr<OpenGLShader> shader{
            std::make_unique<OpenGLShader>(type)};

        if (!shader->compileFromFile(fileName))
        {
            return false;
        }

        attachShader(std::move(shader));
    }
    catch (OpenGLException &e)
    {
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR,
                             Detail::Constant::noId, GL_DEBUG_SEVERITY_MEDIUM,
                             -1, e.what());

        return false;
    }

    return true;
}

bool OpenGLShaderProgram::Impl::addShaderFromSource(OpenGLShader::Type type,
                                                    const char *source) noexcept
{
    PROGRAM_ASSERT(isCreated());

    try
    {
        std::unique_ptr<OpenGLShader> shader{
            std::make_unique<OpenGLShader>(type)};

        if (!shader->compileFromSource(source))
        {
            return false;
        }

        attachShader(std::move(shader));
    }
    catch (OpenGLException &e)
    {
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR,
                             Detail::Constant::noId, GL_DEBUG_SEVERITY_MEDIUM,
                             -1, e.what());

        return false;
    }

    return true;
}

void OpenGLShaderProgram::Impl::attachShader(
    std::unique_ptr<OpenGLShader> &&shader)
{
    PROGRAM_ASSERT(isCreated());

    glAttachShader(id_, shader->id());
    shaders_.push_back(std::move(shader));
}

void OpenGLShaderProgram::Impl::create()
{
    PROGRAM_ASSERT(!isCreated());

    id_ = glCreateProgram();

    if (!isCreated())
    {
        throw OpenGLException(
            "OpenGLShaderProgram instantiate failed at 'glCreateProgram'.");
    }
}

void OpenGLShaderProgram::Impl::destroyProgram()
{
    PROGRAM_ASSERT(isCreated());

    glDeleteProgram(id_);
    id_ = Detail::Constant::noId;
}

void OpenGLShaderProgram::Impl::destroyShaders()
{
    PROGRAM_ASSERT(isCreated());

    for (auto &shader : shaders_)
    {
        glDetachShader(id_, shader->id());
    }

    shaders_.clear();
}

void OpenGLShaderProgram::Impl::disableAttributeArray(GLuint index) noexcept
{
    glDisableVertexAttribArray(index);
}

void OpenGLShaderProgram::Impl::enableAttributeArray(GLuint index) noexcept
{
    glEnableVertexAttribArray(index);
}

GLuint OpenGLShaderProgram::Impl::id() const noexcept { return id_; }

constexpr bool OpenGLShaderProgram::Impl::isCreated() const { return id_; }

void OpenGLShaderProgram::Impl::link() noexcept { glLinkProgram(id_); }

bool OpenGLShaderProgram::Impl::linkStatus() const noexcept
{
    GLint status;
    glGetProgramiv(id_, GL_LINK_STATUS, &status);

    return (status == GL_TRUE);
}

void OpenGLShaderProgram::Impl::mapAttributePointer(GLuint index, GLint size,
                                                    GLenum type,
                                                    GLboolean normalized,
                                                    GLsizei stride,
                                                    int offset) noexcept
{
    glVertexAttribPointer(index, size, type, normalized, stride,
                          PROGRAM_BUFFER_OFFSET(offset));
}

void OpenGLShaderProgram::Impl::tidy()
{
    PROGRAM_ASSERT(isCreated());

    destroyShaders();
    destroyProgram();
}

void OpenGLShaderProgram::Impl::use() noexcept { glUseProgram(id_); }

} // namespace OpenGL

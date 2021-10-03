#include "Mesh.hpp"

#include "OpenGL/OpenGLException.hpp"
#include "Utils/PreDefine.hpp"

#include "OpenGL/OpenGLBufferObject.hpp"
#include "OpenGL/OpenGLVertexArrayObject.hpp"

namespace Model
{

namespace Mesh
{

class Mesh::Impl
{
public:
    using VertexArrayObjectType = OpenGL::OpenGLVertexArrayObject;
    using BufferObjectType = OpenGL::OpenGLBufferObject;

    explicit Impl() noexcept;
    explicit Impl(const std::vector<Vertex> &vertices,
                  const std::vector<IndexType> &indices,
                  std::shared_ptr<ShaderProgramType> shaderProgram,
                  std::shared_ptr<TextureType> texture = nullptr);

    Impl(Impl &&other) noexcept;
    Impl &operator=(Impl &&other) noexcept;
    ~Impl();

    Impl(const Impl &other) = delete;
    Impl &operator=(const Impl &other) = delete;

    void draw(const glm::mat4 &mvp);

private:
    void create(const std::vector<Vertex> &vertices,
                const std::vector<IndexType> &indices);

    void programMapAttribute(ShaderProgramType &program, GLuint index,
                             GLint size, GLenum type, GLboolean normalized,
                             GLsizei stride, int offset);

    std::shared_ptr<ShaderProgramType> shaderProgram_;
    std::shared_ptr<TextureType> texture_;

    std::unique_ptr<VertexArrayObjectType> vertexArrayObject_;
    std::unique_ptr<BufferObjectType> vertexBufferObject_;
    std::unique_ptr<BufferObjectType> elementBufferObject_;

    GLsizei indicesCount_;
};

Mesh::Mesh() noexcept : pimpl_{std::make_unique<Impl>()} {}

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<IndexType> &indices,
           std::shared_ptr<ShaderProgramType> shaderProgram,
           std::shared_ptr<TextureType> texture)
    : pimpl_{std::make_unique<Impl>(vertices, indices, shaderProgram, texture)}
{
}

Mesh::Mesh(Mesh &&other) noexcept = default;

Mesh &Mesh::operator=(Mesh &&other) noexcept = default;

Mesh::~Mesh() noexcept = default;

void Mesh::draw(const glm::mat4 &mvp) { pimpl_->draw(mvp); }

Mesh::Impl::Impl() noexcept
    : shaderProgram_{nullptr}, texture_{nullptr}, vertexArrayObject_{nullptr},
      vertexBufferObject_{nullptr}, elementBufferObject_{nullptr},
      indicesCount_{0}
{
}

Mesh::Impl::Impl(const std::vector<Vertex> &vertices,
                 const std::vector<IndexType> &indices,
                 std::shared_ptr<ShaderProgramType> shaderProgram,
                 std::shared_ptr<TextureType> texture)
    : shaderProgram_{shaderProgram}, texture_{texture},
      vertexArrayObject_{std::make_unique<VertexArrayObjectType>()},
      vertexBufferObject_{std::make_unique<BufferObjectType>(
          OpenGL::OpenGLBufferObject::Type::ArrayBuffer,
          OpenGL::OpenGLBufferObject::UsagePattern::StaticDraw)},
      elementBufferObject_{std::make_unique<BufferObjectType>(
          OpenGL::OpenGLBufferObject::Type::ElementArrayBuffer,
          OpenGL::OpenGLBufferObject::UsagePattern::StaticDraw)},
      indicesCount_{static_cast<GLsizei>(indices.size())}
{
    create(vertices, indices);
}

Mesh::Impl::Impl(Impl &&other) noexcept = default;

Mesh::Impl &Mesh::Impl::operator=(Impl &&other) noexcept = default;

Mesh::Impl::~Impl() noexcept = default;

void Mesh::Impl::create(const std::vector<Vertex> &vertices,
                        const std::vector<IndexType> &indices)
{
    vertexArrayObject_->bind();
    {
        vertexBufferObject_->bind();
        vertexBufferObject_->allocateBufferData(
            vertices.data(), sizeof(Vertex) * vertices.size());

        programMapAttribute(*shaderProgram_, 0, 3, GL_FLOAT, GL_FALSE,
                            sizeof(Vertex), offsetof(Vertex, position));

        programMapAttribute(*shaderProgram_, 1, 3, GL_FLOAT, GL_FALSE,
                            sizeof(Vertex), offsetof(Vertex, normal));

        programMapAttribute(*shaderProgram_, 2, 2, GL_FLOAT, GL_FALSE,
                            sizeof(Vertex),
                            offsetof(Vertex, textureCoordinate));

        elementBufferObject_->bind();
        elementBufferObject_->allocateBufferData(
            indices.data(), sizeof(IndexType) * indices.size());
    }
    vertexArrayObject_->release();
}

void Mesh::Impl::draw(const glm::mat4 &mvp)
{
    if (texture_)
    {
        glActiveTexture(GL_TEXTURE0);
        texture_->bind();
    }

    shaderProgram_->use();

    shaderProgram_->setValue("mvp", mvp, false);

    vertexArrayObject_->bind();
    glDrawElements(GL_TRIANGLES, indicesCount_, GL_UNSIGNED_INT, 0);
    vertexArrayObject_->release();

    if (texture_)
    {
        glActiveTexture(GL_TEXTURE0);
    }
}

void Mesh::Impl::programMapAttribute(ShaderProgramType &program, GLuint index,
                                     GLint size, GLenum type,
                                     GLboolean normalized, GLsizei stride,
                                     int offset)
{
    program.enableAttributeArray(index);
    program.mapAttributePointer(index, size, type, normalized, stride, offset);
}

} // namespace Mesh

} // namespace Model

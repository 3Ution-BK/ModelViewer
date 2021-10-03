#include "Mesh.hpp"

namespace Model
{

Mesh::Mesh() noexcept
    : shaderProgram_{nullptr}, texture_{nullptr}, vertexArrayObject_{nullptr},
      vertexBufferObject_{nullptr}, elementBufferObject_{nullptr},
      indicesCount_{0}, model_{1}
{
}

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<IndexType> &indices,
           ShaderProgramType &shaderProgram, TextureType *texture)
    : shaderProgram_{&shaderProgram}, texture_{texture},
      vertexArrayObject_{nullptr}, vertexBufferObject_{nullptr},
      elementBufferObject_{nullptr},
      indicesCount_{static_cast<GLsizei>(indices.size())}, model_{1}
{
    create(vertices, indices);
}

Mesh::Mesh(Mesh &&other) noexcept = default;

Mesh &Mesh::operator=(Mesh &&other) noexcept = default;

Mesh::~Mesh() noexcept = default;

void Mesh::create(const std::vector<Vertex> &vertices,
                  const std::vector<IndexType> &indices)
{
    vertexArrayObject_.reset(new VertexArrayObjectType{});
    vertexBufferObject_.reset(new BufferObjectType{
        OpenGL::OpenGLBufferObject::Type::ArrayBuffer,
        OpenGL::OpenGLBufferObject::UsagePattern::StaticDraw});
    elementBufferObject_.reset(new BufferObjectType{
        OpenGL::OpenGLBufferObject::Type::ElementArrayBuffer,
        OpenGL::OpenGLBufferObject::UsagePattern::StaticDraw});

    vertexArrayObject_->bind();

    vertexBufferObject_->bind();
    vertexBufferObject_->allocateBufferData(vertices.data(),
                                            sizeof(Vertex) * vertices.size());

    programMapAttribute(*shaderProgram_, 0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(Vertex), offsetof(Vertex, position));

    programMapAttribute(*shaderProgram_, 1, 3, GL_FLOAT, GL_FALSE,
                        sizeof(Vertex), offsetof(Vertex, normal));

    programMapAttribute(*shaderProgram_, 2, 2, GL_FLOAT, GL_FALSE,
                        sizeof(Vertex), offsetof(Vertex, textureCoordinate));

    elementBufferObject_->bind();
    elementBufferObject_->allocateBufferData(
        indices.data(), sizeof(IndexType) * indices.size());

    vertexArrayObject_->release();
}

void Mesh::draw(glm::mat4 &view, glm::mat4 &projection)
{
    if (!(texture_))
    {
        glActiveTexture(GL_TEXTURE0);
        texture_->bind();
    }

    shaderProgram_->use();

    glm::mat4 mvp{projection * view * model_};

    shaderProgram_->setValue<4, 4>("mvp", mvp, false);

    vertexArrayObject_->bind();
    glDrawElements(GL_TRIANGLES, indicesCount_, GL_UNSIGNED_INT, 0);
    vertexArrayObject_->release();

    if (!(texture_))
    {
        glActiveTexture(GL_TEXTURE0);
    }
}

void Mesh::programMapAttribute(ShaderProgramType &program, GLuint index,
                               GLint size, GLenum type, GLboolean normalized,
                               GLsizei stride, int offset)
{
    program.enableAttributeArray(index);
    program.mapAttributePointer(index, size, type, normalized, stride, offset);
}

} // namespace Model

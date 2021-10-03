#ifndef MODELVIEWER_MODEL_MESH_HPP_
#define MODELVIEWER_MODEL_MESH_HPP_

#include "OpenGL/OpenGLBufferObject.hpp"
#include "OpenGL/OpenGLShaderProgram.hpp"
#include "OpenGL/OpenGLTexture.hpp"
#include "OpenGL/OpenGLVertexArrayObject.hpp"
#include "Vertex.hpp"

#include "glm/mat4x4.hpp"

#include <array>
#include <memory>
#include <vector>

namespace Model
{

class Mesh
{
public:
    using IndexType = unsigned int;
    using TextureType = OpenGL::OpenGLTexture;
    using ShaderProgramType = OpenGL::OpenGLShaderProgram;

    explicit Mesh() noexcept;
    explicit Mesh(const std::vector<Vertex> &vertices,
                  const std::vector<IndexType> &indices,
                  ShaderProgramType &shaderProgram,
                  TextureType *texture = nullptr);

    Mesh(Mesh &&other) noexcept;
    Mesh &operator=(Mesh &&other) noexcept;
    ~Mesh();

    Mesh(const Mesh &other) = delete;
    Mesh &operator=(const Mesh &other) = delete;

    void draw(glm::mat4 &view, glm::mat4 &projection);

    glm::mat4 model();
    void setModel(glm::mat4 &model);

private:
    using VertexArrayObjectType = OpenGL::OpenGLVertexArrayObject;
    using BufferObjectType = OpenGL::OpenGLBufferObject;

    void create(const std::vector<Vertex> &vertices,
                const std::vector<IndexType> &indices);

    static void programMapAttribute(ShaderProgramType &program, GLuint index,
                                    GLint size, GLenum type,
                                    GLboolean normalized, GLsizei stride,
                                    int offset);

    ShaderProgramType *shaderProgram_;
    TextureType *texture_;

    std::unique_ptr<VertexArrayObjectType> vertexArrayObject_;
    std::unique_ptr<BufferObjectType> vertexBufferObject_;
    std::unique_ptr<BufferObjectType> elementBufferObject_;

    GLsizei indicesCount_;

    glm::mat4 model_;
};

} // namespace Model

#endif // MODELVIEWER_MODEL_MESH_HPP_

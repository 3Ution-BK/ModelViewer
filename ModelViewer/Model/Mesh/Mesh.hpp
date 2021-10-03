#ifndef MODELVIEWER_MODEL_MESH_MESH_HPP_
#define MODELVIEWER_MODEL_MESH_MESH_HPP_

#include "Model/IModelable.hpp"
#include "Vertex.hpp"

#include "OpenGL/OpenGLShaderProgram.hpp"
#include "OpenGL/OpenGLTexture.hpp"

#include "glm/mat4x4.hpp"

#include <memory>
#include <vector>

namespace Model
{

namespace Mesh
{

class Mesh : public IModelable
{
public:
    using IndexType = GLuint;
    using TextureType = OpenGL::OpenGLTexture;
    using ShaderProgramType = OpenGL::OpenGLShaderProgram;

    explicit Mesh() noexcept;
    explicit Mesh(const std::vector<Vertex> &vertices,
                  const std::vector<IndexType> &indices,
                  std::shared_ptr<ShaderProgramType> shaderProgram,
                  std::shared_ptr<TextureType> texture = nullptr);

    Mesh(Mesh &&other) noexcept;
    Mesh &operator=(Mesh &&other) noexcept;
    ~Mesh() override;

    Mesh(const Mesh &other) = delete;
    Mesh &operator=(const Mesh &other) = delete;

    void draw(const glm::mat4 &mvp) override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

} // namespace Mesh

} // namespace Model


#endif // MODELVIEWER_MODEL_MESH_MESH_HPP_

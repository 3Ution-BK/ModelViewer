#ifndef MODELVIEWER_MODEL_LINE_LINEMODEL_HPP_
#define MODELVIEWER_MODEL_LINE_LINEMODEL_HPP_

#include "Model/IModelable.hpp"
#include "OpenGL/OpenGLLib.hpp"
#include "OpenGL/OpenGLShaderProgram.hpp"
#include "Vertex.hpp"

#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"

#include <memory>
#include <tuple>
#include <vector>

namespace Model
{

namespace Line
{

class LineModel : public IModelable
{
public:
    using IndexType = GLuint;
    using VertexType = Vertex;

    using ShaderProgramType = OpenGL::OpenGLShaderProgram;

    explicit LineModel(std::shared_ptr<ShaderProgramType> shaderProgram,
                       const std::tuple<std::vector<VertexType>,
                                        std::vector<IndexType>> &data);
    LineModel(LineModel &&other) noexcept;
    LineModel &operator=(LineModel &&other) noexcept;
    virtual ~LineModel() override;

    LineModel(const LineModel &other) = delete;
    LineModel &operator=(const LineModel &other) = delete;

    virtual void draw(const glm::mat4 &mvp) override;

    glm::vec4 color() const;
    void setColor(glm::vec4 color);

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

} // namespace Line

} // namespace Model

#endif // MODELVIEWER_MODEL_LINE_LINEMODEL_HPP_

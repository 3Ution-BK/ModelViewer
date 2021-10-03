#ifndef MODELVIEWER_MODEL_LINE_SCENEGRID_HPP_
#define MODELVIEWER_MODEL_LINE_SCENEGRID_HPP_

#include "LineModel.hpp"

#include "glm/vec3.hpp"

namespace Model
{

namespace Line
{

class SceneGrid : public LineModel
{
public:
    explicit SceneGrid(std::shared_ptr<ShaderProgramType> shaderProgram,
                       float size, float divide);
    explicit SceneGrid(std::shared_ptr<ShaderProgramType> shaderProgram,
                       glm::vec3 size, glm::vec3 divide);
    SceneGrid(SceneGrid &&other) noexcept;
    SceneGrid &operator=(SceneGrid &&other) noexcept;
    virtual ~SceneGrid() override;

    SceneGrid(const SceneGrid &other) = delete;
    SceneGrid &operator=(const SceneGrid &other) = delete;
};

} // namespace Line

} // namespace Model

#endif // MODELVIEWER_MODEL_LINE_SCENEGRID_HPP_

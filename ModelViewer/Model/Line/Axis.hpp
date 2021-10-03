#ifndef MODELVIEWER_MODEL_LINE_AXIS_HPP_
#define MODELVIEWER_MODEL_LINE_AXIS_HPP_

#include "LineModel.hpp"

namespace Model
{

namespace Line
{

class Axis : public LineModel
{
public:
    explicit Axis(std::shared_ptr<ShaderProgramType> shaderProgram, float size);
    Axis(Axis &&other) noexcept;
    Axis &operator=(Axis &&other) noexcept;
    virtual ~Axis() override;

    Axis(const Axis &other) = delete;
    Axis &operator=(const Axis &other) = delete;
};

} // namespace Line

} // namespace Model

#endif // MODELVIEWER_MODEL_LINE_AXIS_HPP_

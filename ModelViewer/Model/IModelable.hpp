#ifndef MODELVIEWER_MODEL_IMODELABLE_HPP_
#define MODELVIEWER_MODEL_IMODELABLE_HPP_

#include "glm/mat4x4.hpp"

namespace Model
{

class IModelable
{
public:
    virtual ~IModelable() {}
    virtual void draw(const glm::mat4 &mvp) = 0;
};

} // namespace Model

#endif // MODELVIEWER_MODEL_IMODELABLE_HPP_

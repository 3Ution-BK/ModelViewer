#ifndef OpenGLView_MODEL_VERTEX_HPP_
#define OpenGLView_MODEL_VERTEX_HPP_

#include "Utils/PreDefine.hpp"

PRAGMA_WARNING_PUSH
PRAGMA_WARNING_DISABLE_FLOATEQUAL
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
PRAGMA_WARNING_POP

namespace Model
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinate;
};

inline bool operator==(const Vertex &lhs, const Vertex &rhs)
{
    PRAGMA_WARNING_PUSH
    PRAGMA_WARNING_DISABLE_FLOATEQUAL
    return (lhs.position == rhs.position) && (lhs.normal == rhs.normal) &&
           (lhs.textureCoordinate == rhs.textureCoordinate);
    PRAGMA_WARNING_POP
}

inline bool operator!=(const Vertex &lhs, const Vertex &rhs)
{
    return !(lhs == rhs);
}

} // namespace Model

#endif // OpenGLView_MODEL_VERTEX_HPP_

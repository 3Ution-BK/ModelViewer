#ifndef MODELVIEWER_MODEL_LINE_VERTEX_HPP_
#define MODELVIEWER_MODEL_LINE_VERTEX_HPP_

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"


namespace Model
{

namespace Line
{

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
};

inline bool operator==(const Vertex &lhs, const Vertex &rhs)
{
    return (lhs.position == rhs.position) && (lhs.color == rhs.color);
}

inline bool operator!=(const Vertex &lhs, const Vertex &rhs)
{
    return !(lhs == rhs);
}

} // namespace Line

} // namespace Model


#endif // MODELVIEWER_MODEL_LINE_VERTEX_HPP_

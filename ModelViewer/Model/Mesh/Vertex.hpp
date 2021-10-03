#ifndef MODELVIEWER_MODEL_MESH_VERTEX_HPP_
#define MODELVIEWER_MODEL_MESH_VERTEX_HPP_

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace Model
{

namespace Mesh
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinate;
};

inline bool operator==(const Vertex &lhs, const Vertex &rhs)
{
    return (lhs.position == rhs.position) && (lhs.normal == rhs.normal) &&
           (lhs.textureCoordinate == rhs.textureCoordinate);
}

inline bool operator!=(const Vertex &lhs, const Vertex &rhs)
{
    return !(lhs == rhs);
}

} // namespace Mesh

} // namespace Model

#endif // MODELVIEWER_MODEL_MESH_VERTEX_HPP_

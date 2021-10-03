#include "SceneGrid.hpp"

#include "Model/VertexMap.hpp"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include <list>

namespace Model
{

namespace Line
{

namespace Detail
{

namespace Constant
{

inline constexpr glm::vec4 white{1.0f, 1.0f, 1.0f, 1.0f};

} // namespace Constant

auto calculate(const glm::vec3 &size, const glm::vec3 &divide,
               const glm::vec4 &color)
    -> std::tuple<std::vector<LineModel::VertexType>,
                  std::vector<LineModel::IndexType>>;
auto grid(const std::list<float> &x, const std::list<float> &y,
          const std::list<float> &z, const glm::vec3 &size,
          const glm::vec4 &color)
    -> std::tuple<std::vector<LineModel::VertexType>,
                  std::vector<LineModel::IndexType>>;
std::vector<glm::vec2> plain(const std::list<float> &x,
                             const std::list<float> &y, const glm::vec2 &size);
std::list<float> slice(float size, float divide);

auto calculate(const glm::vec3 &size, const glm::vec3 &divide,
               const glm::vec4 &color)
    -> std::tuple<std::vector<LineModel::VertexType>,
                  std::vector<LineModel::IndexType>>
{
    std::list<float> x{Detail::slice(size.x, divide.x)};
    std::list<float> y{Detail::slice(size.y, divide.y)};
    std::list<float> z{Detail::slice(size.z, divide.z)};

    return Detail::grid(x, y, z, size, color);
}

auto grid(const std::list<float> &x, const std::list<float> &y,
          const std::list<float> &z, const glm::vec3 &size,
          const glm::vec4 &color)
    -> std::tuple<std::vector<LineModel::VertexType>,
                  std::vector<LineModel::IndexType>>
{
    auto xy{plain(x, y, glm::vec2{size.x, size.y})};
    auto xz{plain(x, z, glm::vec2{size.x, size.z})};
    auto yz{plain(y, z, glm::vec2{size.y, size.z})};

    Model::VertexMap<LineModel::VertexType, LineModel::IndexType> map;

    for (const auto &vertex : xy)
    {
        map.insert(Vertex{glm::vec3{vertex.x, vertex.y, 0.0f}, color});
    }
    for (const auto &vertex : xz)
    {
        map.insert(Vertex{glm::vec3{vertex.x, 0.0f, vertex.y}, color});
    }
    for (const auto &vertex : yz)
    {
        map.insert(Vertex{glm::vec3{0.0f, vertex.x, vertex.y}, color});
    }

    std::vector<LineModel::VertexType> vertices;
    std::vector<LineModel::IndexType> indices;

    map.getVertices(vertices);
    map.getIndices(indices);

    return std::make_tuple(vertices, indices);
}

std::vector<glm::vec2> plain(const std::list<float> &x,
                             const std::list<float> &y, const glm::vec2 &size)
{
    std::vector<glm::vec2> vertices;

    for (const auto &i : x)
    {
        vertices.emplace_back(i, 0);
        vertices.emplace_back(i, size.x);
    }

    for (const auto &i : y)
    {
        vertices.emplace_back(0, i);
        vertices.emplace_back(size.y, i);
    }

    return vertices;
}

std::list<float> slice(float size, float divide)
{
    std::list<float> list;
    const auto unit{size / divide};

    for (float i{0.0f}; i <= divide; ++i)
    {
        list.push_back(unit * i);
    }
    return list;
}

} // namespace Detail

SceneGrid::SceneGrid(std::shared_ptr<ShaderProgramType> shaderProgram,
                     float size, float divide)
    : SceneGrid(shaderProgram, glm::vec3{size, size, size},
                glm::vec3{divide, divide, divide})
{
}

SceneGrid::SceneGrid(std::shared_ptr<ShaderProgramType> shaderProgram,
                     glm::vec3 size, glm::vec3 divide)
    : LineModel(shaderProgram,
                Detail::calculate(size, divide, Detail::Constant::white))
{
}

SceneGrid::SceneGrid(SceneGrid &&other) noexcept = default;

SceneGrid &SceneGrid::operator=(SceneGrid &&other) noexcept = default;

SceneGrid::~SceneGrid() noexcept = default;

} // namespace Line

} // namespace Model

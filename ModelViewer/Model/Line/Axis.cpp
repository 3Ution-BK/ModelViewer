#include "Axis.hpp"

#include "OpenGL/OpenGLException.hpp"
#include "Vertex.hpp"

#include <list>
#include <tuple>

namespace Model
{

namespace Line
{

namespace Detail
{

namespace Constant
{

namespace Color
{
inline constexpr glm::vec4 blue{0.0f, 0.0f, 1.0f, 1.0f};
inline constexpr glm::vec4 green{0.0f, 1.0f, 0.0f, 1.0f};
inline constexpr glm::vec4 red{1.0f, 0.0f, 0.0f, 1.0f};
} // namespace Color

namespace Point
{
inline constexpr glm::vec3 origin{0.0f, 0.0f, 0.0f};
inline constexpr glm::vec3 x{1.0f, 0.0f, 0.0f};
inline constexpr glm::vec3 y{0.0f, 1.0f, 0.0f};
inline constexpr glm::vec3 z{0.0f, 0.0f, 1.0f};
} // namespace Point

} // namespace Constant

auto axis(float size) -> std::tuple<std::vector<LineModel::VertexType>,
                                    std::vector<LineModel::IndexType>>;

auto axis(float size) -> std::tuple<std::vector<LineModel::VertexType>,
                                    std::vector<LineModel::IndexType>>
{
    std::vector<LineModel::VertexType> vertices{
        LineModel::VertexType{Constant::Point::origin, Constant::Color::red},
        LineModel::VertexType{Constant::Point::x * size, Constant::Color::red},
        LineModel::VertexType{Constant::Point::origin, Constant::Color::green},
        LineModel::VertexType{Constant::Point::y * size,
                              Constant::Color::green},
        LineModel::VertexType{Constant::Point::origin, Constant::Color::blue},
        LineModel::VertexType{Constant::Point::z * size,
                              Constant::Color::blue}};

    std::vector<LineModel::IndexType> indices{0u, 1u, 2u, 3u, 4u, 5u};

    return std::make_tuple(vertices, indices);
}

} // namespace Detail

Axis::Axis(std::shared_ptr<ShaderProgramType> shaderProgram, float size)
    : LineModel{shaderProgram, Detail::axis(size)}
{
}

Axis::Axis(Axis &&other) noexcept = default;

Axis &Axis::operator=(Axis &&other) noexcept = default;

Axis::~Axis() noexcept = default;

} // namespace Line

} // namespace Model

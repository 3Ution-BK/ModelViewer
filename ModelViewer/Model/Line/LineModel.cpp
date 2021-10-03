#include "LineModel.hpp"

#include "OpenGL/OpenGLException.hpp"
#include "Vertex.hpp"

#include "OpenGL/OpenGLBufferObject.hpp"
#include "OpenGL/OpenGLVertexArrayObject.hpp"

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

} // namespace Detail

class LineModel::Impl
{
public:
    using VertexArrayObjectType = OpenGL::OpenGLVertexArrayObject;
    using BufferObjectType = OpenGL::OpenGLBufferObject;

    explicit Impl(std::shared_ptr<ShaderProgramType> shaderProgram,
                  const std::tuple<std::vector<VertexType>,
                                   std::vector<IndexType>> &data);

    Impl(Impl &&other) noexcept;
    Impl &operator=(Impl &&other) noexcept;
    ~Impl();

    Impl(const Impl &other) = delete;
    Impl &operator=(const Impl &other) = delete;

    void create(const std::vector<VertexType> &vertices,
                const std::vector<IndexType> &indices);

    void draw(const glm::mat4 &mvp);

    glm::vec4 color() const;
    void setColor(glm::vec4 color);

private:
    void programMapAttribute(ShaderProgramType &program, GLuint index,
                             GLint size, GLenum type, GLboolean normalized,
                             GLsizei stride, int offset);

    std::shared_ptr<ShaderProgramType> shaderProgram_;

    std::unique_ptr<VertexArrayObjectType> vertexArrayObject_;
    std::unique_ptr<BufferObjectType> vertexBufferObject_;
    std::unique_ptr<BufferObjectType> elementBufferObject_;
    int indicesCount_;

    glm::vec4 color_;
};

LineModel::LineModel(
    std::shared_ptr<ShaderProgramType> shaderProgram,
    const std::tuple<std::vector<VertexType>, std::vector<IndexType>> &data)
    : pimpl_{std::make_unique<Impl>(shaderProgram, data)}
{
}

LineModel::LineModel(LineModel &&other) noexcept = default;

LineModel &LineModel::operator=(LineModel &&other) noexcept = default;

LineModel::~LineModel() noexcept = default;

glm::vec4 LineModel::color() const { return pimpl_->color(); }

void LineModel::draw(const glm::mat4 &mvp) { pimpl_->draw(mvp); }

void LineModel::setColor(glm::vec4 color) { pimpl_->setColor(color); }

LineModel::Impl::Impl(
    std::shared_ptr<ShaderProgramType> shaderProgram,
    const std::tuple<std::vector<VertexType>, std::vector<IndexType>> &data)
    : shaderProgram_{shaderProgram},
      vertexArrayObject_{std::make_unique<VertexArrayObjectType>()},
      vertexBufferObject_{std::make_unique<BufferObjectType>(
          BufferObjectType::Type::ArrayBuffer,
          BufferObjectType::UsagePattern::StaticDraw)},
      elementBufferObject_{std::make_unique<BufferObjectType>(
          BufferObjectType::Type::ArrayBuffer,
          BufferObjectType::UsagePattern::StaticDraw)},
      indicesCount_{static_cast<GLsizei>(std::get<1>(data).size())},
      color_{Detail::Constant::white}
{
    create(std::get<0>(data), std::get<1>(data));
}

LineModel::Impl::Impl(Impl &&other) noexcept = default;

LineModel::Impl &LineModel::Impl::operator=(Impl &&other) noexcept = default;

LineModel::Impl::~Impl() noexcept = default;

void LineModel::Impl::create(const std::vector<VertexType> &vertices,
                             const std::vector<IndexType> &indices)
{
    vertexArrayObject_->bind();
    {
        vertexBufferObject_->bind();
        vertexBufferObject_->allocateBufferData(
            vertices.data(), sizeof(VertexType) * vertices.size());

        programMapAttribute(*shaderProgram_, 0, 3, GL_FLOAT, GL_FALSE,
                            sizeof(VertexType), offsetof(Vertex, position));
        programMapAttribute(*shaderProgram_, 1, 4, GL_FLOAT, GL_FALSE,
                            sizeof(VertexType), offsetof(Vertex, color));

        elementBufferObject_->bind();
        elementBufferObject_->allocateBufferData(
            indices.data(), sizeof(IndexType) * indices.size());
    }
    vertexArrayObject_->release();

    indicesCount_ = static_cast<GLsizei>(indices.size());
}

glm::vec4 LineModel::Impl::color() const { return color_; }

void LineModel::Impl::draw(const glm::mat4 &mvp)
{
    shaderProgram_->use();

    shaderProgram_->setValue("mvp", mvp, false);
    shaderProgram_->setValue("color", color_);

    vertexArrayObject_->bind();
    glDrawElements(GL_LINES, indicesCount_, GL_UNSIGNED_INT, 0);
    vertexArrayObject_->release();
}

void LineModel::Impl::programMapAttribute(ShaderProgramType &program,
                                          GLuint index, GLint size, GLenum type,
                                          GLboolean normalized, GLsizei stride,
                                          int offset)
{
    program.enableAttributeArray(index);
    program.mapAttributePointer(index, size, type, normalized, stride, offset);
}

void LineModel::Impl::setColor(glm::vec4 color) { color_ = color; }

} // namespace Line

} // namespace Model

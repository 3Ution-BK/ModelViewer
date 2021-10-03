#include "MeshLoader.hpp"

#include "FileIO/FileIO.hpp"
#include "Hash/Hash.hpp"
#include "Model/VertexMap.hpp"
#include "Utils/PreDefine.hpp"
#include "Vertex.hpp"

PRAGMA_WARNING_PUSH
PRAGMA_WARNING_DISABLE_DOUBLEPROMOTION

#include "stb_image.h"

PRAGMA_WARNING_POP

#include "tiny_obj_loader.h"

#include <iostream>
#include <unordered_map>

namespace Model
{

namespace Mesh
{

namespace Loader
{

namespace Detail
{

void getData(const tinyobj::attrib_t &attribute,
             const std::vector<tinyobj::shape_t> &shapes,
             std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
std::shared_ptr<Mesh> getMesh(const tinyobj::attrib_t &attribute,
                              const std::vector<tinyobj::shape_t> &shapes,
                              OpenGL::OpenGLFunction &gl,
                              std::shared_ptr<QOpenGLShaderProgram> program,
                              std::shared_ptr<QOpenGLTexture> texture);
Vertex getVertex(const tinyobj::attrib_t &attribute, tinyobj::index_t &index);
GLenum rgbFormat(int channels) noexcept;

void getData(const tinyobj::attrib_t &attribute,
             const std::vector<tinyobj::shape_t> &shapes,
             std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
    VertexMap<Vertex, GLuint> map;

    for (const auto &shape : shapes)
    {
        size_t indexOffset{0};

        for (const auto &faceVertices : shape.mesh.num_face_vertices)
        {
            size_t castedFaceVertices{static_cast<size_t>(faceVertices)};
            for (size_t v{0}; v < castedFaceVertices; ++v)
            {
                auto index{shape.mesh.indices[indexOffset + v]};
                auto vertex{getVertex(attribute, index)};
                map.insert(vertex);
            }

            indexOffset += castedFaceVertices;
        }
    }

    map.getVertices(vertices);
    map.getIndices(indices);
}

std::shared_ptr<Mesh> getMesh(const tinyobj::attrib_t &attribute,
                              const std::vector<tinyobj::shape_t> &shapes,
                              OpenGL::OpenGLFunction &gl,
                              std::shared_ptr<QOpenGLShaderProgram> program,
                              std::shared_ptr<QOpenGLTexture> texture)
{
    std::vector<GLuint> indices;
    std::vector<Vertex> vertices;

    Detail::getData(attribute, shapes, vertices, indices);

    return std::make_shared<Model::Mesh::Mesh>(vertices, indices, gl, program,
                                               texture);
}

Vertex getVertex(const tinyobj::attrib_t &attribute, tinyobj::index_t &index)
{
    auto position{glm::vec3{
        attribute.vertices[static_cast<size_t>(3 * index.vertex_index + 0)],
        attribute.vertices[static_cast<size_t>(3 * index.vertex_index + 1)],
        attribute.vertices[static_cast<size_t>(3 * index.vertex_index + 2)]}};
    auto normal{glm::vec3{
        attribute.normals[static_cast<size_t>(3 * index.normal_index + 0)],
        attribute.normals[static_cast<size_t>(3 * index.normal_index + 1)],
        attribute.normals[static_cast<size_t>(3 * index.normal_index + 2)]}};
    auto texture{glm::vec2{
        attribute.texcoords[static_cast<size_t>(2 * index.texcoord_index + 0)],
        attribute
            .texcoords[static_cast<size_t>(2 * index.texcoord_index + 1)]}};

    return Model::Mesh::Vertex{position, normal, texture};
}

GLenum rgbFormat(int channels) noexcept
{
    switch (channels)
    {
    case 1:
        return GL_RED;
    case 2:
        return GL_RG;
    case 4:
        return GL_RGBA;
    case 3:
    default:
        return GL_RGB;
    }
}

} // namespace Detail

std::shared_ptr<Mesh>
loadMeshFromFile(const char *model,
                 std::shared_ptr<QOpenGLShaderProgram> program,
                 std::shared_ptr<QOpenGLTexture> texture)
{
    tinyobj::attrib_t attribute;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warning;
    std::string error;

    auto loadStatus = tinyobj::LoadObj(&attribute, &shapes, &materials,
                                       &warning, &error, model);

    if (!warning.empty())
    {
        std::cerr << "[Warning] " << warning;
    }

    if (!error.empty())
    {
        std::cerr << "[Error] " << error;
    }

    if (!loadStatus)
    {
        return nullptr;
    }

    return Detail::getMesh(attribute, shapes, gl, program, texture);
}

std::shared_ptr<Mesh>
loadModelFromStream(std::istream &stream, OpenGL::OpenGLFunction &gl,
                    std::shared_ptr<QOpenGLShaderProgram> program,
                    std::shared_ptr<QOpenGLTexture> texture)
{
    tinyobj::attrib_t attribute;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warning;
    std::string error;

    auto loadStatus = tinyobj::LoadObj(&attribute, &shapes, &materials,
                                       &warning, &error, &stream);

    if (!warning.empty())
    {
        std::cerr << "[Warning] " << warning;
    }

    if (!error.empty())
    {
        std::cerr << "[Error] " << error;
    }

    if (!loadStatus)
    {
        return nullptr;
    }

    return Detail::getMesh(attribute, shapes, gl, program, texture);
}

std::shared_ptr<OpenGL::OpenGLTexture>
ModelFactory::loadTextureFromFile(const char *fileName)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data{stbi_load(fileName, &width, &height, &channels, 0)};

    if (!data)
    {
        return nullptr;
    }

    const size_t size{static_cast<size_t>(width * height * channels)};

    std::vector<unsigned char> buffer{data, data + size};
    stbi_image_free(data);

    return std::make_shared<OpenGL::OpenGLTexture>(
        width, height, Detail::rgbFormat(channels), buffer);
}

} // namespace Loader

} // namespace Mesh

} // namespace Model

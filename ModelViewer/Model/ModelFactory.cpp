#include "ModelFactory.hpp"

#include "Hash/Hash.hpp"
#include "Utils/PreDefine.hpp"
#include "Vertex.hpp"
#include "VertexMap.hpp"

PRAGMA_WARNING_PUSH
PRAGMA_WARNING_DISABLE_DOUBLEPROMOTION

#include "stb_image.h"

PRAGMA_WARNING_POP

#include "tiny_obj_loader.h"

#include <iostream>
#include <unordered_map>

namespace Model
{

namespace Detail
{

void getData(const tinyobj::attrib_t &attribute,
             const std::vector<tinyobj::shape_t> &shapes,
             std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
Vertex getVertex(const tinyobj::attrib_t &attribute, tinyobj::index_t &index);
GLenum rgbFormat(int channels) noexcept;

void getData(const tinyobj::attrib_t &attribute,
             const std::vector<tinyobj::shape_t> &shapes,
             std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
    VertexMap<Vertex, GLuint> map;

    for (auto &shape : shapes)
    {
        size_t indexOffset{0};

        for (auto &faceVertices : shape.mesh.num_face_vertices)
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

Vertex getVertex(const tinyobj::attrib_t &attribute, tinyobj::index_t &index)
{
    auto vx{attribute.vertices[3 * index.vertex_index + 0]};
    auto vy{attribute.vertices[3 * index.vertex_index + 1]};
    auto vz{attribute.vertices[3 * index.vertex_index + 2]};
    auto nx{attribute.normals[3 * index.normal_index + 0]};
    auto ny{attribute.normals[3 * index.normal_index + 1]};
    auto nz{attribute.normals[3 * index.normal_index + 2]};
    auto tx{attribute.texcoords[2 * index.texcoord_index + 0]};
    auto ty{attribute.texcoords[2 * index.texcoord_index + 1]};

    return Model::Vertex{glm::vec3{vx, vy, vz}, glm::vec3{nx, ny, nz},
                         glm::vec2{tx, ty}};
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

std::unique_ptr<OpenGL::OpenGLTexture>
ModelFactory::loadTextureFromFile(const char *fileName)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data{stbi_load(fileName, &width, &height, &channels, 0)};

    if (!data)
    {
        return std::make_unique<OpenGL::OpenGLTexture>();
    }

    const size_t size{static_cast<size_t>(width * height * channels)};

    std::vector<unsigned char> buffer{data, data + size};
    stbi_image_free(data);

    return std::make_unique<OpenGL::OpenGLTexture>(
        width, height, Detail::rgbFormat(channels), buffer);
}

std::unique_ptr<Mesh> ModelFactory::loadMeshFromFile(
    const char *model, std::string &warning, std::string &error,
    OpenGL::OpenGLShaderProgram &program, OpenGL::OpenGLTexture *texture)
{
    tinyobj::attrib_t attribute;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    auto loadStatus = tinyobj::LoadObj(&attribute, &shapes, &materials,
                                       &warning, &error, model);

    if (!loadStatus)
    {
        return nullptr;
    }

    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;

    Detail::getData(attribute, shapes, vertices, indices);

    return std::make_unique<Model::Mesh>(vertices, indices, program, texture);
}

} // namespace Model

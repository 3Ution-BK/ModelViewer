#ifndef MODELVIEWER_MODEL_MESH_MESHLOADER_HPP_
#define MODELVIEWER_MODEL_MESH_MESHLOADER_HPP_

#include "Mesh.hpp"

#include "opencv2/core/mat.hpp"

#include <QOpenGLTexture>

#include <memory>
#include <string>

namespace Model
{

namespace Mesh
{

namespace Loader
{

std::shared_ptr<Mesh>
loadMeshFromFile(const char *model,
                 std::shared_ptr<QOpenGLShaderProgram> program,
                 std::shared_ptr<QOpenGLTexture> texture = nullptr);

std::shared_ptr<Mesh>
loadModelFromStream(std::istream &stream,
                    std::shared_ptr<QOpenGLShaderProgram> program,
                    std::shared_ptr<QOpenGLTexture> texture = nullptr);

std::shared_ptr<QOpenGLTexture> loadTextureFromFile(const char *fileName);

} // namespace Loader

} // namespace Mesh

} // namespace Model

#endif // MODELVIEWER_MODEL_MESH_MESHLOADER_HPP_

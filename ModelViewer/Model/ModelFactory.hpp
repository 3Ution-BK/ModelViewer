#ifndef MODELVIEWER_MODEL_MODELFACTORY_HPP_
#define MODELVIEWER_MODEL_MODELFACTORY_HPP_

#include "Mesh.hpp"
#include "OpenGL/OpenGLTexture.hpp"

#include <memory>
#include <string>

namespace Model
{

class ModelFactory
{
public:
    static std::unique_ptr<OpenGL::OpenGLTexture>
    loadTextureFromFile(const char *fileName);

    static std::unique_ptr<Mesh>
    loadMeshFromFile(const char *model, std::string &warning,
                     std::string &error, OpenGL::OpenGLShaderProgram &program,
                     OpenGL::OpenGLTexture *texture = nullptr);
};

} // namespace Model

#endif // MODELVIEWER_MODEL_MODELFACTORY_HPP_

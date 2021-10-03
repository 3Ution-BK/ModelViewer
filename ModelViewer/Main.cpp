#include "OpenGLWindow.hpp"
#include "OpenGLWindowBuilder.hpp"

#include "glm/vec2.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

int main(int argc, char *argv[])
{
    if (argc <= 4)
    {
        std::cerr << "Not enough parameter\n";
        std::cerr << "Expect: " << argv[0]
                  << "[model name] [texture name] [vertex shader file name] "
                     "[fragment shader file name]"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string model{argv[1]};
    std::string texture{argv[2]};
    std::string vertexShader{argv[3]};
    std::string fragmentShader{argv[4]};

    std::cout << "Vertex Shader: " << vertexShader << "\n"
              << "Fragment Shader: " << fragmentShader << "\n"
              << "Model: " << model << "\n"
              << "Texture: " << texture << std::endl;

    OpenGLWindowBuilder builder;

    auto window{builder.setVersion(4, 3)
                    .setTitle("LearnOpenGL")
                    .setPosition(100, 100)
                    .setSize(800, 600)
                    .build()};

    if (!window)
    {
        exit(EXIT_FAILURE);
    }

    OpenGL::OpenGLShaderProgram *shaderProgram{window->addShader(
        vertexShader.c_str(), fragmentShader.c_str(), nullptr)};

    if (!shaderProgram)
    {
        std::cerr << "Failed to compile shader" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!window->addModel(model.c_str(), texture.c_str(), *shaderProgram))
    {
        std::cerr << "Failed to add model" << std::endl;
        exit(EXIT_FAILURE);
    }

    window->startRender();

    return 0;
}

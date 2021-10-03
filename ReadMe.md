# ModelViewer

## Overview

This toy program demonstrates the obj file viewer with 1 texture using OpenGL.

This repository is found in my personal code testing playground.
It was used for learning purpose.
I decided to recycle the code into something useful.

This is probably not the good approach, but I do hope you can find something
useful.

## Requirement

|          | Requirement                   |
| -------- | ----------------------------- |
| Language | C++14                         |
| Compiler | Any compiler capable of C++14 |
| CMake    | At least 3.3.0                |
| OpenGL   | At least 4.3.0                |

## Additional libraries

This repository used multiple additional libraries.

|               | Version                     | Note                           |
| ------------- | --------------------------- | ------------------------------ |
| glfw          | 3.3                         |                                |
| glm           | 0.9.9.8                     |                                |
| glad          | Generated under glad 0.1.33 | Package in `thridparty` folder |
| imgui         | 1.77                        | Package in `thridparty` folder |
| stb_image     | 2.25                        | Package in `thridparty` folder |
| tinyobjloader | 2.2.0                       | Package in `thridparty` folder |

## How to build

Use CMake to build the library.
Before configure the repository, please install the *GLFW3* and *glm* library
inside your machine.

You need to tell CMake the installed location of the *GLFW3* and *glm* library.

## How to run

Pass the required argument:

```bash
./ModelViewer.exe [model name] [texture name] [vertex shader file name] [fragment shader file name]
```

e.g.

```bash
./ModelViewer.exe cube.obj uv.png Shader/BasicVertexShader.vs.glsl Shader/BasicFragmentShader.fs.glsl
```

## License

The source code (exclude `thirdparty` folder, which contains multiple additional
libraries) is covered under MIT license.

Each license of the libraries is covered under their individual license.
Please follow their regulations.

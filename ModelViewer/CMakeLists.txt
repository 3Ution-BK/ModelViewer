cmake_minimum_required(VERSION 3.3.0)

set(${PROJECT_NAME}_EXECUTABLE_NAME ${PROJECT_NAME})

include(${${PROJECT_NAME}_MODULE_DIR}/CompilerOptions.cmake)

set(${PROJECT_NAME}_HEADER_CODE
    Event/Event.hpp
    Event/EventHandler.hpp
    Event/EventHandlerBase.hpp
    Event/InputAction.hpp
    Event/InputEvent.hpp
    Event/InputModifierFlags.hpp
    Event/KeyboardCode.hpp
    Event/KeyboardEvent.hpp
    Event/MoveEvent.hpp
    Event/MouseEvent.hpp
    Event/ResizeEvent.hpp
    FileIO/Detail/Generals.hpp
    FileIO/FileIn.hpp
    Hash/Hash.hpp
    Logger/Logger.hpp
    Model/Mesh.hpp
    Model/ModelFactory.hpp
    Model/VertexMap.hpp
    OpenGLWindow.hpp
    OpenGLWindowBuilder.hpp
    OpenGL/Detail/Set.hpp
    OpenGL/OpenGLLib.hpp
    OpenGL/OpenGLBufferObject.hpp
    OpenGL/OpenGLException.hpp
    OpenGL/OpenGLShader.hpp
    OpenGL/OpenGLShaderProgram.hpp
    OpenGL/OpenGLVertexArrayObject.hpp
    OpenGL/OpenGLTexture.hpp
    TimeFrame/TimeFrame.hpp
    TimeFrame/TimeFrameException.hpp
    Utils/PreDefine/Architecture.hpp
    Utils/PreDefine/Architecture/Fallback.hpp
    Utils/PreDefine/Architecture/Windows.hpp
    Utils/PreDefine/Architecture/X86.hpp
    Utils/PreDefine/Compiler.hpp
    Utils/PreDefine/Compiler/Clang.hpp
    Utils/PreDefine/Compiler/Detail/Detected.hpp
    Utils/PreDefine/Compiler/Gcc.hpp
    Utils/PreDefine/Compiler/Msvc.hpp
    Utils/PreDefine/Language.hpp
    Utils/PreDefine/OperatingSystem.hpp
    Utils/PreDefine/OperatingSystem/Cygwin.hpp
    Utils/PreDefine/OperatingSystem/Detail/Detected.hpp
    Utils/PreDefine/OperatingSystem/Linux.hpp
    Utils/PreDefine/OperatingSystem/Macos.hpp
    Utils/PreDefine/OperatingSystem/Unix.hpp
    Utils/PreDefine/OperatingSystem/Windows.hpp
    Utils/PreDefine/PragmaWarning.hpp
    Utils/StringFormat/StringFormat.hpp
)

set(${PROJECT_NAME}_INLINE_CODE
    Event/Event-inl.hpp
    Event/EventHandler-inl.hpp
    Event/InputEvent-inl.hpp
    Event/InputModifierFlags-inl.hpp
    Event/KeyboardEvent-inl.hpp
    Event/MoveEvent-inl.hpp
    Event/MouseEvent-inl.hpp
    Event/ResizeEvent-inl.hpp
    Model/VertexMap-inl.hpp
    OpenGL/Detail/Set-inl.hpp
    OpenGL/OpenGLShaderProgram-inl.hpp
    Utils/StringFormat/StringFormat-inl.hpp
)

set(${PROJECT_NAME}_SOURCE_CODE
    Event/Event.cpp
    Event/EventHandlerBase.cpp
    Event/InputEvent.cpp
    Event/KeyboardEvent.cpp
    Event/MoveEvent.cpp
    Event/MouseEvent.cpp
    Event/ResizeEvent.cpp
    FileIO/Detail/Generals.cpp
    FileIO/FileIn.cpp
    Main.cpp
    Logger/Logger.cpp
    Model/Mesh.cpp
    Model/ModelFactory.cpp
    OpenGLWindow.cpp
    OpenGLWindowBuilder.cpp
    OpenGL/OpenGLBufferObject.cpp
    OpenGL/OpenGLException.cpp
    OpenGL/OpenGLShader.cpp
    OpenGL/OpenGLShaderProgram.cpp
    OpenGL/OpenGLVertexArrayObject.cpp
    OpenGL/OpenGLTexture.cpp
    TimeFrame/TimeFrame.cpp
    TimeFrame/TimeFrameException.cpp
)

add_executable(${${PROJECT_NAME}_EXECUTABLE_NAME}
    ${${PROJECT_NAME}_HEADER_CODE}
    ${${PROJECT_NAME}_INLINE_CODE}
    ${${PROJECT_NAME}_SOURCE_CODE}
)

set_target_properties(${${PROJECT_NAME}_EXECUTABLE_NAME}
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
)

target_include_directories(${${PROJECT_NAME}_EXECUTABLE_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${GLM_INCLUDE_DIRS}
        ${IMGUI_INCLUDE_DIRS}
        ${TINYOBJLOADER_INCLUDE_DIRS}
        ${STB_INCLUDE_DIRS}
)

target_compile_features(${${PROJECT_NAME}_EXECUTABLE_NAME}
    PUBLIC
        cxx_std_14
)

target_compile_options(${${PROJECT_NAME}_EXECUTABLE_NAME}
    PUBLIC
        "$<$<CONFIG:DEBUG>:${${PROJECT_NAME}_CXX_FLAGS_DEBUG}>"
        "$<$<CONFIG:RELEASE>:${${PROJECT_NAME}_CXX_FLAGS_RELEASE}>"
)

target_compile_definitions(${${PROJECT_NAME}_EXECUTABLE_NAME}
    PRIVATE
        GLM_FORCE_SILENT_WARNINGS
)

target_link_libraries(${${PROJECT_NAME}_EXECUTABLE_NAME}
    PRIVATE
        ${OPENGL_gl_LIBRARY}
        glad
        glfw
        imgui
        stb
        tinyobjloader
        $<$<PLATFORM_ID:Linux>:${CMAKE_DL_LIBS}>
)

include(${${PROJECT_NAME}_MODULE_DIR}/PostBuildCommand.cmake)

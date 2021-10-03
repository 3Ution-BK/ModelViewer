#include "Logger.hpp"

#include "Utils/PreDefine.hpp"
#include "Utils/StringFormat/StringFormat.hpp"

#include "OpenGL/OpenGLLib.hpp"

#include <ctime>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

namespace Logger
{

namespace Detail
{

std::string getCurrentTime();
std::string getSeverity(GLenum severity);
std::string getSource(GLenum source);
std::string getType(GLenum type);

std::string getCurrentTime()
{
    using namespace std::chrono;
    auto now{system_clock::now()};
    auto us{duration_cast<microseconds>(now.time_since_epoch()) % 1000000};

    auto nowRaw{system_clock::to_time_t(now)};
    std::tm timeInfo;
#if defined(PROGRAM_COMPILER_MSVC)
    localtime_s(&timeInfo, &nowRaw);
#elif defined(PROGRAM_SYSTEM_UNIX)
    localtime_r(&nowRaw, &timeInfo);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    timeInfo = *std::localtime(&nowRaw);
#endif
    std::ostringstream stream;

    stream << std::put_time(&timeInfo, "%Y/%m/%d %H:%M:%S");
    stream << "." << std::setfill('0') << std::setw(6) << us.count();
    return stream.str();
}

std::string getSeverity(GLenum severity)
{
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        return "High";
    case GL_DEBUG_SEVERITY_MEDIUM:
        return "Medium";
    case GL_DEBUG_SEVERITY_LOW:
        return "Low";
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        return "Notification";
    default:
        return "Unknown";
    }
}

std::string getSource(GLenum source)
{
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return "OpenGLWindow System";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        return "Shader Compiler";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return "Third Party";
    case GL_DEBUG_SOURCE_APPLICATION:
        return "Application";
    case GL_DEBUG_SOURCE_OTHER:
        return "Other";
    default:
        return "Unknown";
    }
}

std::string getType(GLenum type)
{
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        return "Error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return "Deprecated Behaviour";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return "Undefined Behaviour";
    case GL_DEBUG_TYPE_PORTABILITY:
        return "Portability";
    case GL_DEBUG_TYPE_PERFORMANCE:
        return "Performance";
    case GL_DEBUG_TYPE_MARKER:
        return "Marker";
    case GL_DEBUG_TYPE_PUSH_GROUP:
        return "Push Group";
    case GL_DEBUG_TYPE_POP_GROUP:
        return "Pop Group";
    case GL_DEBUG_TYPE_OTHER:
        return "Other";
    default:
        return "Unknown";
    }
}

} // namespace Detail

void APIENTRY openGLDebugOutput(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam)
{
    PROGRAM_MAYBE_UNUSED(length);
    PROGRAM_MAYBE_UNUSED(userParam);

    auto fullMessage{StringFormat::StringFormat(
        "%u: [%s] [%12s] [%s] [%s]\n%s", id, Detail::getCurrentTime().c_str(),
        Detail::getSeverity(severity).c_str(), Detail::getType(type).c_str(),
        Detail::getSource(source).c_str(), message)};

    std::cerr << fullMessage << "\n";
}

} // namespace Logger

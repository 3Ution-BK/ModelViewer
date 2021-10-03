#include "OpenGLWindow.hpp"

#include "Event/Event.hpp"
#include "Event/EventHandler.hpp"
#include "Event/KeyboardEvent.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/MoveEvent.hpp"
#include "Event/ResizeEvent.hpp"
#include "Logger/Logger.hpp"
#include "Model/ModelFactory.hpp"
#include "OpenGL/OpenGLException.hpp"
#include "OpenGLWindowBuilder.hpp"
#include "TimeFrame/TimeFrame.hpp"
#include "Utils/PreDefine.hpp"
#include "Utils/StringFormat/StringFormat.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <forward_list>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace Detail
{

bool compileShaders(OpenGL::OpenGLShaderProgram &program,
                    const char *vertexShaderFile,
                    const char *fragmentShaderFile = nullptr,
                    const char *geometryShaderFile = nullptr);

bool compileShaders(OpenGL::OpenGLShaderProgram &program,
                    const char *vertexShaderFile,
                    const char *fragmentShaderFile,
                    const char *geometryShaderFile)
{
    if (!program.addShaderFromFile(OpenGL::OpenGLShader::Type::Vertex,
                                   vertexShaderFile))
    {
        return false;
    }

    if (fragmentShaderFile &&

        !program.addShaderFromFile(OpenGL::OpenGLShader::Type::Fragment,
                                   fragmentShaderFile))
    {
        return false;
    }

    if (geometryShaderFile &&
        !program.addShaderFromFile(OpenGL::OpenGLShader::Type::Geometry,
                                   geometryShaderFile))
    {
        return false;
    }

    program.link();
    if (!program.linkStatus())
    {
        return false;
    }

    return true;
}

} // namespace Detail

class OpenGLWindow::Impl
{
public:
    enum RenderMode : int
    {
        Line = GL_LINE,
        Fill = GL_FILL
    };

    explicit Impl(const OpenGLWindowBuilder &builder);
    ~Impl();

    Impl(Impl &&other) = delete;
    Impl &operator=(Impl &&other) = delete;
    Impl(const Impl &other) = delete;
    Impl &operator=(const Impl &other) = delete;

    void startRender();

    bool addModel(const char *modelSource, const char *textureSource,
                  OpenGL::OpenGLShaderProgram &program);
    OpenGL::OpenGLShaderProgram *
    addShader(const char *vertexShaderSource, const char *fragmentShaderSource,
              const char *geometryShaderSource = nullptr);

    glm::ivec2 windowPosition() const;
    void setWindowPosition(const glm::ivec2 &position);
    void setWindowPosition(int x, int y);

    glm::ivec2 windowSize() const;
    void setWindowSize(const glm::ivec2 &size);
    void setWindowSize(int width, int height);

    glm::ivec2 frameBufferSize() const;

    GLFWwindow &window();
    const GLFWwindow &window() const;

    void pushEvent(std::unique_ptr<Event::Event> &&event);

    void frameBufferResizeEvent(Event::FrameBufferResizeEvent *event);
    void mouseEvent(Event::MouseEvent *event);
    void keyboardEvent(Event::KeyboardEvent *event);
    void windowMoveEvent(Event::MoveEvent *event);
    void windowResizeEvent(Event::WindowResizeEvent *event);

    void create(const glm::ivec2 &version, OpenGLWindow &window);

private:
    static void mouseButtonInputCallback(GLFWwindow *window, int button,
                                         int action, int mods);
    static void keyboardInputCallback(GLFWwindow *window, int key, int scancode,
                                      int action, int mods);
    static void frameBufferSizeCallback(GLFWwindow *window, int width,
                                        int height);
    static void windowPositionCallback(GLFWwindow *window, int x, int y);
    static void windowSizeCallback(GLFWwindow *window, int width, int height);

    bool createWindow(OpenGLWindow &window);
    void initializeDebug();
    void initializeEventQueue(OpenGLWindow &window);
    bool initializeGLAD();
    void initializeImgui();
    bool initializeOpenGL(const glm::ivec2 &version);

    void destroy();
    void destroyDebug();
    void destroyGLAD();
    void destroyImgui();
    void destroyOpenGL();

    void windowFrameLoop();
    void windowFrameEventUpdate();
    void windowFrameRender();
    void windowFrameRenderImguiUpdate();

    void windowImguiGeneralSetting();

    void handleEvent(Event::Event *event);

    void updateFrameBufferSize(const glm::ivec2 &frame);

    void clearColor();

    float windowAspectRatio() const;
    int windowHeight() const;
    int windowWidth() const;

    float frameBufferAspectRatio() const;
    int frameBufferHeight() const;
    int frameBufferWidth() const;

    bool isRenderable() const;

    GLFWwindow *window_;
    std::queue<std::unique_ptr<Event::Event>> eventQueue_;
    std::forward_list<std::unique_ptr<Event::EventHandlerBase>> eventHandlers_;

    glm::ivec2 position_;
    glm::ivec2 windowSize_;
    glm::ivec2 frameBufferSize_;
    std::string title_;

    std::vector<std::unique_ptr<Model::Mesh>> models_;
    std::vector<std::unique_ptr<OpenGL::OpenGLTexture>> textures;
    std::vector<std::unique_ptr<OpenGL::OpenGLShaderProgram>> shaders_;

    RenderMode renderMode_;

    std::unique_ptr<TimeFrame::TimeFrame> timeFrame_;

    glm::vec4 backgroundColor_;

    glm::vec3 lookAt_;
    glm::vec3 cameraPosition_;
};

OpenGLWindow::OpenGLWindow(const OpenGLWindowBuilder &builder)
    : pimpl_{std::make_unique<Impl>(builder)}
{
    pimpl_->create(builder.productVersion(), *this);
}

OpenGLWindow::~OpenGLWindow() = default;

bool OpenGLWindow::addModel(const char *modelSource, const char *textureSource,
                            OpenGL::OpenGLShaderProgram &program)
{
    return pimpl_->addModel(modelSource, textureSource, program);
}

OpenGL::OpenGLShaderProgram *
OpenGLWindow::addShader(const char *vertexShaderSource,
                        const char *fragmentShaderSource,
                        const char *geometryShaderSource)
{
    return pimpl_->addShader(vertexShaderSource, fragmentShaderSource,
                             geometryShaderSource);
}

void OpenGLWindow::frameBufferResizeEvent(Event::FrameBufferResizeEvent *event)
{
    pimpl_->frameBufferResizeEvent(event);
}

glm::ivec2 OpenGLWindow::frameBufferSize() const
{
    return pimpl_->frameBufferSize();
}

void OpenGLWindow::keyboardEvent(Event::KeyboardEvent *event)
{
    pimpl_->keyboardEvent(event);
}

void OpenGLWindow::mouseEvent(Event::MouseEvent *event)
{
    pimpl_->mouseEvent(event);
}

void OpenGLWindow::pushEvent(std::unique_ptr<Event::Event> &&event)
{
    pimpl_->pushEvent(std::move(event));
}

void OpenGLWindow::setWindowPosition(int x, int y)
{
    pimpl_->setWindowPosition(x, y);
}

void OpenGLWindow::setWindowPosition(const glm::ivec2 &position)
{
    pimpl_->setWindowPosition(position);
}

void OpenGLWindow::setWindowSize(const glm::ivec2 &size)
{
    pimpl_->setWindowSize(size);
}

void OpenGLWindow::setWindowSize(int width, int height)
{
    pimpl_->setWindowSize(width, height);
}

void OpenGLWindow::startRender() { pimpl_->startRender(); }

glm::ivec2 OpenGLWindow::windowPosition() const
{
    return pimpl_->windowPosition();
}

const GLFWwindow &OpenGLWindow::window() const { return pimpl_->window(); }

GLFWwindow &OpenGLWindow::window() { return pimpl_->window(); }

void OpenGLWindow::windowMoveEvent(Event::MoveEvent *event)
{
    pimpl_->windowMoveEvent(event);
}

void OpenGLWindow::windowResizeEvent(Event::WindowResizeEvent *event)
{
    pimpl_->windowResizeEvent(event);
}

glm::ivec2 OpenGLWindow::windowSize() const { return pimpl_->windowSize(); }

OpenGLWindow::Impl::Impl(const OpenGLWindowBuilder &builder)
    : window_{nullptr}, eventQueue_{}, eventHandlers_{},
      position_{builder.productPosition()}, windowSize_{builder.productSize()},
      frameBufferSize_{/* Not set until window is created */},
      title_{builder.productTitle()}, renderMode_{RenderMode::Fill},
      timeFrame_{/* Not set until window is created */},
      backgroundColor_{0.2f, 0.3f, 0.3f, 1.0f}, lookAt_{0},
      cameraPosition_{lookAt_ + glm::vec3{8}}
{
}

OpenGLWindow::Impl::~Impl() { destroy(); }

bool OpenGLWindow::Impl::addModel(const char *modelSource,
                                  const char *textureSource,
                                  OpenGL::OpenGLShaderProgram &program)
{
    OpenGL::OpenGLTexture *texture_ptr{nullptr};

    if (textureSource)
    {
        auto texture = Model::ModelFactory::loadTextureFromFile(textureSource);
        texture_ptr = texture.get();

        textures.push_back(std::move(texture));
    }

    std::string warning;
    std::string error;
    auto mesh = Model::ModelFactory::loadMeshFromFile(
        modelSource, warning, error, program, texture_ptr);

    if (!warning.empty())
    {
        std::cerr << "[Warning]\n" << warning;
    }

    if (!error.empty())
    {
        std::cerr << "[Error]\n" << error;
    }

    if (!mesh)
    {
        return false;
    }

    models_.push_back(std::move(mesh));

    return true;
}

OpenGL::OpenGLShaderProgram *
OpenGLWindow::Impl::addShader(const char *vertexShaderSource,
                              const char *fragmentShaderSource,
                              const char *geometryShaderSource)
{
    auto program{std::make_unique<OpenGL::OpenGLShaderProgram>()};
    if (!Detail::compileShaders(*program, vertexShaderSource,
                                fragmentShaderSource, geometryShaderSource))
    {
        return nullptr;
    }
    shaders_.push_back(std::move(program));

    return shaders_.back().get();
}

void OpenGLWindow::Impl::create(const glm::ivec2 &version, OpenGLWindow &window)
{
    if (!initializeOpenGL(version))
    {
        throw OpenGL::OpenGLException{"Failed to initialize OpenGL"};
    }

    if (!createWindow(window))
    {
        glfwTerminate();
        throw OpenGL::OpenGLException{"Failed to Create GLFW window"};
    }

    if (!initializeGLAD())
    {
        glfwTerminate();
        throw OpenGL::OpenGLException{"Failed to initialize GLAD"};
    }

    initializeDebug();

    initializeImgui();

    glEnable(GL_DEPTH_TEST);

    initializeEventQueue(window);

    setWindowPosition(position_);

    glm::ivec2 frame;
    glfwGetFramebufferSize(window_, &(frame.x), &(frame.y));
    updateFrameBufferSize(frame);
}

void OpenGLWindow::Impl::clearColor()
{
    glClearColor(backgroundColor_.x, backgroundColor_.y, backgroundColor_.z,
                 backgroundColor_.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool OpenGLWindow::Impl::createWindow(OpenGLWindow &window)
{
    window_ = glfwCreateWindow(windowWidth(), windowHeight(), title_.c_str(),
                               nullptr, nullptr);
    if (!window_)
    {
        return false;
    }
    glfwMakeContextCurrent(window_);

    glfwSetWindowUserPointer(window_, reinterpret_cast<void *>(&window));

    glfwSetWindowSizeCallback(window_, windowSizeCallback);
    glfwSetWindowPosCallback(window_, windowPositionCallback);
    glfwSetFramebufferSizeCallback(window_, frameBufferSizeCallback);
    glfwSetKeyCallback(window_, keyboardInputCallback);
    glfwSetMouseButtonCallback(window_, mouseButtonInputCallback);

    return true;
}

void OpenGLWindow::Impl::destroy()
{
    for (auto &model : models_)
    {
        model.reset(nullptr);
    }
    models_.clear();

    for (auto &texture : textures)
    {
        texture.reset(nullptr);
    }
    textures.clear();

    shaders_.clear();

    destroyImgui();
    destroyDebug();
    destroyOpenGL();
}

void OpenGLWindow::Impl::destroyDebug()
{
#if !defined(NDEBUG) && defined(GL_VERSION_4_3)
    if (GLAD_GL_VERSION_4_3)
    {
        GLint debugFlags;

        glGetIntegerv(GL_CONTEXT_FLAGS, &debugFlags);
        if (debugFlags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glDisable(GL_DEBUG_OUTPUT);
            glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        }
    }
#endif
}

void OpenGLWindow::Impl::destroyImgui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void OpenGLWindow::Impl::destroyOpenGL()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

glm::ivec2 OpenGLWindow::Impl::frameBufferSize() const
{
    return frameBufferSize_;
}

float OpenGLWindow::Impl::frameBufferAspectRatio() const
{
    return static_cast<float>(frameBufferWidth()) /
           static_cast<float>(frameBufferHeight());
}

int OpenGLWindow::Impl::frameBufferHeight() const { return frameBufferSize_.y; }

void OpenGLWindow::Impl::frameBufferResizeEvent(
    Event::FrameBufferResizeEvent *event)
{
    auto size{event->size()};
    frameBufferSize_ = size;
    glViewport(0, 0, size.x, size.y);
}

void OpenGLWindow::Impl::frameBufferSizeCallback(GLFWwindow *window, int width,
                                                 int height)
{
    auto time{glfwGetTimerValue()};

    if (auto who{
            reinterpret_cast<OpenGLWindow *>(glfwGetWindowUserPointer(window))})
    {
        auto before{who->frameBufferSize()};
        auto after{glm::ivec2{width, height}};

        who->pushEvent(std::make_unique<Event::FrameBufferResizeEvent>(
            after, before, time, window));
    }
}

int OpenGLWindow::Impl::frameBufferWidth() const { return frameBufferSize_.x; }

void OpenGLWindow::Impl::handleEvent(Event::Event *event)
{
    for (auto &handler : eventHandlers_)
    {
        if (handler->handle(event))
        {
            return;
        }
    }
}

void OpenGLWindow::Impl::initializeDebug()
{
#if !defined(NDEBUG) && defined(GL_VERSION_4_3)
    if (GLAD_GL_VERSION_4_3)
    {
        GLint debugFlags;

        glGetIntegerv(GL_CONTEXT_FLAGS, &debugFlags);
        if (debugFlags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(Logger::openGLDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                                  nullptr, GL_TRUE);
        }
    }
#endif
}

void OpenGLWindow::Impl::initializeEventQueue(OpenGLWindow &window)
{
    eventHandlers_.push_front(
        std::make_unique<Event::EventHandler<OpenGLWindow, Event::MoveEvent,
                                             &OpenGLWindow::windowMoveEvent>>(
            window));
    eventHandlers_.push_front(
        std::make_unique<
            Event::EventHandler<OpenGLWindow, Event::WindowResizeEvent,
                                &OpenGLWindow::windowResizeEvent>>(window));
    eventHandlers_.push_front(
        std::make_unique<
            Event::EventHandler<OpenGLWindow, Event::FrameBufferResizeEvent,
                                &OpenGLWindow::frameBufferResizeEvent>>(
            window));
    eventHandlers_.push_front(
        std::make_unique<Event::EventHandler<OpenGLWindow, Event::KeyboardEvent,
                                             &OpenGLWindow::keyboardEvent>>(
            window));
    eventHandlers_.push_front(
        std::make_unique<Event::EventHandler<OpenGLWindow, Event::MouseEvent,
                                             &OpenGLWindow::mouseEvent>>(
            window));
}

bool OpenGLWindow::Impl::initializeGLAD()
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void OpenGLWindow::Impl::initializeImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    PROGRAM_MAYBE_UNUSED(io)

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init(StringFormat::StringFormat("#version %d%d0",
                                                      GLVersion.major,
                                                      GLVersion.minor)
                               .c_str());
}

bool OpenGLWindow::Impl::initializeOpenGL(const glm::ivec2 &version)
{
    if (!glfwInit())
    {
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version[0]);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version[1]);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if !defined(NDEBUG) && defined(GL_VERSION_4_3)
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

#ifdef PROGRAM_SYSTEM_MACOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    return true;
}

bool OpenGLWindow::Impl::isRenderable() const
{
    return (frameBufferSize_.x > 0 &&
            frameBufferSize_.y >
                0); // At least contain 1 pixel in frame buffer.
}

void OpenGLWindow::Impl::keyboardEvent(Event::KeyboardEvent *event)
{
    if (event->key() == Event::KeyboardCode::Escape &&
        event->action() == Event::InputAction::Press)
    {
        glfwSetWindowShouldClose(window_, true);
    }
}

void OpenGLWindow::Impl::keyboardInputCallback(GLFWwindow *window, int key,
                                               int scancode, int action,
                                               int mods)
{
    auto time{glfwGetTimerValue()};

    if (auto who{
            reinterpret_cast<OpenGLWindow *>(glfwGetWindowUserPointer(window))})
    {
        who->pushEvent(std::make_unique<Event::KeyboardEvent>(
            key, action, scancode, time, window, mods));
    }
}

void OpenGLWindow::Impl::mouseEvent(Event::MouseEvent *event)
{
    PROGRAM_MAYBE_UNUSED(event);
}

void OpenGLWindow::Impl::mouseButtonInputCallback(GLFWwindow *window,
                                                  int button, int action,
                                                  int mods)
{
    auto time{glfwGetTimerValue()};
    glm::dvec2 position;
    glfwGetCursorPos(window, &(position.x), &(position.y));

    if (auto who{
            reinterpret_cast<OpenGLWindow *>(glfwGetWindowUserPointer(window))})
    {
        who->pushEvent(std::make_unique<Event::MouseEvent>(
            button, position, action, time, window, mods));
    }
}

void OpenGLWindow::Impl::pushEvent(std::unique_ptr<Event::Event> &&event)
{
    eventQueue_.push(std::move(event));
}

void OpenGLWindow::Impl::setWindowPosition(const glm::ivec2 &position)
{
    glfwSetWindowPos(window_, position.x, position.y);
}

void OpenGLWindow::Impl::setWindowPosition(int x, int y)
{
    setWindowPosition(glm::ivec2{x, y});
}

void OpenGLWindow::Impl::setWindowSize(const glm::ivec2 &size)
{
    glfwSetWindowSize(window_, size.x, size.y);
}

void OpenGLWindow::Impl::setWindowSize(int width, int height)
{
    setWindowSize(glm::ivec2{width, height});
}

void OpenGLWindow::Impl::startRender()
{
    timeFrame_ =
        std::make_unique<TimeFrame::TimeFrame>(glfwGetTimerFrequency());
    timeFrame_->start(glfwGetTimerValue());

    windowFrameLoop();

    timeFrame_->stop();
}

void OpenGLWindow::Impl::updateFrameBufferSize(const glm::ivec2 &frame)
{
    frameBufferSize_ = frame;
    glViewport(0, 0, frame.x, frame.y);
}

const GLFWwindow &OpenGLWindow::Impl::window() const { return *window_; }

GLFWwindow &OpenGLWindow::Impl::window() { return *window_; }

float OpenGLWindow::Impl::windowAspectRatio() const
{
    return static_cast<float>(windowWidth()) /
           static_cast<float>(windowHeight());
}

void OpenGLWindow::Impl::windowFrameEventUpdate()
{
    timeFrame_->update(glfwGetTimerValue());

    while (!eventQueue_.empty())
    {
        handleEvent(eventQueue_.front().get());
        eventQueue_.pop();
    }
}

void OpenGLWindow::Impl::windowFrameLoop()
{
    while (!(glfwWindowShouldClose(window_)))
    {
        windowFrameEventUpdate();

        clearColor();

        windowFrameRender();

        windowFrameRenderImguiUpdate();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void OpenGLWindow::Impl::windowFrameRender()
{
    if (!isRenderable())
    {
        return;
    }

    PRAGMA_WARNING_PUSH
    PRAGMA_WARNING_DISABLE_CONSTANTCONDITIONAL
    glm::mat4 view{glm::lookAt(cameraPosition_, lookAt_, glm::vec3{0, 1, 0}) *
                   glm::mat4(1)};
    PRAGMA_WARNING_POP

    glm::mat4 projection{glm::perspective(
        glm::radians(45.0f), frameBufferAspectRatio(), 0.1f, 100.0f)};

    for (auto &model : models_)
    {
        model->draw(view, projection);
    }
}

void OpenGLWindow::Impl::windowFrameRenderImguiUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    windowImguiGeneralSetting();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int OpenGLWindow::Impl::windowHeight() const { return windowSize_.y; }

void OpenGLWindow::Impl::windowImguiGeneralSetting()
{
    ImGui::Begin("Setting");
    ImGui::ColorEdit4("Background color", glm::value_ptr(backgroundColor_));
    ImGui::SliderFloat3("Camera Position", glm::value_ptr(cameraPosition_),
                        -20.0f, 20.0f);
    ImGui::SliderFloat3("Look At", glm::value_ptr(lookAt_), -20.0f, 20.0f);

    const char *items[] = {"Line", "Fill"};
    int current_item = renderMode_ - RenderMode::Line;
    if (ImGui::Combo("combo", &current_item, items, IM_ARRAYSIZE(items)))
    {
        renderMode_ = static_cast<RenderMode>(current_item + RenderMode::Line);
        glPolygonMode(GL_FRONT_AND_BACK, renderMode_);
    }

    double scale{timeFrame_->timeScale()};
    double min{0.0};
    double max{3.0};

    if (ImGui::SliderScalar("scale", ImGuiDataType_Double, &scale, &min, &max))
    {
        timeFrame_->setTimeScale(scale);
    }

    ImGui::Text("DeltaTime: [%f, %f]", timeFrame_->deltaTime(),
                timeFrame_->unscaledDeltaTime());
    ImGui::Text("Time: [%f, %f]", timeFrame_->time(),
                timeFrame_->unscaledTime());
    ImGui::Text("FPS: %f", 1 / timeFrame_->unscaledDeltaTime());

    ImGui::End();
}

void OpenGLWindow::Impl::windowMoveEvent(Event::MoveEvent *event)
{
    position_ = event->position();
}

glm::ivec2 OpenGLWindow::Impl::windowPosition() const { return position_; }

void OpenGLWindow::Impl::windowPositionCallback(GLFWwindow *window, int x,
                                                int y)
{
    auto time{glfwGetTimerValue()};

    if (auto who{
            reinterpret_cast<OpenGLWindow *>(glfwGetWindowUserPointer(window))})
    {
        auto before{who->windowPosition()};
        auto after{glm::ivec2{x, y}};

        who->pushEvent(
            std::make_unique<Event::MoveEvent>(after, before, time, window));
    }
}

void OpenGLWindow::Impl::windowResizeEvent(Event::WindowResizeEvent *event)
{
    windowSize_ = event->size();
}

glm::ivec2 OpenGLWindow::Impl::windowSize() const { return windowSize_; }

void OpenGLWindow::Impl::windowSizeCallback(GLFWwindow *window, int width,
                                            int height)
{
    auto time{glfwGetTimerValue()};

    if (auto who{
            reinterpret_cast<OpenGLWindow *>(glfwGetWindowUserPointer(window))})
    {
        auto before{who->windowSize()};
        auto after{glm::ivec2{width, height}};

        who->pushEvent(std::make_unique<Event::WindowResizeEvent>(
            after, before, time, window));
    }
}

int OpenGLWindow::Impl::windowWidth() const { return windowSize_.x; }

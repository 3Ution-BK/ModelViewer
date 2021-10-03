#include "OpenGLWindowBuilder.hpp"

#include <iostream>
#include <stdexcept>

class OpenGLWindowBuilder::Impl
{
public:
    explicit Impl();
    ~Impl();

    Impl(const Impl &other) = delete;
    Impl(Impl &&other) noexcept = delete;
    Impl &operator=(const Impl &other) = delete;
    Impl &operator=(Impl &&other) noexcept = delete;

    void setVersion(const glm::ivec2 &version);
    void setVersion(int major, int minor);

    void setPosition(const glm::ivec2 &position);
    void setPosition(int x, int y);

    void setSize(const glm::ivec2 &size);
    void setSize(int width, int height);

    void setTitle(const std::string &title);

    void reset();

    glm::ivec2 productVersion() const;
    glm::ivec2 productPosition() const;
    glm::ivec2 productSize() const;
    std::string productTitle() const;

    std::unique_ptr<OpenGLWindow> build(OpenGLWindowBuilder &me);

private:
    glm::ivec2 version_;
    glm::ivec2 position_;
    glm::ivec2 windowSize_;
    std::string title_;
};

OpenGLWindowBuilder::OpenGLWindowBuilder() : pimpl_{std::make_unique<Impl>()} {}

OpenGLWindowBuilder::~OpenGLWindowBuilder() = default;

std::unique_ptr<OpenGLWindow> OpenGLWindowBuilder::build()
{
    return pimpl_->build(*this);
}

glm::ivec2 OpenGLWindowBuilder::productVersion() const
{
    return pimpl_->productVersion();
}

glm::ivec2 OpenGLWindowBuilder::productPosition() const
{
    return pimpl_->productPosition();
}

glm::ivec2 OpenGLWindowBuilder::productSize() const
{
    return pimpl_->productSize();
}

std::string OpenGLWindowBuilder::productTitle() const
{
    return pimpl_->productTitle();
}

void OpenGLWindowBuilder::reset() { pimpl_->reset(); }

OpenGLWindowBuilder &
OpenGLWindowBuilder::setPosition(const glm::ivec2 &position)
{
    pimpl_->setPosition(position);
    return *this;
}

OpenGLWindowBuilder &OpenGLWindowBuilder::setPosition(int x, int y)
{
    pimpl_->setPosition(x, y);
    return *this;
}

OpenGLWindowBuilder &OpenGLWindowBuilder::setSize(const glm::ivec2 &size)
{
    pimpl_->setSize(size);
    return *this;
}

OpenGLWindowBuilder &OpenGLWindowBuilder::setSize(int width, int height)
{
    pimpl_->setSize(width, height);
    return *this;
}

OpenGLWindowBuilder &OpenGLWindowBuilder::setTitle(const std::string &title)
{
    pimpl_->setTitle(title);
    return *this;
}

OpenGLWindowBuilder &OpenGLWindowBuilder::setVersion(const glm::ivec2 &version)
{
    pimpl_->setVersion(version);
    return *this;
}

OpenGLWindowBuilder &OpenGLWindowBuilder::setVersion(int major, int minor)
{
    pimpl_->setVersion(major, minor);
    return *this;
}

OpenGLWindowBuilder::Impl::Impl() {}

OpenGLWindowBuilder::Impl::~Impl() = default;

std::unique_ptr<OpenGLWindow>
OpenGLWindowBuilder::Impl::build(OpenGLWindowBuilder &me)
{
    auto window{std::unique_ptr<OpenGLWindow>()};

    try
    {
        window = std::make_unique<OpenGLWindow>(me);
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }

    reset();

    return window;
}

glm::ivec2 OpenGLWindowBuilder::Impl::productVersion() const
{
    return version_;
}

glm::ivec2 OpenGLWindowBuilder::Impl::productPosition() const
{
    return position_;
}

glm::ivec2 OpenGLWindowBuilder::Impl::productSize() const
{
    return windowSize_;
}

std::string OpenGLWindowBuilder::Impl::productTitle() const { return title_; }

void OpenGLWindowBuilder::Impl::reset()
{
    version_ = glm::ivec2{4, 3};
    position_ = glm::ivec2{0, 0};
    windowSize_ = glm::ivec2{800, 600};
}

void OpenGLWindowBuilder::Impl::setPosition(const glm::ivec2 &position)
{
    position_ = position;
}

void OpenGLWindowBuilder::Impl::setPosition(int x, int y)
{
    setPosition(glm::ivec2{x, y});
}

void OpenGLWindowBuilder::Impl::setSize(const glm::ivec2 &size)
{
    windowSize_ = size;
}

void OpenGLWindowBuilder::Impl::setSize(int width, int height)
{
    setSize(glm::ivec2{width, height});
}

void OpenGLWindowBuilder::Impl::setTitle(const std::string &title)
{
    title_ = title;
}

void OpenGLWindowBuilder::Impl::setVersion(const glm::ivec2 &version)
{
    version_ = version;
}

void OpenGLWindowBuilder::Impl::setVersion(int major, int minor)
{
    setVersion(glm::ivec2{major, minor});
}

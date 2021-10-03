#include "TimeFrame.hpp"

#include "OpenGL/OpenGLLib.hpp"

#include "TimeFrameException.hpp"

namespace TimeFrame
{

namespace Detail
{

namespace Constant
{

const double normalTimeScale{1.0};

}

} // namespace Detail

class TimeFrame::Impl
{
public:
    explicit Impl(uint64_t frequency);
    ~Impl();

    Impl(const Impl &other);
    Impl(Impl &&other) noexcept;
    Impl &operator=(const Impl &other);
    Impl &operator=(Impl &&other) noexcept;

    void start(uint64_t now);
    void update(uint64_t now);
    void stop();

    void reset();
    void zero();

    double time() const noexcept;
    double unscaledTime() const noexcept;

    double unscaledDeltaTime() const noexcept;
    double deltaTime() const noexcept;
    size_t frameCount() const noexcept;

    void setTimeScale(double t) noexcept;
    double timeScale() const noexcept;

private:
    double frequency_;

    uint64_t start_;
    uint64_t now_;

    double timeScale_;

    double time_;
    double unscaledTime_;

    double deltaTime_;
    double unscaledDeltaTime_;

    size_t frameCount_;

    bool isActive_;
};

TimeFrame::TimeFrame(uint64_t frequency)
    : pimpl_{std::make_unique<Impl>(frequency)}
{
}

TimeFrame::TimeFrame(const TimeFrame &other)
    : pimpl_{std::make_unique<Impl>(*other.pimpl_)}
{
}

TimeFrame::TimeFrame(TimeFrame &&other) noexcept = default;

TimeFrame &TimeFrame::operator=(const TimeFrame &other)
{
    if (this != &other)
    {
        pimpl_ = std::make_unique<Impl>(*other.pimpl_);
    }
    return *this;
}

TimeFrame &TimeFrame::operator=(TimeFrame &&other) noexcept = default;

TimeFrame::~TimeFrame() = default;

double TimeFrame::deltaTime() const noexcept { return pimpl_->deltaTime(); }

size_t TimeFrame::frameCount() const noexcept { return pimpl_->frameCount(); }

void TimeFrame::reset() { pimpl_->reset(); }

void TimeFrame::setTimeScale(double t) noexcept { pimpl_->setTimeScale(t); }

void TimeFrame::start(uint64_t now) { pimpl_->start(now); }

void TimeFrame::stop() { pimpl_->stop(); }

double TimeFrame::time() const noexcept { return pimpl_->time(); }

double TimeFrame::timeScale() const noexcept { return pimpl_->timeScale(); }

double TimeFrame::unscaledDeltaTime() const noexcept
{
    return pimpl_->unscaledDeltaTime();
}

double TimeFrame::unscaledTime() const noexcept
{
    return pimpl_->unscaledTime();
}

void TimeFrame::update(uint64_t now) { pimpl_->update(now); }

void TimeFrame::zero() { pimpl_->zero(); }

TimeFrame::Impl::Impl(uint64_t frequency)
    : frequency_{static_cast<double>(frequency)}, start_{0}, now_{0},
      timeScale_{Detail::Constant::normalTimeScale}, time_{0.0},
      unscaledTime_{0.0}, deltaTime_{0.0}, unscaledDeltaTime_{0.0},
      frameCount_{0}, isActive_{false}
{
}

TimeFrame::Impl::Impl(const Impl &other) = default;

TimeFrame::Impl::Impl(Impl &&other) noexcept = default;

TimeFrame::Impl &TimeFrame::Impl::operator=(const Impl &other) = default;

TimeFrame::Impl &TimeFrame::Impl::operator=(Impl &&other) noexcept = default;

TimeFrame::Impl::~Impl() = default;

double TimeFrame::Impl::deltaTime() const noexcept { return deltaTime_; }

size_t TimeFrame::Impl::frameCount() const noexcept { return frameCount_; }

void TimeFrame::Impl::reset()
{
    if (isActive_)
    {
        throw TimeFrameException("reset is called when time frame is running.");
    }

    zero();
    timeScale_ = Detail::Constant::normalTimeScale;
}

void TimeFrame::Impl::setTimeScale(double t) noexcept
{
    timeScale_ = t;
    if (timeScale_ < 0.0)
    {
        timeScale_ = 0.0;
    }
}

void TimeFrame::Impl::start(uint64_t now)
{
    if (isActive_)
    {
        throw TimeFrameException("start is called when time frame is running.");
    }

    zero();

    start_ = now;
    now_ = now;

    isActive_ = true;
}

void TimeFrame::Impl::stop()
{
    if (!isActive_)
    {
        throw TimeFrameException(
            "stop is called when time frame is not running.");
    }
    isActive_ = false;
}

double TimeFrame::Impl::time() const noexcept { return time_; }

double TimeFrame::Impl::timeScale() const noexcept { return timeScale_; }

double TimeFrame::Impl::unscaledDeltaTime() const noexcept
{
    return unscaledDeltaTime_;
}

double TimeFrame::Impl::unscaledTime() const noexcept { return unscaledTime_; }

void TimeFrame::Impl::update(uint64_t now)
{
    if (!isActive_)
    {
        throw TimeFrameException(
            "update is called when time frame is not running.");
    }

    auto lastFrame{now_};
    now_ = now;

    unscaledDeltaTime_ = static_cast<double>(now_ - lastFrame) / frequency_;
    unscaledTime_ = static_cast<double>(now_ - start_) / frequency_;

    deltaTime_ = unscaledDeltaTime_ * timeScale_;
    time_ += deltaTime_;

    ++frameCount_;
}

void TimeFrame::Impl::zero()
{
    if (isActive_)
    {
        throw TimeFrameException("zero is called when time frame is running.");
    }

    start_ = 0;
    now_ = 0;

    time_ = 0.0;
    unscaledTime_ = 0.0;

    deltaTime_ = 0.0;
    unscaledDeltaTime_ = 0.0;

    frameCount_ = 0;
}

} // namespace TimeFrame

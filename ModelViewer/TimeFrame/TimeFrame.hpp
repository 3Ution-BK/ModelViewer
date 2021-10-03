#ifndef MODELVIEWER_TIMEFRAME_TIMEFRAME_HPP_
#define MODELVIEWER_TIMEFRAME_TIMEFRAME_HPP_

#include <memory>

namespace TimeFrame
{

/**
 * \brief This class represents the time frame.
 *
 * TimeFrame is used for calculate the time between frames. Measure the time
 * between each update and get specific time information.
 */
class TimeFrame
{
public:
    /**
     * \brief Initializes a new instance of the TimeFrame class with specified
     * frequency.
     *
     * \param frequency Specified frequency
     */
    explicit TimeFrame(uint64_t frequency);

    TimeFrame(const TimeFrame &other);
    TimeFrame(TimeFrame &&other) noexcept;
    TimeFrame &operator=(const TimeFrame &other);
    TimeFrame &operator=(TimeFrame &&other) noexcept;
    ~TimeFrame();

    /**
     * \brief start the TimeFrame with \p now as the start time.
     *
     * This function record the time infomation from \p now as the frame.
     * Use the Time::update to update the frame.
     *
     * \par Warning:
     * Do not call this function when running. Otherwise, it will throw
     * TimeFrameException.
     *
     * \param now start time
     *
     * \exception TimeFrameException TimeFrame is already running.
     */
    void start(uint64_t now);

    /**
     * \brief update the TimeFrame
     *
     * This function update the current frame and calculate the time infomation.
     *
     * \par Warning:
     * Remember to call start before calling this function. Otherwise, it will
     * throw TimeFrameException.
     *
     * \param now current time.
     *
     * \exception TimeFrameException TimeFrame is not running yet.
     */
    void update(uint64_t now);

    /**
     * \brief stop the TimeFrame
     *
     * Stop recording the frame.
     *
     * \par Warning:
     * Do not call this function when it stops. Otherwise, it will throw
     * TimeFrameException.
     *
     * \exception TimeFrameException TimeFrame is not running yet.
     */
    void stop();

    /**
     * \brief Reset the TimeFrame.
     *
     * This function tend to call zero and set the time scale to 1.0.
     *
     * \exception TimeFrameException TimeFrame is already running.
     *
     * \sa zero
     */
    void reset();

    /**
     * \brief Zero the TimeFrame.
     *
     * Unlike reset, this function reset the value to zero. It leaves the
     * timeScale untouched.
     *
     * \exception TimeFrameException TimeFrame is already running.
     *
     * \sa reset
     */
    void zero();

    /**
     * \brief The time from the start of the time frame to the last time
     * update is called.
     *
     * This value is influenced by timeScale.
     *
     * \return Requested time in second.
     *
     * \sa unscaledTime
     */
    double time() const noexcept;

    /**
     *  \brief The time from the start of the time frame to the last time
     * update is called.
     *
     * Unlike time, this value is not influenced by timeScale.
     *
     * \return Requested time in second.
     *
     * \sa time
     */
    double unscaledTime() const noexcept;

    /**
     * \brief The time period between the current frame and the last one.
     *
     * This value is influenced by timeScale.
     *
     * \return Requested time in second.
     */
    double deltaTime() const noexcept;

    /**
     * \brief The time period between the current and last frame.
     *
     * Unlike deltaTime, this value is not influenced by timeScale.
     *
     * \return Requested time in second.
     */
    double unscaledDeltaTime() const noexcept;

    /**
     * \brief How many frame has passed since the last time update is called.
     *
     * This value is equal to "how many time update is called".
     *
     * \return Requested value.
     */
    size_t frameCount() const noexcept;

    /**
     * \brief Sets the time scale of the class.
     *
     * \par
     * \p t cannot be smaller than 0. Otherwise, the value will set to 0.
     *
     * \param t specified value.
     *
     * \sa timeScale
     */
    void setTimeScale(double t) noexcept;

    /**
     * \brief Time scale value.
     *
     * This value determine the scale when the time passed.
     *
     * Everytime update is called, the scale will influenced the time
     * infomation. This value is useful for time effect likes slow motion.
     *
     * \par
     * * Default value is set to 1.0. This value represent the speed of the
     * realtime.
     * * When the value is set below 1.0, the time passes slower than the
     * realtime.
     * * When the value is set above 1.0, the time passes faster than the
     * realtime.
     * * When the value is set to 0.5, the time passes 2 times slower than the
     * realtime.
     * * When the value is set to 2, the time passes 2 times faster than the
     * realtime.
     * * When the value is set to 0, the time freezes.
     *
     * \return Requested value.
     *
     * \sa setTimeScale
     */
    double timeScale() const noexcept;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

} // namespace TimeFrame

#endif // MODELVIEWER_TIMEFRAME_TIMEFRAME_HPP_

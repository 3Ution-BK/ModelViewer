#ifndef MODELVIEWER_TIMEFRAME_TIMEFRAMEEXCEPTION_HPP_
#define MODELVIEWER_TIMEFRAME_TIMEFRAMEEXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace TimeFrame
{

/**
 * \brief This class represent the TimeFrame Exception.
 *
 * This class is used for throwing an exception about TimeFrame. It is derived
 * from std::runtime_error.
 */
class TimeFrameException : public std::runtime_error
{
public:
    /**
     * \brief Initializes a new instance of the TimeFrame Exception class with
     * specified \p message.
     *
     * \param message specified exception message.
     */
    explicit TimeFrameException(const char *message);

    /**
     * \overload
     *
     * \param message specified exception message.
     */
    explicit TimeFrameException(const std::string &message);
};

} // namespace TimeFrame

#endif // MODELVIEWER_TIMEFRAME_TIMEFRAMEEXCEPTION_HPP_

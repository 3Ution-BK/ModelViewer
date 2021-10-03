#include "TimeFrameException.hpp"

namespace TimeFrame
{

TimeFrameException::TimeFrameException(const char *message)
    : std::runtime_error{message}
{
}

TimeFrameException::TimeFrameException(const std::string &message)
    : std::runtime_error{message.c_str()}
{
}

} // namespace TimeFrame

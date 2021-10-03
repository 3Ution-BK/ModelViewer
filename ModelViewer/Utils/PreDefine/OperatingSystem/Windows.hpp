#ifndef MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_WINDOWS_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_WINDOWS_HPP_

/**
 * \def PROGRAM_SYSTEM_WINDOWS
 *
 * \brief This macro is defined if the target system is Windows.
 */

#if !defined(PROGRAM_DETAIL_OS_DETECTED)
    #if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
        #define PROGRAM_SYSTEM_WINDOWS
        #include "Detail/Detected.hpp"
    #endif
#endif

#endif // MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_WINDOWS_HPP_

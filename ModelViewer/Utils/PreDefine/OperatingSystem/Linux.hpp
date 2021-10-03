#ifndef MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_LINUX_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_LINUX_HPP_

/**
 * \def PROGRAM_SYSTEM_LINUX
 *
 * \brief This macro is defined if the target system is Linux.
 */

#if !defined(PROGRAM_DETAIL_OS_DETECTED)
    #if defined(__linux__)
        #define PROGRAM_SYSTEM_LINUX
        #include "Detail/Detected.hpp"
    #endif
#endif

#endif // MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_LINUX_HPP_

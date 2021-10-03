#ifndef MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_CYGWIN_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_CYGWIN_HPP_

/**
 * \def PROGRAM_SYSTEM_CYGWIN
 *
 * \brief This macro is defined if the target system is cygwin.
 */

#if !defined(PROGRAM_DETAIL_OS_DETECTED)
    #if defined(__CYGWIN__)
        #define PROGRAM_SYSTEM_CYGWIN
        #include "Detail/Detected.hpp"
    #endif
#endif

#endif // MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_CYGWIN_HPP_

#ifndef MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_MACOS_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_MACOS_HPP_

/**
 * \def PROGRAM_SYSTEM_MACOS
 *
 * \brief This macro is defined if the target system is MacOS (iOS not
 * included).
 */

/**
 * \def PROGRAM_SYSTEM_IOS
 *
 * \brief This macro is defined if the target system is iOS.
 */

#if !defined(PROGRAM_DETAIL_OS_DETECTED)
    #if defined(__APPLE__)
        #include <TargetConditionals.h>
        #if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
            #define PROGRAM_SYSTEM_IOS
        #elif TARGET_OS_IPHONE
            #define PROGRAM_SYSTEM_IOS
        #elif TARGET_OS_MAC
            #define PROGRAM_SYSTEM_MACOS
        #else
            #error "Unknown Apple platform"
        #endif

        #include "Detail/Detected.hpp"
    #endif
#endif

#endif // MODELVIEWER_UTILS_PREDEFINE_OPERATINGSYSTEM_MACOS_HPP_

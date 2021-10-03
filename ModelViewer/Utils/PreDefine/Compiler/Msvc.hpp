#ifndef MODELVIEWER_UTILS_PREDEFINE_COMPILER_MSVC_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_COMPILER_MSVC_HPP_

#include "Clang.hpp"
// clang will enable MSVC marco. Detect it first.

/**
 * \def PROGRAM_COMPILER_MSVC
 *
 * \brief This macro is defined if the compiler is using MSVC.
 */

#if !defined(PROGRAM_DETAIL_COMPILER_DETECTED)
    #if defined(_MSC_VER)
        #define PROGRAM_COMPILER_MSVC
        #include "Detail/Detected.hpp"
    #endif
#endif

#endif // MODELVIEWER_UTILS_PREDEFINE_COMPILER_MSVC_HPP_

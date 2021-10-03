#ifndef MODELVIEWER_UTILS_PREDEFINE_COMPILER_GCC_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_COMPILER_GCC_HPP_

#include "Clang.hpp"
// clang will enable MSVC marco. Detect it first.

/**
 * \def PROGRAM_COMPILER_GCC
 *
 * \brief This macro is defined if the compiler is using GNU C++.
 */

#if !defined(PROGRAM_DETAIL_COMPILER_DETECTED)
    #if defined(__GNUC__)
        #define PROGRAM_COMPILER_GCC
        #include "Detail/Detected.hpp"
    #endif
#endif

#endif // MODELVIEWER_UTILS_PREDEFINE_COMPILER_GCC_HPP_

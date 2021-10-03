#ifndef MODELVIEWER_UTILS_PREDEFINE_COMPILER_CLANG_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_COMPILER_CLANG_HPP_

/**
 * \def PROGRAM_COMPILER_CLANG
 *
 * \brief This macro is defined if the compiler is using clang.
 */

#if !defined(PROGRAM_DETAIL_COMPILER_DETECTED)
    #if defined(__clang__)
        #define PROGRAM_COMPILER_CLANG
        #include "Detail/Detected.hpp"
    #endif
#endif

#endif // MODELVIEWER_UTILS_PREDEFINE_COMPILER_CLANG_HPP_

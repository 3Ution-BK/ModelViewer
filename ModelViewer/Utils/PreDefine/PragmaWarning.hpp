#ifndef MODELVIEWER_UTILS_PREDEFINE_PRAGMAWARNING_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_PRAGMAWARNING_HPP_

#include "Compiler.hpp"

// clang-format off

/**
 * \def PRAGMA_TO(x)
 *
 * \brief Wrapper for general \c pragma
 */

/**
 * \def PRAGMA_WARNING_PUSH
 *
 * \brief Wrapper for general pragma definition
 * \code{.cpp}
 * #pragma GCC diagnostic push // GNU c++
 * #pragma warning(push) // MSVC
 * \endcode
 */

/**
 * \def PRAGMA_WARNING_POP
 *
 * \brief Wrapper for general pragma definition
 * \code{.cpp}
 * #pragma GCC diagnostic pop // GNU c++
 * #pragma warning(pop) // MSVC
 * \endcode
 */


/**
 * \def PRAGMA_WARNING_DISABLE(x)
 *
 * \brief Wrapper for general pragma definition
 * \code{.cpp}
 * #pragma GCC diagnostic ignored x // GNU c++
 * #pragma warning(disable : x) // MSVC
 * \endcode
 */

#if defined(PROGRAM_COMPILER_MSVC)
    #define PRAGMA_TO(x) __pragma(x)
    #define PRAGMA_WARNING_PUSH PRAGMA_TO(warning(push))
    #define PRAGMA_WARNING_POP PRAGMA_TO(warning(pop))
    #define PRAGMA_WARNING_DISABLE(x) PRAGMA_TO(warning(disable : x))
#elif defined(PROGRAM_COMPILER_GNU) || defined(PROGRAM_COMPILER_CLANG)
    #define PRAGMA_TO(x) _Pragma(#x)
    #define PRAGMA_WARNING_PUSH PRAGMA_TO(GCC diagnostic push)
    #define PRAGMA_WARNING_POP PRAGMA_TO(GCC diagnostic pop)
    #define PRAGMA_WARNING_DISABLE(x) PRAGMA_TO(GCC diagnostic ignored #x)
#elif defined(PROGRAM_COMPILER_CLANG)
    #define PRAGMA_TO(x) _Pragma(#x)
    #define PRAGMA_WARNING_PUSH PRAGMA_TO(GCC diagnostic push)
    #define PRAGMA_WARNING_POP PRAGMA_TO(GCC diagnostic pop)
    #define PRAGMA_WARNING_DISABLE(x) PRAGMA_TO(GCC diagnostic ignored #x)
#else
    #define PRAGMA_TO(x)
    #define PRAGMA_WARNING_PUSH
    #define PRAGMA_WARNING_POP
    #define PRAGMA_WARNING_DISABLE(x)
#endif

/**
 * \def PRAGMA_WARNING_DISABLE_UNREFERENCED_FORMAL_PARAMETER
 *
 * \brief Disable the following circumstance:
 * The formal parameter is not referenced in the body of the function.
 */
#if defined(PROGRAM_COMPILER_MSVC)
    #define PRAGMA_WARNING_DISABLE_UNREFERENCED_FORMAL_PARAMETER PRAGMA_WARNING_DISABLE(4100)
#elif defined(PROGRAM_COMPILER_GNU) || defined(PROGRAM_COMPILER_CLANG)
    #define PRAGMA_WARNING_DISABLE_UNREFERENCED_FORMAL_PARAMETER PRAGMA_WARNING_DISABLE(-Wunused-parameter)
#else
    #define PRAGMA_WARNING_DISABLE_UNREFERENCED_FORMAL_PARAMETER
#endif

/**
 * \def PRAGMA_WARNING_DISABLE_CONSTANTCONDITIONAL
 *
 * \brief Disable the following circumstance:
 * Controlling expression of an `if` or `while` loop is constant.
 */
#if defined(PROGRAM_COMPILER_MSVC)
    #define PRAGMA_WARNING_DISABLE_CONSTANTCONDITIONAL PRAGMA_WARNING_DISABLE(4127)
#else
    #define PRAGMA_WARNING_DISABLE_CONSTANTCONDITIONAL
#endif

/**
 * \def PRAGMA_WARNING_DISABLE_CONVERTION
 *
 * \brief Disable the following circumstance:
 * Conversion from one type to another type, it might lose some data.
 */
#if defined(PROGRAM_COMPILER_MSVC)
    #define PRAGMA_WARNING_DISABLE_CONVERTION PRAGMA_WARNING_DISABLE(4244)
#elif defined(PROGRAM_COMPILER_GNU) || defined(PROGRAM_COMPILER_CLANG)
    #define PRAGMA_WARNING_DISABLE_CONVERTION PRAGMA_WARNING_DISABLE(-Wconversion)
#else
    #define PRAGMA_WARNING_DISABLE_CONVERTION
#endif

/**
 * \def PRAGMA_WARNING_DISABLE_DOUBLEPROMOTION
 *
 * \brief Disable the following circumstance:
 * Single floating point in implicitly convert to double floating point.
 */
#if defined(PROGRAM_COMPILER_GNU) || defined(PROGRAM_COMPILER_CLANG)
    #define PRAGMA_WARNING_DISABLE_DOUBLEPROMOTION PRAGMA_WARNING_DISABLE(-Wdouble-promotion)
#else
    #define PRAGMA_WARNING_DISABLE_DOUBLEPROMOTION
#endif

/**
 * \def PRAGMA_WARNING_DISABLE_FLOATEQUAL
 *
 * \brief Disable the following circumstance:
 * Equal comparison is happened for floating-point value.
 */
#if defined(PROGRAM_COMPILER_GNU) || defined(PROGRAM_COMPILER_CLANG)
    #define PRAGMA_WARNING_DISABLE_FLOATEQUAL PRAGMA_WARNING_DISABLE(-Wfloat-equal)
#else
    #define PRAGMA_WARNING_DISABLE_FLOATEQUAL
#endif

/**
 * \def PRAGMA_WARNING_DISABLE_HIDE_PREVIOUS
 *
 * \brief Disable the following circumstance:
 * Declaration hides previous local declaration.
 */
#if defined(PROGRAM_COMPILER_MSVC)
    #define PRAGMA_WARNING_DISABLE_HIDE_PREVIOUS PRAGMA_WARNING_DISABLE(4456)
#else
    #define PRAGMA_WARNING_DISABLE_HIDE_PREVIOUS
#endif

/**
 * \def PRAGMA_WARNING_DISABLE_HIDE_FUNCTION_PARAMETER
 *
 * \brief Disable the following circumstance:
 * Declaration hides function parameter.
 */
#if defined(PROGRAM_COMPILER_MSVC)
    #define PRAGMA_WARNING_DISABLE_HIDE_FUNCTION_PARAMETER PRAGMA_WARNING_DISABLE(4457)
#else
    #define PRAGMA_WARNING_DISABLE_HIDE_FUNCTION_PARAMETER
#endif

/**
 * \def PRAGMA_WARNING_DISABLE_HIDE_CLASS_MEMBER
 *
 * \brief Disable the following circumstance:
 * Declaration hides class member.
 */
#if defined(PROGRAM_COMPILER_MSVC)
    #define PRAGMA_WARNING_DISABLE_HIDE_CLASS_MEMBER PRAGMA_WARNING_DISABLE(4458)
#else
    #define PRAGMA_WARNING_DISABLE_HIDE_CLASS_MEMBER
#endif

/**
 * \def PRAGMA_WARNING_DISABLE_UNREACHABLE_CODE
 *
 * \brief Disable the following circumstance:
 * Unreachable code. (The following code won't execute at any circumstance.)
 */
#if defined(PROGRAM_COMPILER_MSVC)
    #define PRAGMA_WARNING_DISABLE_UNREACHABLE_CODE PRAGMA_WARNING_DISABLE(4702)
#else
    #define PRAGMA_WARNING_DISABLE_UNREACHABLE_CODE
#endif

// clang-format on

#endif // MODELVIEWER_UTILS_PREDEFINE_PRAGMAWARNING_HPP_

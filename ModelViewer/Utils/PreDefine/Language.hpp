#ifndef MODELVIEWER_UTILS_PREDEFINE_LANGUAGE_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_LANGUAGE_HPP_

#include "Compiler.hpp"

#include <cstdio>

/**
 * \def PROGRAM_FALLTHROUGH
 *
 * \brief Intend to fallthrough in switch statement.
 *
 * This attribute is available for the following condition.
 *
 * * Cpp17: [[fallthrough]]
 * * gcc: [[gnu::fallthrough]] or __attribute__ ((fallthrough))
 * * clang: [[clang::fallthrough]] or [[gnu::fallthrough]]
 */

#if defined(__cplusplus)
    #if defined(__has_cpp_attribute)
        #if __has_cpp_attribute(fallthrough)
            #define PROGRAM_FALLTHROUGH [[fallthrough]]
        #endif
    #endif
#endif

#if !defined(PROGRAM_FALLTHROUGH)
    #if defined(PROGRAM_COMPILER_GCC)
        #if __has_attribute(gnu::fallthrough)
            #define PROGRAM_FALLTHROUGH [[gnu::fallthrough]]
        #elif __has_attribute(fallthrough)
            #define PROGRAM_FALLTHROUGH __attribute__((fallthrough))
        #endif
    #elif defined(PROGRAM_COMPILER_CLANG)
        #if __has_attribute(clang::fallthrough)
            #define PROGRAM_FALLTHROUGH [[clang::fallthrough]]
        #elif __has_attribute(gnu::fallthrough)
            #define PROGRAM_FALLTHROUGH [[gnu::fallthrough]]
        #endif
    #else
        #define PROGRAM_FALLTHROUGH ((void)(0))
    #endif
#endif

/**
 * \def PROGRAM_MAYBE_UNUSED(x)
 *
 * \brief This variable might not be used in this function.
 *
 * Use it to suppress the warning of unused variable.
 *
 * \note Suggest to use attribute \c maybe_unused if this program is compiled in
 * c++17.
 */
#define PROGRAM_MAYBE_UNUSED(x) ((void)(x));

// OpenGL related
#define PROGRAM_BUFFER_OFFSET(x) (static_cast<char *>(0) + (x))

/**
 * \def PROGRAM_ASSERT(expression)
 *
 * \brief Check whether the \c expression is true. If the \c expression is \c
 * false, print the message.
 *
 * This macro only works when \c NDEBUG is defined.
 *
 * Use it to check the value at runtime without terminating the program.
 *
 * \note Suggest to use \c assert in \c cassert header if the terminate process
 * is needed.
 */
#ifndef NDEBUG
    #define PROGRAM_ASSERT(expression)                                         \
        do                                                                     \
        {                                                                      \
            if (!(expression))                                                 \
            {                                                                  \
                fprintf(stderr, "[%s: %d]: Assertion `%s' failed.\n",          \
                        __FILE__, __LINE__, #expression);                      \
            }                                                                  \
        } while (0)
#else
    #define PROGRAM_ASSERT(expression) ((void)(0))
#endif

/**
 * \def PROGRAM_ASSERT_X(expression, message)
 *
 * \brief Check whether the \c expression is true. If the \c expression is \c
 * false, print the \c message.
 *
 * This macro only works when \c NDEBUG is defined.
 *
 * Use it to check the value at runtime without terminating the program.
 *
 * \note Suggest to use \c assert in \c cassert header if the terminate process
 * is needed.
 */

#ifndef NDEBUG
    #define PROGRAM_ASSERT_X(expression, message)                              \
        do                                                                     \
        {                                                                      \
            if (!(expression))                                                 \
            {                                                                  \
                fprintf(stderr, "[%s: %d]: %s\n", __FILE__, __LINE__,          \
                        message);                                              \
            }                                                                  \
        } while (0)
#else
    #define PROGRAM_ASSERT_X(expression, message) ((void)(0))
#endif

/**
 * \def PROGRAM_UNREACHABLE
 *
 * \brief This code cannot be reached. In some compiler, it can let the compiler
 * generate the optimized code.
 *
 * If NDEBUG was defined. It will warn you that the code was reached when the
 * program actually execute this code. It is useful for debugging.
 */

#if defined(PROGRAM_COMPILER_MSVC)
    #define PROGRAM_UNREACHABLE_IMPL __assume(0)
#elif defined(PROGRAM_COMPILER_GCC)
    #define PROGRAM_UNREACHABLE_IMPL __builtin_unreachable()
#elif defined(PROGRAM_COMPILER_CLANG)
    #if __has_builtin(__builtin_assume)
        #define PROGRAM_UNREACHABLE_IMPL __builtin_assume(false)
    #else
        #define PROGRAM_UNREACHABLE_IMPL ((void)(0))
    #endif
#else
    #define PROGRAM_UNREACHABLE_IMPL ((void)(0))
#endif

#define PROGRAM_UNREACHABLE                                                    \
    do                                                                         \
    {                                                                          \
        PROGRAM_ASSERT_X(false, "PROGRAM_UNREACHABLE reached");                \
        PROGRAM_UNREACHABLE_IMPL;                                              \
    } while (false)

#endif // MODELVIEWER_UTILS_PREDEFINE_LANGUAGE_HPP_

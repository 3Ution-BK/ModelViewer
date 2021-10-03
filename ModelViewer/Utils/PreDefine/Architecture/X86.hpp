#ifndef MODELVIEWER_UTILS_PREDEFINE_ARCHITECTURE_X86_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_ARCHITECTURE_X86_HPP_

/**
 * \def PROGRAM_ENVIRONMENT_32BIT
 *
 * \brief This macro is defined if the target architecture is 32-bit.
 */

/**
 * \def PROGRAM_ENVIRONMENT_64BIT
 *
 * \brief This macro is defined if the target architecture is 64-bit.
 */

#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) ||          \
    defined(__amd64) || defined(_M_X64) || defined(_M_AMD64)
    #define PROGRAM_ENVIRONMENT_64BIT
#elif defined(i386) || defined(__i386) || defined(__i386__) ||                 \
    defined(__i486__) || defined(__i586__) || defined(__i686__) ||             \
    defined(_M_IX86)
    #define PROGRAM_ENVIRONMENT_32BIT
#endif

#endif // MODELVIEWER_UTILS_PREDEFINE_ARCHITECTURE_X86_HPP_

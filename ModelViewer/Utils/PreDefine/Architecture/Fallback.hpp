#ifndef MODELVIEWER_UTILS_PREDEFINE_ARCHITECTURE_FALLBACK_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_ARCHITECTURE_FALLBACK_HPP_

#if !defined(PROGRAM_ENVIRONMENT_64BIT) && !defined(PROGRAM_ENVIRONMENT_32BIT)
    #include <cstdint>
    #if INTPTR_MAX == INT64_MAX
        #define PROGRAM_ENVIRONMENT_64BIT
    #elif INTPTR_MAX == INT32_MAX
        #define PROGRAM_ENVIRONMENT_32BIT
    #else
        #error                                                                 \
            "Cannot determine the architecture of the compiler or the architecture is not support."
    #endif
#endif

#endif // MODELVIEWER_UTILS_PREDEFINE_ARCHITECTURE_FALLBACK_HPP_

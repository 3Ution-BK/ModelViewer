/**
 * \file Architecture.hpp
 *
 * \brief General check for computer architecture.
 *
 * This file check the architecture of the computer.
 */

#ifndef MODELVIEWER_UTILS_PREDEFINE_ARCHITECTURE_HPP_
#define MODELVIEWER_UTILS_PREDEFINE_ARCHITECTURE_HPP_

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

#include "Architecture/Windows.hpp" // Windows suggest to use _WIN32 & _WIN64

#include "Architecture/X86.hpp" // x86 & AMD64

#include "Architecture/Fallback.hpp"

#endif // MODELVIEWER_UTILS_PREDEFINE_ARCHITECTURE_HPP_

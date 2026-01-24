//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_GAL_HPP
#define GAL_GAL_HPP

#ifdef GAL_VERBOSE
#define GAL_ERROR_LOGGING
#define GAL_WARNING_LOGGING
#define GAL_INFO_LOGGING
#endif // GAL_VERBOSE

#ifndef GAL_DONT_INCLUDE_GLAD
#include <glad/gl.h>
#endif
#ifndef GAL_DONT_INCLUDE_GLFW
#include <GLFW/glfw3.h>
#endif

#include "GAL/config.hpp"
#include "GAL/types.hpp"

#include "GAL/core/core.hpp"
#include "GAL/detail/detail.hpp"

#endif //GAL_GAL_HPP
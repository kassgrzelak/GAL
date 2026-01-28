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
#ifndef GAL_DONT_INCLUDE_GLM
#include "glmIncludes.hpp"
#endif

#include "types.hpp"

#include "core/core.hpp"
#include "debug/debug.hpp"
#include "detail/detail.hpp"
#include "graphics/graphics.hpp"
#include "system/system.hpp"

#endif //GAL_GAL_HPP
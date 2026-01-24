//
// Created by kassie on 22/01/2026.
//

#ifndef GAL_CORE_HPP
#define GAL_CORE_HPP

#if !defined(GAL_GAL_HPP) && !defined(GAL_DONT_INCLUDE_GLAD)
#include <glad/gl.h>
#endif
#if !defined(GAL_GAL_HPP) && !defined(GAL_DONT_INCLUDE_GLFW)
#include <GLFW/glfw3.h>
#endif

#include "enums.hpp"
#include "GALException.hpp"
#include "init.hpp"
#include "Window.hpp"

#endif //GAL_CORE_HPP
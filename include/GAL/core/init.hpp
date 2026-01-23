//
// Created by kassie on 23/01/2026.
//

#ifndef GAL_INIT_HPP
#define GAL_INIT_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "GAL/detail/ResourceRegistry.hpp"

namespace gal
{
	namespace detail
	{
		inline int openGLVersionMajor = -1;
		inline int openGLVersionMinor = -1;

		inline bool postGLInitialized = false;

		inline void postGLInit()
		{
			if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
				throwErr(ErrCode::GLADInitFailed, "Failed to initialize GLAD.");

			postGLInitialized = true;
		}
	}

	inline void init(const int openGLVersionMajor, const int openGLVersionMinor)
	{
		if (!glfwInit())
			detail::throwErr(ErrCode::GLFWInitFailed, "Failed to initialize GLFW.");

		detail::openGLVersionMajor = openGLVersionMajor;
		detail::openGLVersionMinor = openGLVersionMinor;
	}

	inline void terminate()
	{
		detail::openGLVersionMajor = -1;
		detail::openGLVersionMinor = -1;

		detail::resourceRegistry.destroyAll();

		glfwTerminate();
	}
}

#endif //GAL_INIT_HPP

//
// Created by kassie on 23/01/2026.
//

#ifndef GAL_INIT_HPP
#define GAL_INIT_HPP

#include "GAL/detail/ResourceRegistry.hpp"

namespace gal
{
	namespace detail
	{
		inline int g_openGLVersionMajor = -1;
		inline int g_openGLVersionMinor = -1;

		inline bool g_postGLInitialized = false;

		/// @brief Initialization that can only be done after an OpenGL context has been created.
		inline void postGLInit()
		{
			const int version = gladLoadGL(glfwGetProcAddress);
			if (!version)
				throwErr(ErrCode::GLADInitFailed, "Failed to initialize GLAD.");

			const int major = GLAD_VERSION_MAJOR(version);
			const int minor = GLAD_VERSION_MINOR(version);

			logInfoStart() << "Initialized GLAD with OpenGL " << major << "." << minor << logInfoEnd;

			if (major != g_openGLVersionMajor or minor != g_openGLVersionMinor)
				logWarnStart() << "Initialized GLAD with a different version of OpenGL (" << major << "." << minor <<
						") than was specified in the call to gal::init()." << logWarnEnd;

			g_postGLInitialized = true;
		}
	}

	inline void init(const int openGLVersionMajor = 4, const int openGLVersionMinor = 6)
	{
		if (!glfwInit())
			detail::throwErr(ErrCode::GLFWInitFailed, "Failed to initialize GLFW.");

		detail::g_openGLVersionMajor = openGLVersionMajor;
		detail::g_openGLVersionMinor = openGLVersionMinor;
	}

	inline void terminate()
	{
		detail::g_openGLVersionMajor = -1;
		detail::g_openGLVersionMinor = -1;

		detail::g_postGLInitialized = false;

		detail::g_resourceRegistry.destroyAll();

		glfwTerminate();
	}
}

#endif //GAL_INIT_HPP

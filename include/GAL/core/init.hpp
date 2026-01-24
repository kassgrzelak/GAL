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
		inline int openGLVersionMajor = -1;
		inline int openGLVersionMinor = -1;

		inline bool postGLInitialized = false;

		/// @brief Initialization that can only be done after an OpenGL context has been created.
		inline void postGLInit()
		{
			const int version = gladLoadGL(glfwGetProcAddress);
			if (!version)
				throwErr(ErrCode::GLADInitFailed, "Failed to initialize GLAD.");

			const int major = GLAD_VERSION_MAJOR(version);
			const int minor = GLAD_VERSION_MINOR(version);

			logInfoStart() << "Initialized GLAD with OpenGL " << major << "." << minor << logInfoEnd;

			if (major != openGLVersionMajor or minor != openGLVersionMinor)
				logWarnStart() << "Initialized GLAD with a different version of OpenGL (" << major << "." << minor <<
						") than was specified in the call to gal::init()." << logWarnEnd;

			postGLInitialized = true;
		}
	}

	inline void init(const int openGLVersionMajor = 4, const int openGLVersionMinor = 6)
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

		detail::postGLInitialized = false;

		detail::resourceRegistry.destroyAll();

		glfwTerminate();
	}
}

#endif //GAL_INIT_HPP

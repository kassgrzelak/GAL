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

		/// @brief Initialization that can only be done after an OpenGL context has been created. Mainly initialization
		/// of glad.
		inline void postGLInit()
		{
			logInfo("Post-GL initializing GAL...");
			logIncreaseIndent();

			const int version = gladLoadGL(glfwGetProcAddress);
			if (!version)
				throwErr(ErrCode::GLADInitFailed, "Failed to initialize GLAD.");

			const int major = GLAD_VERSION_MAJOR(version);
			const int minor = GLAD_VERSION_MINOR(version);

			logInfoStart() << "Initialized GLAD with OpenGL " << major << "." << minor << "." << logInfoEnd;

			if (major != g_openGLVersionMajor or minor != g_openGLVersionMinor)
				logWarnStart() << "Initialized GLAD with a different version of OpenGL (" << major << "." << minor <<
						") than was specified in the call to gal::init()." << logWarnEnd;

			g_postGLInitialized = true;

			logInfo("Successfully post-GL initialized GAL.");
			logDecreaseIndent();
		}
	}

	/// @brief Initialize GLFW, setting window hints for OpenGL version and profile with the given values. You must call
	/// this before calling almost any other GAL function.
	/// @param openGLVersionMajor Major OpenGL version. The default is 4 as this is what the vendored glad was generated
	/// for. If supplying your own glad, change this accordingly.
	/// @param openGLVersionMinor Minor OpenGL version. The default is 6 as this is what the vendored glad was generated
	/// for. If supplying your own glad, change this accordingly.
	/// @param contextProfile The OpenGL context profile to use. The default is GLFW_OPENGL_CORE_PROFILE as this is what
	/// the vendored glad was generated for. If supplying your own glad, change this accordingly.
	/// @param debugContext Whether to set the window hint for a debug context.
	/// @throws ErrCode::GLFWInitFailed If GLFW initialization fails for any reason.
	inline void init(const int openGLVersionMajor = 4, const int openGLVersionMinor = 6,
	                 const int contextProfile = GLFW_OPENGL_CORE_PROFILE, const bool debugContext = false)
	{
		detail::logInfo("Initializing gal...");
		detail::logIncreaseIndent();

		if (!glfwInit())
			detail::throwErr(ErrCode::GLFWInitFailed, "Failed to initialize GLFW.");

		detail::logInfo("Initialized GLFW.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGLVersionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGLVersionMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, contextProfile);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // This represents both the beginning and end of my
		// bothering to make GAL compatible with macOS.
#endif

		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, debugContext);

		detail::g_openGLVersionMajor = openGLVersionMajor;
		detail::g_openGLVersionMinor = openGLVersionMinor;

		detail::logInfo("Successfully initialized GAL.");
		detail::logDecreaseIndent();
	}

	/// @brief Terminate GAL. This resets all internal state back to default values, terminates GLFW, and destroys any
	/// resources allocated by GAL.
	inline void terminate() noexcept
	{
		detail::logInfo("Terminating GAL...");
		detail::logIncreaseIndent();

		detail::g_openGLVersionMajor = -1;
		detail::g_openGLVersionMinor = -1;

		detail::g_postGLInitialized = false;

		detail::g_resourceRegistry.destroyAll();
		detail::logInfo("Destroyed all GAL resources.");

		glfwTerminate();
		detail::logInfo("Terminated GLFW.");

		detail::logInfo("Terminated GAL.");
		detail::logDecreaseIndent();
	}
}

#endif //GAL_INIT_HPP

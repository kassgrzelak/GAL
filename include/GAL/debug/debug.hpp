//
// Created by kassie on 24/01/2026.
//

#ifndef GAL_DEBUG_HPP
#define GAL_DEBUG_HPP

namespace gal
{
	namespace detail
	{
		inline void defaultGLFWErrorCallback(const int errorCode, const char* description)
		{
			logErrStart() << errorCode << " " << description << logErrEnd;
		}
	}

	inline void setOpenGLDebugMessageCallback()
	{

	}

	inline void clearOpenGLDebugMessageCallback()
	{
		
	}

	inline void setGLFWErrorCallback(const GLFWerrorfun callback)
	{
		glfwSetErrorCallback(callback);
	}

	inline void clearGLFWErrorCallback()
	{
		setGLFWErrorCallback(nullptr);
	}

	inline void attachDefaultOpenGLDebugMessageCallback()
	{
		// TODO: OpenGL default debug message callback set function.
	}

	inline void attachDefaultGLFWErrorCallback()
	{
		glfwSetErrorCallback(detail::defaultGLFWErrorCallback);
	}
}

#endif //GAL_DEBUG_HPP
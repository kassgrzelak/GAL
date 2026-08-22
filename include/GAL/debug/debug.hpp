//
// Created by kassie on 24/01/2026.
//

#ifndef GAL_DEBUG_HPP
#define GAL_DEBUG_HPP
#include "GAL/core/enums.hpp"

namespace gal
{
	namespace detail
	{
		/**
		 * @brief Default GLFW error callback, set by attachDefaultErrorCallback().
		 */
		inline void defaultErrorCallback(const int errorCode, const char* description)
		{
			logErrStart() << errorCode << " " << description << logErrEnd;
		}
		
		/**
		 * @brief Default OpenGL debug message callback, set by attachDefaultDebugMessageCallback();
		 */
		inline void defaultDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, 
			const GLchar* message, const void* userParam)
		{
			switch (static_cast<DebugMessageSeverity>(severity))
			{
				case DebugMessageSeverity::High:
					std::cerr << "\u001b[31mOpenGL Debug Message\nSeverity: High\n"; break;
				case DebugMessageSeverity::Medium:
					std::cerr << "\u001b[33mOpenGL Debug Message\nSeverity: Medium\n"; break;
				case DebugMessageSeverity::Low:
					std::cerr << "\u001b[33mOpenGL Debug Message\nSeverity: Low\n"; break;
				case DebugMessageSeverity::Notification:
					std::cerr << "OpenGL Debug Message\nSeverity: Notification\n"; break;
			}
			
			switch (static_cast<DebugMessageSource>(source))
			{
				case DebugMessageSource::API:
					std::cerr << "Source: " << "API\n"; break;
				case DebugMessageSource::WindowSystem:
					std::cerr << "Source: " << "Window system\n"; break;
				case DebugMessageSource::ShaderCompiler:
					std::cerr << "Source: " << "Shader compiler\n"; break;
				case DebugMessageSource::ThirdParty:
					std::cerr << "Source: " << "Third party\n"; break;
				case DebugMessageSource::Application:
					std::cerr << "Source: " << "Application\n"; break;
				case DebugMessageSource::Other:
					std::cerr << "Source: " << "Other\n"; break;
			}
			
			switch  (static_cast<DebugMessageType>(type))
			{
				case DebugMessageType::Error:
					std::cerr << "Type: Error\n"; break;
				case DebugMessageType::DeprecatedBehavior:
					std::cerr << "Type: Deprecated Behavior\n"; break;
				case DebugMessageType::UndefinedBehavior:
					std::cerr << "Type: Undefined Behavior\n"; break;
				case DebugMessageType::Portability:
					std::cerr << "Type: Portability\n"; break;
				case DebugMessageType::Performance:
					std::cerr << "Type: Performance\n"; break;
				case DebugMessageType::Marker:
					std::cerr << "Type: Marker\n"; break;
				case DebugMessageType::PushGroup:
					std::cerr << "Type: Push Group\n"; break;
				case DebugMessageType::PopGroup:
					std::cerr << "Type: Pop Group\n"; break;
				case DebugMessageType::Other:
					std::cerr << "Type: Other\n"; break;
			}
			
			std::cerr << "ID: " << id << "\n";
			
			if (length < 0)
				std::cerr << "Message: " << message << "\n";
			else 
				fprintf(stderr, "%*s\n", length, message);
			
			std::cerr << "\u001b[0m";
		}
	}

	/**
	 * @brief Set the OpenGL debug message callback.
	 * @param callback The debug message callback to set.
	 * @param synchronous If true, enable GL_DEBUG_OUTPUT_SYNCHRONOUS so the debug message callback is called in the 
	 * same thread as the context and in the same scope as the OpenGL function call that triggered the message.
	 * @param userParam A pointer to any object, which will be passed along to the debug message callback.
	 */
	inline void setDebugMessageCallback(const GLDEBUGPROC callback, const bool synchronous = false, const void* userParam = nullptr)
	{
		glEnable(GL_DEBUG_OUTPUT);
		
		if (synchronous)
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		
		glDebugMessageCallback(callback, userParam);
	}

	inline void clearDebugMessageCallback()
	{
		glDisable(GL_DEBUG_OUTPUT);
		glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(nullptr, nullptr);
	}

	inline void setErrorCallback(const GLFWerrorfun callback)
	{
		glfwSetErrorCallback(callback);
	}

	inline void clearErrorCallback()
	{
		setErrorCallback(nullptr);
	}

	inline void attachDefaultDebugMessageCallback(const bool synchronous = false, const void* userParam = nullptr)
	{
		setDebugMessageCallback(detail::defaultDebugMessageCallback, synchronous, userParam);
	}

	inline void attachDefaultErrorCallback()
	{
		glfwSetErrorCallback(detail::defaultErrorCallback);
	}
}

#endif //GAL_DEBUG_HPP
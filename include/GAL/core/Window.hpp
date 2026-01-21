//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_WINDOW_HPP
#define GAL_WINDOW_HPP

#include <GAL/detail/UniqueHandle.hpp>
#include <GLFW/glfw3.h>

namespace gal
{
	namespace detail
	{
		inline void windowDeleter(GLFWwindow* window) noexcept
		{
			glfwDestroyWindow(window);
		}

		using UniqueWindow = UniqueHandle<GLFWwindow*, nullptr, windowDeleter>;
	}

	class Window : detail::UniqueWindow
	{
	public:
		Window()
		{
			GLFWwindow* windowPtr = glfwCreateWindow(800, 600, "test", nullptr, nullptr);

			setHandle(windowPtr);
		}

		GAL_NODISCARD bool shouldClose() const noexcept
		{
			return glfwWindowShouldClose(getHandle());
		}
	};
}

#endif //GAL_WINDOW_HPP

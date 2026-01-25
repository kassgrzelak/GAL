//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_WINDOW_HPP
#define GAL_WINDOW_HPP

#include <GAL/detail/UniqueHandle.hpp>

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

	/// @brief Wrapper around GLFWwindow. As in GLFW, a window is inextricably linked with an OpenGL context; this
	/// encapsulates them both.
	class Window : detail::UniqueWindow
	{
	public:
		/// @brief Create a window with the given parameters.
		/// @param width Initial width of the window in pixels.
		/// @param height Initial height of the window in pixels.
		/// @param title Title of the window.
		/// @param monitor The monitor to use for fullscreen mode. Default is nullptr which is windowed mode.
		/// @param share Monitor to share context with. If setting this, make sure to set makeContextCurrent to false.
		/// @param resizable Sets the GLFW_RESIZABLE window hint to true. You still need to set a framebuffer size
		/// callback.
		/// @param vsync Calls glfwSwapInterval(1) if true.
		/// @param makeContextCurrent Whether to make the context created with this new window current or not.
		/// @throws ErrCode::CreateWindowFailed If window creation fails for any reason.
		/// @throws ErrCode::GLADInitFailed If glad hasn't already been initialized and initializing it fails for any
		/// reason.
		Window(const int width, const int height, const char* title, GLFWmonitor* monitor = nullptr,
		       GLFWwindow* share = nullptr, const bool resizable = false, const bool vsync = false,
		       const bool makeContextCurrent = true)
		{
			detail::logInfo("Creating window...");
			detail::logIncreaseIndent();
			glfwWindowHint(GLFW_RESIZABLE, resizable);

			GLFWwindow* windowPtr = glfwCreateWindow(width, height, title, monitor, share);
			if (!windowPtr)
			{
				resetConstructorWindowHints();
				detail::throwErr(ErrCode::CreateWindowFailed, "Failed to create window.");
			}
			detail::logInfo("Successfully created GLFWwindow object.");

			if (makeContextCurrent)
				glfwMakeContextCurrent(windowPtr);

			if (!detail::g_postGLInitialized)
				detail::postGLInit();

			if (vsync)
				glfwSwapInterval(1);

			setHandle(windowPtr);
			detail::logInfo("Successfully created window.");
			detail::logDecreaseIndent();
		}

		/// @brief Get the GLFWwindow* for this window for use with GLFW functions.
		GAL_NODISCARD GLFWwindow* getWindowHandle() const noexcept { return getHandle(); }
		/// @brief Get whether this window should close or not.
		GAL_NODISCARD bool shouldClose() const noexcept { return glfwWindowShouldClose(getHandle()); }
		/// @brief Get the current width of the window.
		GAL_NODISCARD int getWidth() const noexcept
		{
			int width;
			glfwGetWindowSize(getHandle(), &width, nullptr);
			return width;
		}
		/// @brief Get the current height of the window.
		GAL_NODISCARD int getHeight() const noexcept
		{
			int height;
			glfwGetWindowSize(getHandle(), nullptr, &height);
			return height;
		}

		/// @brief Set the width of the window.
		/// @param width The new width of the window.
		void setWidth(const int width) const noexcept { glfwSetWindowSize(getHandle(), width, getHeight()); }
		/// @brief Set the height of the window.
		/// @param height The new height of the window.
		void setHeight(const int height) const noexcept { glfwSetWindowSize(getHandle(), getWidth(), height); }
		/// @brief Set the size of the window.
		/// @param width The new width of the window.
		/// @param height The new height of the window.
		void setSize(const int width, const int height) const noexcept { glfwSetWindowSize(getHandle(), width, height); }

	private:
		/// @brief Reset any window hints set in the constructor to their defaults in the event an error is thrown.
		static void resetConstructorWindowHints()
		{
			glfwWindowHint(GLFW_RESIZABLE, false);
		}
	};
}

#endif //GAL_WINDOW_HPP

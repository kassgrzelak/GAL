//
// Created by kassie on 28/01/2026.
//

#ifndef GAL_TIME_HPP
#define GAL_TIME_HPP

namespace gal
{
	namespace detail
	{
		inline double g_lastProgramTime = 0.0;
		inline double g_programTime = 0.0;

		inline void updateTime()
		{
			g_lastProgramTime = g_programTime;
			g_programTime = glfwGetTime();
		}
	}

	
	/**
	 * @brief Get the time elapsed since gal::init() was called.
	 * @tparam T The numeric type to static_cast the time value to. Default is double.
	 * @return The time, in seconds, since gal::init() was called, static_casted to T.
	 */
	template<typename T = double>
	T getTime() noexcept
	{
		return static_cast<T>(detail::g_programTime);
	}

	/**
	 * @brief Get time between the last two calls to Window::pollEvents().
	 * @tparam T The numeric type to static_cast the delta time value to. Default is double.
	 * @return The time, in seconds, elapsed between the last two calls to Window::pollEvents(), static_casted to T.
	 */
	template<typename T = double>
	T getDeltaTime() noexcept
	{
		return static_cast<T>(detail::g_programTime - detail::g_lastProgramTime);
	}
}

#endif //GAL_TIME_HPP
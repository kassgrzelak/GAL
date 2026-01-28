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

	/// @brief Get current program time.
	template<typename T = double>
	T getTime()
	{
		return static_cast<T>(detail::g_programTime);
	}

	/// @brief Get time between the last two calls to Window::pollEvents().
	template<typename T = double>
	T getDeltaTime()
	{
		return static_cast<T>(detail::g_programTime - detail::g_lastProgramTime);
	}
}

#endif //GAL_TIME_HPP
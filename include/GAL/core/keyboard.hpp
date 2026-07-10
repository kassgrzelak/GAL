//
// Created by kassie on 26/01/2026.
//

#ifndef GAL_KEYBOARD_HPP
#define GAL_KEYBOARD_HPP

#include <array>

namespace gal
{
	namespace detail
	{
		// First valid GLFW key code.
		constexpr int FIRST_KEY_CODE = 32;
		constexpr int KEY_CODE_NUM = GLFW_KEY_LAST + 1;

		inline std::array<uint8_t, KEY_CODE_NUM> g_prevKeyStates;
		inline std::array<uint8_t, KEY_CODE_NUM> g_currKeyStates;

		/// @brief Update internal key states.
		inline void updateKeyStates(GLFWwindow* window)
		{
			std::move(g_currKeyStates.begin(), g_currKeyStates.end(), g_prevKeyStates.begin());

			for (int key = FIRST_KEY_CODE; key < KEY_CODE_NUM; ++key)
				g_currKeyStates[key] = glfwGetKey(window, key) == GLFW_PRESS;
		}

		/// @brief Check if a key is in the valid range.
		inline bool isValidKey(const int key)
		{
			return key < KEY_CODE_NUM && key >= 0;
		}
	}

	/// @brief Check if a key has been pressed this frame.
	/// @param key The GLFW key token to check.
	/// @returns True if the key was pressed this frame (not if it stayed pressed since a previous frame), false
	/// if not or if key is not a valid GLFW key token.
	[[nodiscard]] inline bool isKeyPressed(const int key)
	{
		if (!detail::isValidKey(key))
			return false;

		return detail::g_currKeyStates[key] && !detail::g_prevKeyStates[key];
	}

	/// @brief Check if a key has been released this frame.
	/// @param key The GLFW key token to check.
	/// @returns True if the key was released this frame (not if it stayed released since a previous frame), false
	/// if not or if key is not a valid GLFW key token.
	[[nodiscard]] inline bool isKeyReleased(const int key)
	{
		if (!detail::isValidKey(key))
			return false;

		return detail::g_currKeyStates[key] && !detail::g_prevKeyStates[key];
	}

	/// @brief Check if a key is currently pressed.
	/// @param key The GLFW key token to check.
	/// @returns True if the key is pressed, false if not or if key is not a valid GLFW key token.
	[[nodiscard]] inline bool isKeyDown(const int key)
	{
		if (!detail::isValidKey(key))
			return false;

		return detail::g_currKeyStates[key];
	}

	/// @brief Check if a key is not currently pressed.
	/// @param key The GLFW key token to check.
	/// @returns True if the key is not pressed, false if not or if key is not a valid GLFW key token.
	[[nodiscard]] inline bool isKeyUp(const int key)
	{
		if (!detail::isValidKey(key))
			return false;

		return !detail::g_currKeyStates[key];
	}
}

#endif //GAL_KEYBOARD_HPP

//
// Created by kassie on 23/01/2026.
//

#ifndef GAL_ENUMS_HPP
#define GAL_ENUMS_HPP

namespace gal
{
	/// @brief Enum of all the various errors that can occur in GAL.
	enum class ErrCode
	{
		// Init.
		GLFWInitFailed, // Failed to initialize GLFW.
		GLADInitFailed, // Failed to initialize GLAD.

		// Window.
		CreateWindowFailed, // Failed to create window.
	};

	/// @brief Convert a GAL error code to a string of its name.
	/// @param errCode Error code to convert to string.
	GAL_NODISCARD inline const char* errCodeToString(const ErrCode errCode)
	{
		switch (errCode)
		{
			case ErrCode::GLFWInitFailed: return "GLFWInitFailed";
			case ErrCode::GLADInitFailed: return "GLADInitFailed";

			case ErrCode::CreateWindowFailed: return "CreateWindowFailed";
		}

		return "Unknown. The developer probably forgot to add this ErrCode to the switch statement.";
	}
}

#endif //GAL_ENUMS_HPP

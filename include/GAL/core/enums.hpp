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

		// Program.
		CreateProgramFailed, // Failed to create program.
		ProgramLinkFailed, // Failed to link program.
		NonExistentShaderUniform, // Attempted to set non-existent shader uniform.

		// Shader.
		CreateShaderFailed, // Failed to create shader.
		ShaderCompilationFailed, // Failed to compile shader.
		ShaderFileReadFailed, // Failed to read shader source file.
	};

	/// @brief Convert a GAL error code to a string of its name.
	/// @param errCode Error code to convert to string.
	[[nodiscard]] inline const char* errCodeToString(const ErrCode errCode)
	{
		switch (errCode)
		{
			case ErrCode::GLFWInitFailed: return "GLFWInitFailed";
			case ErrCode::GLADInitFailed: return "GLADInitFailed";

			case ErrCode::CreateWindowFailed: return "CreateWindowFailed";

			case ErrCode::CreateProgramFailed: return "CreateProgramFailed";

			case ErrCode::CreateShaderFailed: return "CreateShaderFailed";
			case ErrCode::ShaderCompilationFailed: return "ShaderCompilationFailed";
			case ErrCode::ShaderFileReadFailed: return "ShaderFileReadFailed";
		}

		return "Unknown. The developer probably forgot to add this ErrCode to the switch statement.";
	}

	/// @brief Enum of all possible shader types.
	/// Values align with GL enums of the same names.
	enum class ShaderType : GLenum
	{
		Compute = GL_COMPUTE_SHADER,
		Vertex = GL_VERTEX_SHADER,
		TessControl = GL_TESS_CONTROL_SHADER,
		TessEvaluation = GL_TESS_EVALUATION_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};
}

#endif //GAL_ENUMS_HPP

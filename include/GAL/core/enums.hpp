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
		// Buffer.
		CreateBufferFailed, // Failed to create buffer.

		// Init.
		GLFWInitFailed, // Failed to initialize GLFW.
		GLADInitFailed, // Failed to initialize GLAD.

		// Program.
		CreateProgramFailed, // Failed to create program.
		ProgramLinkFailed, // Failed to link program.
		NonExistentShaderUniform, // Attempted to set non-existent shader uniform.

		// Shader.
		CreateShaderFailed, // Failed to create shader.
		ShaderCompilationFailed, // Failed to compile shader.
		ShaderFileReadFailed, // Failed to read shader source file.

		// Window.
		CreateWindowFailed, // Failed to create window.
	};

	/// @brief Convert a GAL error code to a string of its name.
	/// @param errCode Error code to convert to string.
	[[nodiscard]] inline const char* errCodeToString(const ErrCode errCode)
	{
		switch (errCode)
		{
			case ErrCode::CreateBufferFailed: return "CreateBufferFailed";

			case ErrCode::GLFWInitFailed: return "GLFWInitFailed";
			case ErrCode::GLADInitFailed: return "GLADInitFailed";

			case ErrCode::CreateWindowFailed: return "CreateWindowFailed";

			case ErrCode::CreateProgramFailed: return "CreateProgramFailed";
			case ErrCode::ProgramLinkFailed: return "ProgramLinkFailed";
			case ErrCode::NonExistentShaderUniform: return "NonExistentShaderUniform";

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
		Compute        = GL_COMPUTE_SHADER,
		Vertex         = GL_VERTEX_SHADER,
		TessControl    = GL_TESS_CONTROL_SHADER,
		TessEvaluation = GL_TESS_EVALUATION_SHADER,
		Geometry       = GL_GEOMETRY_SHADER,
		Fragment       = GL_FRAGMENT_SHADER
	};

	/// @brief Enum of all possible buffer targets.
	/// Values align with GL enums of same names.
	enum class BufferTarget : GLenum
	{
		Array             = GL_ARRAY_BUFFER,
		AtomicCounter     = GL_ATOMIC_COUNTER_BUFFER,
		CopyRead          = GL_COPY_READ_BUFFER,
		CopyWrite         = GL_COPY_WRITE_BUFFER,
		DispatchIndirect  = GL_DISPATCH_INDIRECT_BUFFER,
		DrawIndirect      = GL_DRAW_INDIRECT_BUFFER,
		ElementArray      = GL_ELEMENT_ARRAY_BUFFER,
		PixelPack         = GL_PIXEL_PACK_BUFFER,
		PixelUnpack       = GL_PIXEL_UNPACK_BUFFER,
		Query             = GL_QUERY_BUFFER,
		ShaderStorage     = GL_SHADER_STORAGE_BUFFER,
		Texture           = GL_TEXTURE_BUFFER,
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
		Uniform           = GL_UNIFORM_BUFFER
	};

	/// @brief Enum of all possible buffer usages.
	/// Values align with GL enums of same names.
	enum class BufferUsage : GLenum
	{
		StaticDraw  = GL_STATIC_DRAW,
		StaticRead  = GL_STATIC_READ,
		StaticCopy  = GL_STATIC_COPY,

		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY,

		StreamDraw  = GL_STREAM_DRAW,
		StreamRead  = GL_STREAM_READ,
		StreamCopy  = GL_STREAM_COPY
	};
}

#endif //GAL_ENUMS_HPP

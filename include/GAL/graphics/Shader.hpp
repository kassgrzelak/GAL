//
// Created by kassie on 26/01/2026.
//

#ifndef GAL_SHADER_HPP
#define GAL_SHADER_HPP
#include <fstream>

namespace gal
{
	namespace detail
	{
		inline void shaderDeleter(const ShaderID id) noexcept
		{
			glDeleteShader(id);
		}

		using UniqueShader = UniqueHandle<ShaderID, 0, shaderDeleter>;
	}

	/// @brief Wrapper around an OpenGL shader.
	class Shader : detail::UniqueShader
	{
	public:
		/// @brief Create a shader of the given type.
		/// @param type The type of shader to create.
		/// @throws ErrCode::CreateShaderFailed If shader creation fails for any reason.
		explicit Shader(const ShaderType type)
		{
			detail::logInfo("Creating shader...");
			detail::logIncreaseIndent();

			const ShaderID id = glCreateShader(static_cast<GLenum>(type));
			if (!id)
				detail::throwErr(ErrCode::CreateShaderFailed, "Failed to create shader.");
			detail::logInfoStart() << "Successfully created shader ID " << id << "." << detail::logInfoEnd;

			setHandle(id);
			detail::logInfo("Successfully created shader.");
			detail::logDecreaseIndent();
		}

		/// @brief Get the ID of the shader.
		[[nodiscard]] ShaderID getID() const noexcept { return getHandle(); }

		/// @brief Set the shader's source from a string.
		/// @param source String containing the shader's source code.
		[[maybe_unused]] const Shader& sourceString(const std::string& source) const noexcept // NOLINT(*-use-nodiscard)
		{
			const char* sourceChars = source.c_str();
			glShaderSource(getHandle(), 1, &sourceChars, nullptr);
			return *this;
		}

		/// @brief Set the shader's source from a file.
		/// @param path Filepath to the file containing the shader's source code.
		/// @throws ErrCode::ShaderFileReadFailed If reading the file at the path provided fails for any reason.
		[[maybe_unused]] const Shader& sourceFile(const std::string& path) const // NOLINT(*-use-nodiscard)
		{
			std::ifstream file{path};
			if (!file.is_open())
				detail::throwErr(ErrCode::ShaderFileReadFailed, "Failed to read shader source file.");

			std::stringstream buffer;
			buffer << file.rdbuf();

			return sourceString(buffer.str());
		}

		/// @brief Compile the shader with the source code provided with an earlier call to sourceString() or
		/// sourceFile().
		/// @throws ErrCode::ShaderCompilationFailed If shader compilation fails for any reason.
		void compile() const
		{
			glCompileShader(getHandle());

			GLint success;
			glGetShaderiv(getHandle(), GL_COMPILE_STATUS, &success);
			if (!success)
			{
#ifdef GAL_ERROR_LOGGING
				GLint logLength;
				glGetShaderiv(getHandle(), GL_INFO_LOG_LENGTH, &logLength);

				std::vector<GLchar> errorLog(logLength);
				glGetShaderInfoLog(getHandle(), logLength, &logLength, errorLog.data());

				detail::logErr("Failed to compile shader. Error log from OpenGL to follow.");
				detail::throwErr(ErrCode::ShaderCompilationFailed, errorLog.data());
#else
				detail::throwErr(ErrCode::ShaderCompilationFailed, "Failed to compile shader.");
#endif
			}
		}

		/// @brief Delete the shader.
		///
		/// This just calls the destructor, which would delete the shader anyway when it goes out of scope, but this
		/// is here as a more explicit option (that's also less ugly than calling the destructor directly).
		void destroy() const noexcept { this->~Shader(); }
	};
}

#endif //GAL_SHADER_HPP
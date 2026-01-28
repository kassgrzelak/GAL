//
// Created by kassie on 26/01/2026.
//

#ifndef GAL_PROGRAM_HPP
#define GAL_PROGRAM_HPP

#include <unordered_map>

#include "Shader.hpp"

namespace gal
{
	namespace detail
	{
		inline void programDeleter(const ProgramID id) noexcept
		{
			glDeleteProgram(id);
		}

		using UniqueProgram = UniqueHandle<ProgramID, 0, programDeleter>;
	}

	/// @brief Wrapper around an OpenGL shader program with uniform location caching.
	class Program : detail::UniqueProgram
	{
	public:
		/// @brief Create an empty program.
		/// @throws ErrCode::CreateProgramFailed If program creation fails for any reason.
		Program()
		{
			detail::logInfo("Creating program...");
			detail::logIncreaseIndent();

			const ProgramID id = glCreateProgram();
			if (!id)
				detail::throwErr(ErrCode::CreateProgramFailed, "Failed to create program.");
			detail::logInfoStart() << "Successfully created program ID " << id << "." << detail::logInfoEnd;

			setHandle(id);
			detail::logInfo("Successfully created program.");
			detail::logDecreaseIndent();
		}

		/// @brief Get the ID of the program.
		[[nodiscard]] ProgramID getID() const noexcept { return getHandle(); }

		/// @brief Make OpenGL use the program.
		void use() const noexcept { glUseProgram(getHandle()); }

		/// @brief Attach a shader to the program.
		/// @param shader The shader to attach.
		void attachShader(const Shader& shader) const noexcept { attachShader(shader.getID()); }
		/// @brief Attach a shader to the program.
		/// @param shaderID The ID of the shader to attach.
		void attachShader(const ShaderID shaderID) const noexcept { glAttachShader(getHandle(), shaderID); }
		/// @brief Detach a shader to the program.
		/// @param shader The shader to detach.
		void detachShader(const Shader& shader) const noexcept { detachShader(shader.getID()); }
		/// @brief Detach a shader to the program.
		/// @param shaderID The ID of the shader to detach.
		void detachShader(const ShaderID shaderID) const noexcept { glDetachShader(getHandle(), shaderID); }

		/// @brief Link the program and automatically detach all attached shaders.
		/// @throws ErrCode::ProgramLinkFailed If program linking fails for any reason.
		void link() const
		{
			detail::logInfoStart() << "Linking program ID " << getHandle() << "..." << detail::logInfoEnd;
			detail::logIncreaseIndent();

			glLinkProgram(getHandle());

			GLint success;
			glGetProgramiv(getHandle(), GL_LINK_STATUS, &success);
			if (!success)
			{
#ifdef GAL_ERROR_LOGGING
				GLint logLength;
				glGetProgramiv(getHandle(), GL_INFO_LOG_LENGTH, &logLength);

				std::vector<GLchar> errorLog(logLength);
				glGetProgramInfoLog(getHandle(), logLength, &logLength, errorLog.data());

				detail::logErr("Failed to link program. Error log from OpenGL to follow.");
				detail::throwErr(ErrCode::ProgramLinkFailed, errorLog.data());
#else
				detail::throwErr(ErrCode::ProgramLinkFailed, "Failed to link program.");
#endif
			}

			detail::logInfo("Successfully linked program.");
			detail::logInfo("Detaching shaders...");
			detail::logIncreaseIndent();

			GLint attachedShaderCount;
			glGetProgramiv(getHandle(), GL_ATTACHED_SHADERS, &attachedShaderCount);

			std::vector<ShaderID> attachedShaders(attachedShaderCount);
			glGetAttachedShaders(getHandle(), attachedShaderCount, nullptr, attachedShaders.data());

			for (const auto& id : attachedShaders)
			{
				detachShader(id);
				detail::logInfoStart() << "Detached shader ID " << id << "." << detail::logInfoEnd;
			}

			detail::logDecreaseIndent(2);
		}
		
		// ========== float uniform setters ==========

		/// @brief Set a float uniform.
		/// @param name Name of the uniform to set.
		/// @param val Value to assign to the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const float val) const
		{
			glProgramUniform1f(getHandle(), getUniformLocation(name), val);
			return *this;
		}

		/// @brief Set a float uniform.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 1-component vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::vec1& vec) const
		{
			glProgramUniform1fv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		/// @brief Set a float vector uniform with two components.
		/// @param name Name of the uniform to set.
		/// @param val1 First component of the uniform.
		/// @param val2 Second component of the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const float val1, const float val2) const
		{
			glProgramUniform2f(getHandle(), getUniformLocation(name), val1, val2);
			return *this;
		}

		/// @brief Set a float vector uniform with two components.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 2-component vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::vec2& vec) const
		{
			glProgramUniform2fv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		/// @brief Set a float vector uniform with three components.
		/// @param name Name of the uniform to set.
		/// @param val1 First component of the uniform.
		/// @param val2 Second component of the uniform.
		/// @param val3 Third component of the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const float val1, const float val2, const float val3) const
		{
			glProgramUniform3f(getHandle(), getUniformLocation(name), val1, val2, val3);
			return *this;
		}

		/// @brief Set a float vector uniform with three components.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 3-component vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::vec3& vec) const
		{
			glProgramUniform3fv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		/// @brief Set a float vector uniform with four components.
		/// @param name Name of the uniform to set.
		/// @param val1 First component of the uniform.
		/// @param val2 Second component of the uniform.
		/// @param val3 Third component of the uniform.
		/// @param val4 Fourth component of the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const float val1, const float val2, const float val3, const float val4) const
		{
			glProgramUniform4f(getHandle(), getUniformLocation(name), val1, val2, val3, val4);
			return *this;
		}

		/// @brief Set a float vector uniform with four components.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 4-component vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::vec4& vec) const
		{
			glProgramUniform4fv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		// ========== int uniform setters ==========

		/// @brief Set a boolean uniform.
		/// @param name Name of the uniform to set.
		/// @param val Boolean value to assign to the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const bool val) const
		{
			glProgramUniform1i(getHandle(), getUniformLocation(name), static_cast<int>(val));
			return *this;
		}

		/// @brief Set an integer uniform.
		/// @param name Name of the uniform to set.
		/// @param val Integer value to assign to the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const int val) const
		{
			glProgramUniform1i(getHandle(), getUniformLocation(name), val);
			return *this;
		}

		/// @brief Set an integer uniform.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 1-component integer vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::ivec1& vec) const
		{
			glProgramUniform1iv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		/// @brief Set an integer vector uniform with two components.
		/// @param name Name of the uniform to set.
		/// @param val1 First component of the uniform.
		/// @param val2 Second component of the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const int val1, const int val2) const
		{
			glProgramUniform2i(getHandle(), getUniformLocation(name), val1, val2);
			return *this;
		}

		/// @brief Set an integer vector uniform with two components.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 2-component integer vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::ivec2& vec) const
		{
			glProgramUniform2iv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		/// @brief Set an integer vector uniform with three components.
		/// @param name Name of the uniform to set.
		/// @param val1 First component of the uniform.
		/// @param val2 Second component of the uniform.
		/// @param val3 Third component of the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const int val1, const int val2, const int val3) const
		{
			glProgramUniform3i(getHandle(), getUniformLocation(name), val1, val2, val3);
			return *this;
		}

		/// @brief Set an integer vector uniform with three components.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 3-component integer vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::ivec3& vec) const
		{
			glProgramUniform3iv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		/// @brief Set an integer vector uniform with four components.
		/// @param name Name of the uniform to set.
		/// @param val1 First component of the uniform.
		/// @param val2 Second component of the uniform.
		/// @param val3 Third component of the uniform.
		/// @param val4 Fourth component of the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const int val1, const int val2, const int val3, const int val4) const
		{
			glProgramUniform4i(getHandle(), getUniformLocation(name), val1, val2, val3, val4);
			return *this;
		}

		/// @brief Set an integer vector uniform with four components.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 4-component integer vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::ivec4& vec) const
		{
			glProgramUniform4iv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		// ========== uint uniform setters ==========

		/// @brief Set an unsigned integer uniform.
		/// @param name Name of the uniform to set.
		/// @param val Unsigned integer value to assign to the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const unsigned int val) const
		{
			glProgramUniform1ui(getHandle(), getUniformLocation(name), val);
			return *this;
		}

		/// @brief Set an unsigned integer uniform.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 1-component unsigned integer vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::uvec1& vec) const
		{
			glProgramUniform1uiv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		/// @brief Set an unsigned integer vector uniform with two components.
		/// @param name Name of the uniform to set.
		/// @param val1 First component of the uniform.
		/// @param val2 Second component of the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const unsigned int val1, const unsigned int val2) const
		{
			glProgramUniform2ui(getHandle(), getUniformLocation(name), val1, val2);
			return *this;
		}

		/// @brief Set an unsigned integer vector uniform with two components.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 2-component unsigned integer vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::uvec2& vec) const
		{
			glProgramUniform2uiv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		/// @brief Set an unsigned integer vector uniform with three components.
		/// @param name Name of the uniform to set.
		/// @param val1 First component of the uniform.
		/// @param val2 Second component of the uniform.
		/// @param val3 Third component of the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const unsigned int val1, const unsigned int val2, const unsigned int val3) const
		{
			glProgramUniform3ui(getHandle(), getUniformLocation(name), val1, val2, val3);
			return *this;
		}

		/// @brief Set an unsigned integer vector uniform with three components.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 3-component unsigned integer vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::uvec3& vec) const
		{
			glProgramUniform3uiv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}

		/// @brief Set an unsigned integer vector uniform with four components.
		/// @param name Name of the uniform to set.
		/// @param val1 First component of the uniform.
		/// @param val2 Second component of the uniform.
		/// @param val3 Third component of the uniform.
		/// @param val4 Fourth component of the uniform.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const unsigned int val1, const unsigned int val2, const unsigned int val3, const unsigned int val4) const
		{
			glProgramUniform4ui(getHandle(), getUniformLocation(name), val1, val2, val3, val4);
			return *this;
		}

		/// @brief Set an unsigned integer vector uniform with four components.
		/// @param name Name of the uniform to set.
		/// @param vec Value to assign to the uniform as a 4-component unsigned integer vector.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::uvec4& vec) const
		{
			glProgramUniform4uiv(getHandle(), getUniformLocation(name), 1, glm::value_ptr(vec));
			return *this;
		}


		// ========== matrix uniform setters ==========

		/// @brief Set a 2x2 matrix uniform.
		/// @param name Name of the uniform to set.
		/// @param mat Matrix value to assign to the uniform.
		/// @param transpose Whether to transpose the matrix when uploading.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::mat2& mat, const bool transpose = false) const
		{
			glProgramUniformMatrix2fv(getHandle(), getUniformLocation(name), 1, transpose, glm::value_ptr(mat));
			return *this;
		}

		/// @brief Set a 3x3 matrix uniform.
		/// @param name Name of the uniform to set.
		/// @param mat Matrix value to assign to the uniform.
		/// @param transpose Whether to transpose the matrix when uploading.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::mat3& mat, const bool transpose = false) const
		{
			glProgramUniformMatrix3fv(getHandle(), getUniformLocation(name), 1, transpose, glm::value_ptr(mat));
			return *this;
		}

		/// @brief Set a 4x4 matrix uniform.
		/// @param name Name of the uniform to set.
		/// @param mat Matrix value to assign to the uniform.
		/// @param transpose Whether to transpose the matrix when uploading.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::mat4& mat, const bool transpose = false) const
		{
			glProgramUniformMatrix4fv(getHandle(), getUniformLocation(name), 1, transpose, glm::value_ptr(mat));
			return *this;
		}

		/// @brief Set a 2x3 matrix uniform.
		/// @param name Name of the uniform to set.
		/// @param mat Matrix value to assign to the uniform.
		/// @param transpose Whether to transpose the matrix when uploading.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::mat2x3& mat, const bool transpose = false) const
		{
			glProgramUniformMatrix2x3fv(getHandle(), getUniformLocation(name), 1, transpose, glm::value_ptr(mat));
			return *this;
		}

		/// @brief Set a 3x2 matrix uniform.
		/// @param name Name of the uniform to set.
		/// @param mat Matrix value to assign to the uniform.
		/// @param transpose Whether to transpose the matrix when uploading.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::mat3x2& mat, const bool transpose = false) const
		{
			glProgramUniformMatrix3x2fv(getHandle(), getUniformLocation(name), 1, transpose, glm::value_ptr(mat));
			return *this;
		}

		/// @brief Set a 2x4 matrix uniform.
		/// @param name Name of the uniform to set.
		/// @param mat Matrix value to assign to the uniform.
		/// @param transpose Whether to transpose the matrix when uploading.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::mat2x4& mat, const bool transpose = false) const
		{
			glProgramUniformMatrix2x4fv(getHandle(), getUniformLocation(name), 1, transpose, glm::value_ptr(mat));
			return *this;
		}

		/// @brief Set a 4x2 matrix uniform.
		/// @param name Name of the uniform to set.
		/// @param mat Matrix value to assign to the uniform.
		/// @param transpose Whether to transpose the matrix when uploading.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::mat4x2& mat, const bool transpose = false) const
		{
			glProgramUniformMatrix4x2fv(getHandle(), getUniformLocation(name), 1, transpose, glm::value_ptr(mat));
			return *this;
		}

		/// @brief Set a 3x4 matrix uniform.
		/// @param name Name of the uniform to set.
		/// @param mat Matrix value to assign to the uniform.
		/// @param transpose Whether to transpose the matrix when uploading.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::mat3x4& mat, const bool transpose = false) const
		{
			glProgramUniformMatrix3x4fv(getHandle(), getUniformLocation(name), 1, transpose, glm::value_ptr(mat));
			return *this;
		}

		/// @brief Set a 4x3 matrix uniform.
		/// @param name Name of the uniform to set.
		/// @param mat Matrix value to assign to the uniform.
		/// @param transpose Whether to transpose the matrix when uploading.
		/// @throws ErrCode::NonExistentShaderUniform If the given uniform does not exist.
		[[maybe_unused]] const Program& setUniform(const std::string& name, const glm::mat4x3& mat, const bool transpose = false) const
		{
			glProgramUniformMatrix4x3fv(getHandle(), getUniformLocation(name), 1, transpose, glm::value_ptr(mat));
			return *this;
		}

	private:
		std::vector<ShaderID> m_attachedShaders;
		mutable std::unordered_map<std::string, GLint> m_uniformLocations;

		GLint getUniformLocation(const std::string& name) const
		{
			if (const auto it = m_uniformLocations.find(name); it != m_uniformLocations.end())
				return it->second;

			const GLint loc = glGetUniformLocation(getHandle(), name.c_str());
			if (loc == -1)
				detail::throwErr(ErrCode::NonExistentShaderUniform, "Attempted to set non-existent shader uniform.");

			m_uniformLocations[name] = loc;
			return loc;
		}
	};
}

#endif //GAL_PROGRAM_HPP
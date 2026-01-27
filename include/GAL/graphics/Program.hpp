//
// Created by kassie on 26/01/2026.
//

#ifndef GAL_PROGRAM_HPP
#define GAL_PROGRAM_HPP

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

	/// @brief Wrapper around an OpenGL shader program.
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

	private:
		std::vector<ShaderID> m_attachedShaders;
	};
}

#endif //GAL_PROGRAM_HPP
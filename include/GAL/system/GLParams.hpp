//
// Created by kassie on 29/01/2026.
//

#ifndef GAL_GL_PARAMS_HPP
#define GAL_GL_PARAMS_HPP

namespace gal
{
	/// @brief Get the value of a boolean OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	inline GLboolean getGLParamBool(const GLenum name)
	{
		GLboolean param;
		glGetBooleanv(name, &param);
		return param;
	}

	/// @brief Get the value of a double OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	inline GLdouble getGLParamDouble(const GLenum name)
	{
		GLdouble param;
		glGetDoublev(name, &param);
		return param;
	}

	/// @brief Get the value of a float OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	inline GLfloat getGLParamFloat(const GLenum name)
	{
		GLfloat param;
		glGetFloatv(name, &param);
		return param;
	}

	/// @brief Get the value of an int OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	inline GLint getGLParamInt(const GLenum name)
	{
		GLint param;
		glGetIntegerv(name, &param);
		return param;
	}

	/// @brief Get the value of an int64 OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	inline GLint64 getGLParamInt64(const GLenum name)
	{
		GLint64 param;
		glGetInteger64v(name, &param);
		return param;
	}

	/// @brief Get the value of an indexed boolean OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	/// @param index Index of the particular element to get.
	inline GLboolean getGLIndexedParamBool(const GLenum name, const GLuint index)
	{
		GLboolean param;
		glGetBooleani_v(name, index, &param);
		return param;
	}

	/// @brief Get the value of an indexed double OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	/// @param index Index of the particular element to get.
	inline GLdouble getGLIndexedParamDouble(const GLenum name, const GLuint index)
	{
		GLdouble param;
		glGetDoublei_v(name, index, &param);
		return param;
	}

	/// @brief Get the value of an indexed float OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	/// @param index Index of the particular element to get.
	inline GLfloat getGLIndexedParamFloat(const GLenum name, const GLuint index)
	{
		GLfloat param;
		glGetFloati_v(name, index, &param);
		return param;
	}

	/// @brief Get the value of an indexed int OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	/// @param index Index of the particular element to get.
	inline GLint getGLIndexedParamInt(const GLenum name, const GLuint index)
	{
		GLint param;
		glGetIntegeri_v(name, index, &param);
		return param;
	}

	/// @brief Get the value of an indexed int64 OpenGL parameter.
	/// @param name GLenum name of the parameter to get.
	/// @param index Index of the particular element to get.
	inline GLint64 getGLIndexedParamInt64(const GLenum name, const GLuint index)
	{
		GLint64 param;
		glGetInteger64i_v(name, index, &param);
		return param;
	}
}

#endif //GAL_GL_PARAMS_HPP
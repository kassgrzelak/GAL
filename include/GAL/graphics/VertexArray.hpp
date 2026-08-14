//
// Created by kassie on 29/01/2026.
//

#ifndef GAL_VERTEX_ARRAY_HPP
#define GAL_VERTEX_ARRAY_HPP

namespace gal
{
	namespace detail
	{
		inline void vertexArrayDeleter(const VertexArrayID id) noexcept
		{
			glDeleteVertexArrays(1, &id);
		}

		using UniqueVertexArray = UniqueHandle<VertexArrayID, 0, &vertexArrayDeleter>;
	}

	class VertexArray : detail::UniqueVertexArray
	{
	public:
		VertexArray()
		{
			detail::logInfo("Creating vertex array...");
			detail::logIncreaseIndent();

			VertexArrayID id;
			glCreateVertexArrays(1, &id);
			if (!id)
				detail::throwErr(ErrCode::CreateVertexArrayFailed, "Failed to create vertex array.");
			detail::logInfoStart() << "Successfully created vertex array ID " << id << "." << detail::logInfoEnd;

			setHandle(id);
			detail::logInfo("Successfully created vertex array.");
			detail::logDecreaseIndent();
		}

		/// @brief Get the ID of the vertex array.
		[[nodiscard]] VertexArrayID getID() const noexcept { return getHandle(); }

		/// @brief Bind the vertex array for use.
		void bind() const noexcept { glBindVertexArray(getHandle()); }

		/// @brief Bind a buffer to be this vertex array's vertex buffer for the given index.
		/// @param bufferID The ID of the buffer to bind.
		/// @param bufferIndex The index to bind the vertex buffer to.
		/// @param offset The byte offset at which the vertex data begins in the vertex buffer.
		/// @param stride The byte offset from one vertex to the next; i.e., the size of each vertex's data.
		void bindVertexBuffer(const BufferID bufferID, const GLuint bufferIndex, const GLintptr offset, const GLsizei stride) const noexcept
		{
			glVertexArrayVertexBuffer(getHandle(), bufferIndex, bufferID, offset, stride);
			detail::logInfoStart() << "Bound buffer ID " << bufferID << " to buffer index " << bufferIndex <<
				" of vertex array ID " << getHandle() << "." << detail::logInfoEnd;
		}

		/// @brief Bind a buffer to be this vertex array's vertex buffer for the given index.
		/// @param buffer The buffer to bind.
		/// @param bufferIndex The index to bind the vertex buffer to.
		/// @param offset The byte offset at which the vertex data begins in the vertex buffer.
		/// @param stride The byte offset from one vertex to the next; i.e., the size of each vertex's data.
		void bindVertexBuffer(const Buffer& buffer, const GLuint bufferIndex, const GLintptr offset, const GLsizei stride) const noexcept
		{
			bindVertexBuffer(buffer.getID(), bufferIndex, offset, stride);
		}

		/// @brief Unbind (bind to 0) the vertex buffer bound to the given buffer index.
		/// @param bufferIndex The index of the buffer to unbind.
		void unbindVertexBuffer(const GLuint bufferIndex) const noexcept
		{
			bindVertexBuffer(0, bufferIndex, 0, 0);
		}

		/// @brief Define and enable a new vertex attribute for the data in the buffer at the given binding index.
		/// @param attributeIndex Index of the new attribute.
		/// @param bufferIndex Index of the buffer whose data to use.
		/// @param components Number of components in the vector this attribute represents.
		/// @param dataType The data type of each component in the vector.
		/// @param normalized Whether to normalize integer values to floats.
		/// @param relativeOffset The offset from the beginning of a vertex's data to the vector this attribute represents.
		/// Think offsetof(VertexType, component).
		void vertexAttributeFormat(const GLuint attributeIndex, const GLuint bufferIndex, const GLint components,
			const GLenum dataType, const GLboolean normalized, const GLuint relativeOffset) const noexcept
		{
			glEnableVertexArrayAttrib(getHandle(), attributeIndex);
			glVertexArrayAttribFormat(getHandle(), attributeIndex, components, dataType, normalized, relativeOffset);
			glVertexArrayAttribBinding(getHandle(), attributeIndex, bufferIndex);
		}

		/// @brief Define and enable a new vertex attribute for the data in the buffer at the given binding index (integer version).
		/// @param attributeIndex Index of the new attribute.
		/// @param bufferIndex Index of the buffer whose data to use.
		/// @param components Number of components in the vector this attribute represents.
		/// @param dataType The data type of each component in the vector.
		/// @param relativeOffset The offset from the beginning of a vertex's data to the vector this attribute represents.
		/// Think offsetof(VertexType, component).
		void vertexAttributeIntFormat(const GLuint attributeIndex, const GLuint bufferIndex, const GLint components,
			const GLenum dataType, const GLuint relativeOffset) const noexcept
		{
			glEnableVertexArrayAttrib(getHandle(), attributeIndex);
			glVertexArrayAttribIFormat(getHandle(), attributeIndex, components, dataType, relativeOffset);
			glVertexArrayAttribBinding(getHandle(), attributeIndex, bufferIndex);
		}

		/// @brief Define and enable a new vertex attribute for the data in the buffer at the given binding index (double version).
		/// @param attributeIndex Index of the new attribute.
		/// @param bufferIndex Index of the buffer whose data to use.
		/// @param components Number of components in the vector this attribute represents.
		/// @param dataType The data type of each component in the vector.
		/// @param relativeOffset The offset from the beginning of a vertex's data to the vector this attribute represents.
		/// Think offsetof(VertexType, component).
		void vertexAttributeDoubleFormat(const GLuint attributeIndex, const GLuint bufferIndex, const GLint components,
			const GLenum dataType, const GLuint relativeOffset) const noexcept
		{
			glEnableVertexArrayAttrib(getHandle(), attributeIndex);
			glVertexArrayAttribLFormat(getHandle(), attributeIndex, components, dataType, relativeOffset);
			glVertexArrayAttribBinding(getHandle(), attributeIndex, bufferIndex);
		}

		/// @brief Bind a buffer to be this vertex array's element buffer.
		/// @param bufferID The ID of the buffer to bind.
		void bindElementBuffer(const BufferID bufferID) const noexcept
		{
			glVertexArrayElementBuffer(getHandle(), bufferID);
			detail::logInfoStart() << "Bound buffer ID " << bufferID << " to be the element buffer of vertex array ID " <<
				getHandle() << "." << detail::logInfoEnd;
		}

		/// @brief Bind a buffer to be this vertex array's element buffer.
		/// @param buffer The buffer to bind.
		void bindElementBuffer(const Buffer& buffer) const noexcept
		{
			bindElementBuffer(buffer.getID());
		}

		/// @brief Unbind (bind to 0) this vertex array's element buffer.
		void unbindElementBuffer() const noexcept
		{
			bindElementBuffer(0);
		}
	};
}

#endif //GAL_VERTEX_ARRAY_HPP
//
// Created by kassie on 28/01/2026.
//

#ifndef GAL_BUFFER_HPP
#define GAL_BUFFER_HPP

namespace gal
{
	namespace detail
	{
		inline void bufferDeleter(const BufferID id) noexcept
		{
			glDeleteBuffers(1, &id);
		}

		using UniqueBuffer = UniqueHandle<BufferID, 0, &bufferDeleter>;
	}

	/// @brief Wrapper around an OpenGL buffer.
	class Buffer : detail::UniqueBuffer
	{
	public:
		/// @brief Create a buffer.
		/// @throws ErrCode::CreateBufferFailed If initial buffer creation fails.
		Buffer()
		{
			detail::logInfo("Creating buffer...");
			detail::logIncreaseIndent();

			BufferID id;
			glCreateBuffers(1, &id);
			if (!id)
				detail::throwErr(ErrCode::CreateBufferFailed, "Failed to create buffer.");
			detail::logInfoStart() << "Successfully created buffer ID " << id << "." << detail::logInfoEnd;

			setHandle(id);
			detail::logInfo("Successfully created buffer.");
			detail::logDecreaseIndent();
		}

		/// @brief Get the ID of the buffer.
		[[nodiscard]] BufferID getID() const noexcept { return getHandle(); }

		/// @brief Bind the buffer to the given target. DSA is encouraged where possible.
		/// @param target Target to bind the buffer to.
		void bind(BufferTarget target) const noexcept { glBindBuffer(static_cast<GLenum>(target), getHandle()); }

		/// @brief Get the access policy set while mapping the buffer. Default value is GL_READ_WRITE.
		[[nodiscard]] GLbitfield getAccessPolicy() const noexcept
		{
			GLint access;
			glGetNamedBufferParameteriv(getHandle(), GL_BUFFER_ACCESS, &access);
			return access;
		}

		/// @brief Get whether the buffer is currently mapped. Default value is false.
		[[nodiscard]] bool getMapped() const noexcept
		{
			GLint mapped;
			glGetNamedBufferParameteriv(getHandle(), GL_BUFFER_MAPPED, &mapped);
			return mapped;
		}

		/// @brief Get the size of the buffer. Default value is 0.
		[[nodiscard]] GLint64 getSize() const noexcept
		{
			GLint64 size;
			glGetNamedBufferParameteri64v(getHandle(), GL_BUFFER_SIZE, &size);
			return size;
		}

		/// @brief Get the usage pattern specified for this buffer. Default value is StaticDraw.
		[[nodiscard]] BufferUsage getUsage() const noexcept
		{
			GLint usage;
			glGetNamedBufferParameteriv(getHandle(), GL_BUFFER_USAGE, &usage);
			return static_cast<BufferUsage>(usage);
		}

		/// @brief Allocate given space in VRAM for this buffer with the given usage but don't fill it, leaving the
		/// contents undefined.
		/// @param size Size to allocate in bytes.
		/// @param usage Buffer usage hint.
		void allocate(const GLsizeiptr size, const BufferUsage usage) const noexcept
		{
			glNamedBufferData(getHandle(), size, nullptr, static_cast<GLenum>(usage));
		}

		/// @brief Allocate given space in VRAM for this buffer with the given usage hint and fill it with the given data.
		/// @param size Size of data to write in bytes.
		/// @param data Pointer to data to write.
		/// @param usage Buffer usage hint.
		void allocateAndWrite(const GLsizeiptr size, const void* data, const BufferUsage usage) const noexcept
		{
			glNamedBufferData(getHandle(), size, data, static_cast<GLenum>(usage));
		}

		/// @brief Allocate enough space in VRAM to hold all the data in the given container and fill the buffer with
		/// that data.
		/// @tparam Container Container type. This can be anything that satisfies the ContinuousContainer requirement.
		/// See https://en.cppreference.com/w/cpp/named_req/ContiguousContainer.html
		/// @param data The container with the data to fill the buffer with.
		/// @param usage Buffer usage hint.
		template<typename Container>
		auto allocateAndWrite(const Container& data, const BufferUsage usage) const noexcept
			-> std::enable_if_t<
				std::is_pointer_v<decltype(data.data())> &&
				std::is_integral_v<decltype(data.size())>
			>
		{
			using T = std::remove_pointer_t<decltype(data.data())>;
			allocateAndWrite(sizeof(T) * data.size(), data.data(), usage);
		}

		/// @brief Update the entire contents of the buffer with the given data.
		/// @param data Pointer to the data to write.
		///
		/// This function assumes the array that data points to is the same size the buffer was allocated to.
		void writeAll(const void* data) const noexcept
		{
			glNamedBufferSubData(getHandle(), 0, getSize(), data);
		}

		/// @brief Update the entire contents of the buffer with the given data.
		/// @tparam Container Container type. This can be anything that satisfies the ContinuousContainer requirement.
		/// See https://en.cppreference.com/w/cpp/named_req/ContiguousContainer.html
		/// @param data The container with the data to fill the buffer with.
		template<typename Container>
		auto writeAll(const Container& data) const noexcept
			-> std::enable_if_t<
				std::is_pointer_v<decltype(data.data())> &&
				std::is_integral_v<decltype(data.size())>
			>
		{
			writeAll(data.data());
		}
	};
}

#endif //GAL_BUFFER_HPP
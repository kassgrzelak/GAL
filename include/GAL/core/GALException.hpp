//
// Created by kassie on 23/01/2026.
//

#ifndef GAL_GAL_EXCEPTION_HPP
#define GAL_GAL_EXCEPTION_HPP

#include <exception>

#include "GAL/detail/logging.hpp"

namespace gal
{
	/// @brief Class for exceptions in GAL. This is thrown when an expected error occurs inside GAL. Also
	/// contains a GAL ErrCode.
	class GALException : public std::exception
	{
	public:
		const ErrCode errCode;

		explicit GALException(const ErrCode errCode, const char* msg)
			: errCode(errCode), msg(msg) {}

		[[nodiscard]] const char* what() const noexcept override { return msg; }

	private:
		const char* msg;
	};

	namespace detail
	{
		/// @brief Log an error and immediately throw it.
		inline void throwErr(const ErrCode errCode, const char* msg)
		{
			logErr(msg);
			throw GALException(errCode, msg);
		}
	}
}

#endif //GAL_GAL_EXCEPTION_HPP
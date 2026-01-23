//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_LOGGING_HPP
#define GAL_LOGGING_HPP

#include <iostream>

namespace gal::detail
{
	/// @brief Blank ostream struct so the compiler can optimize out log function calls when those macros aren't defined.
	struct NullStream : std::ostream
	{
		struct NullBuf : std::streambuf
		{
			int overflow(const int c) override { return c; }
		};

		NullBuf buf;
		NullStream() : std::ostream(&buf) { }
	};

	inline NullStream nullStream;

#ifdef GAL_ERROR_LOGGING
	inline void logErr(const char* msg)
	{
		std::cerr << "\u001b[31mGAL_ERR: " << msg << "\u001b[0m\n";
	}

	inline std::ostream& logErrStart()
	{
		return std::cerr << "\u001b[31mGAL_ERR: ";
	}

	inline std::ostream& logErrEnd(std::ostream& os)
	{
		return os << "\u001b[0m\n";
	}
#else
	inline void logErr(const char* msg) { }
	inline std::ostream& logErrStart() { return nullStream; }
	inline std::ostream& logErrEnd(std::ostream& os) { return os; }
#endif // GAL_ERROR_LOGGING

#ifdef GAL_WARNING_LOGGING
	inline void logWarn(const char* msg)
	{
		std::cerr << "\u001b[33mGAL_WARN: " << msg << "\u001b[0m\n";
	}

	inline std::ostream& logWarnStart()
	{
		return std::cerr << "\u001b[33mGAL_WARN: ";
	}

	inline std::ostream& logWarnEnd(std::ostream& os)
	{
		return os << "\u001b[0m\n";
	}
#else
	inline void logWarn(const char* msg) { }
	inline std::ostream& logWarnStart() { return nullStream; }
	inline std::ostream& logWarnEnd(std::ostream& os) { return os; }
#endif // GAL_WARNING_LOGGING

#ifdef GAL_INFO_LOGGING
	inline void logInfo(const char* msg)
	{
		std::cout << "GAL_INFO: " << msg << "\n";
	}

	inline std::ostream& logInfoStart()
	{
		return std::cout << "GAL_INFO: ";
	}

	inline std::ostream& logInfoEnd(std::ostream& os)
	{
		return os << "\n";
	}
#else
	inline void logInfo(const char* msg) { }
	inline std::ostream& logInfoStart() { return nullStream; }
	inline std::ostream& logInfoEnd(std::ostream& os) { return os; }
#endif // GAL_INFO_LOGGING
}


#endif //GAL_LOGGING_HPP

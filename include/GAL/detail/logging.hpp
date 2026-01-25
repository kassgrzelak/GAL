//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_LOGGING_HPP
#define GAL_LOGGING_HPP

#include <iostream>

namespace gal::detail
{
	/// @brief Blank ostream struct so the compiler can optimize out log function calls when the logging macros aren't
	/// defined.
	struct NullStream : std::ostream
	{
		struct NullBuf : std::streambuf
		{
			int overflow(const int c) override { return c; }
		};

		NullBuf buf;
		NullStream() : std::ostream(&buf) { }
	};

	inline NullStream g_nullStream;
	inline int g_logIndent = 0;

	inline void logIncreaseIndent(const int delta = 1)
	{
#if defined(GAL_ERROR_LOGGING) || defined(GAL_WARNING_LOGGING) || defined(GAL_INFO_LOGGING)
		g_logIndent += delta;
#endif
	}

	inline void logDecreaseIndent(const int delta = 1)
	{
#if defined(GAL_ERROR_LOGGING) || defined(GAL_WARNING_LOGGING) || defined(GAL_INFO_LOGGING)
		g_logIndent -= delta;
#endif
	}

#ifdef GAL_ERROR_LOGGING
	inline std::ostream& logErrEnd(std::ostream& os)
	{
		return os << "\u001b[0m" << std::endl;
	}

	inline std::ostream& logErrStart()
	{
		if (g_logIndent == 0)
			return std::cerr << "\u001b[31mGAL_ERR: ";

		for (int i = 0; i < g_logIndent; ++i)
			std::cerr << "\t";

		return std::cerr << "\u001b[31m- ";
	}

	inline void logErr(const char* msg)
	{
		if (g_logIndent == 0)
			logErrStart() << msg << logErrEnd;
		else
		{
			for (int i = 0; i < g_logIndent; ++i)
				std::cerr << "\t";

			std::cerr << "\u001b[31m- " << msg << logErrEnd;
		}
	}
#else
	inline std::ostream& logErrEnd(std::ostream& os) { return os; }
	inline std::ostream& logErrStart() { return g_nullStream; }
	inline void logErr(const char* msg) { }
#endif // GAL_ERROR_LOGGING

#ifdef GAL_WARNING_LOGGING
	inline std::ostream& logWarnEnd(std::ostream& os)
	{
		return os << "\u001b[0m" << std::endl;
	}

	inline std::ostream& logWarnStart()
	{
		if (g_logIndent == 0)
			return std::cerr << "\u001b[33mGAL_WARN: ";

		for (int i = 0; i < g_logIndent; ++i)
			std::cerr << "\t";

		return std::cerr << "\u001b[33m- ";
	}

	inline void logWarn(const char* msg)
	{
		if (g_logIndent == 0)
			logWarnStart() << msg << logWarnEnd;
		else
		{
			for (int i = 0; i < g_logIndent; ++i)
				std::cerr << "\t";

			std::cerr << "\u001b[33m- " << msg << logWarnEnd;
		}
	}
#else
	inline std::ostream& logWarnEnd(std::ostream& os) { return os; }
	inline std::ostream& logWarnStart() { return g_nullStream; }
	inline void logWarn(const char* msg) { }
#endif // GAL_WARNING_LOGGING

#ifdef GAL_INFO_LOGGING
	inline std::ostream& logInfoEnd(std::ostream& os)
	{
		return os << std::endl;
	}

	inline std::ostream& logInfoStart()
	{
		if (g_logIndent == 0)
			return std::cout << "GAL_INFO: ";

		for (int i = 0; i < g_logIndent; ++i)
			std::cout << "\t";

		return std::cout << "- ";
	}

	inline void logInfo(const char* msg)
	{
		if (g_logIndent == 0)
			logInfoStart() << msg << logInfoEnd;
		else
		{
			for (int i = 0; i < g_logIndent; ++i)
				std::cout << "\t";

			std::cout << "- " << msg << logInfoEnd;
		}
	}
#else
	inline std::ostream& logInfoEnd(std::ostream& os) { return os; }
	inline std::ostream& logInfoStart() { return g_nullStream; }
	inline void logInfo(const char* msg) { }
#endif // GAL_INFO_LOGGING
}


#endif //GAL_LOGGING_HPP

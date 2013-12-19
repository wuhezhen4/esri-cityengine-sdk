/*
  COPYRIGHT (c) 2013 ESRI
  TRADE SECRETS: ESRI PROPRIETARY AND CONFIDENTIAL
  Unpublished material - all rights reserved under the
  Copyright Laws of the United States and applicable international
  laws, treaties, and conventions.

  For additional information, contact:
  Environmental Systems Research Institute, Inc.
  Attn: Contracts and Legal Services Department
  380 New York Street
  Redlands, California, 92373
  USA

  email: contracts@esri.com
*/

#ifndef PRTX_LOG_H_
#define PRTX_LOG_H_

#include <string>
#include <ostream>
#include <exception>

#include "prt/LogLevel.h"
#include "prt/LogHandler.h"
#include "prt/Status.h"

#include "prtx/prtx.h"
#include "prtx/Types.h"
#include "prtx/URI.h"


#ifndef PRTX_LOG_ENABLED
#	define PRTX_LOG_ENABLED 1						// enable prtx logger by default
#endif

#ifndef PRTX_LOG_ENFORCE_TRACING
#	define PRTX_LOG_ENFORCE_TRACING 0				// set to 1 if you want tracing even in PRT_CC_OPT or PRT_CC_OPT_SYM
#endif

#ifndef PRTX_LOG_PREPEND_PRETTY_FUNCTION_NAME
#	define PRTX_LOG_PREPEND_PRETTY_FUNCTION_NAME 0	// set to 1 if you want to the fully qualified function name prepended
#endif

#if (PRTX_LOG_ENFORCE_TRACING == 1) && defined(PRT_BC_REL)
#	error "enforcing tracing in release mode is not allowed"
#endif

#if (PRTX_LOG_ENABLED == 0)
#	define log_wfatal(...)		if(0) prtx::LogFormatterW(prt::LOG_FATAL, __VA_ARGS__)
#	define log_werror(...)		if(0) prtx::LogFormatterW(prt::LOG_ERROR, __VA_ARGS__)
#	define log_wwarn(...)		if(0) prtx::LogFormatterW(prt::LOG_WARNING, __VA_ARGS__)
#	define log_winfo(...)		if(0) prtx::LogFormatterW(prt::LOG_INFO, __VA_ARGS__)
#	define log_wdebug(...)		if(0) prtx::LogFormatterW(prt::LOG_DEBUG, __VA_ARGS__)
#	define log_wtrace(...)		if(0) prtx::LogFormatterW(prt::LOG_TRACE, __VA_ARGS__)
#	define log_fatal(...)		if(0) prtx::LogFormatter(prt::LOG_FATAL, __VA_ARGS__)
#	define log_error(...)		if(0) prtx::LogFormatter(prt::LOG_ERROR, __VA_ARGS__)
#	define log_warn(...)		if(0) prtx::LogFormatter(prt::LOG_WARNING, __VA_ARGS__)
#	define log_info(...)		if(0) prtx::LogFormatter(prt::LOG_INFO, __VA_ARGS__)
#	define log_debug(...)		if(0) prtx::LogFormatter(prt::LOG_DEBUG, __VA_ARGS__)
#	define log_trace(...)		if(0) prtx::LogFormatter(prt::LOG_TRACE, __VA_ARGS__)
#else
#	define log_wfatal(...)		prtx::LogFormatterW(prt::LOG_FATAL, __VA_ARGS__)
#	define log_werror(...)		prtx::LogFormatterW(prt::LOG_ERROR, __VA_ARGS__)
#	define log_wwarn(...)		prtx::LogFormatterW(prt::LOG_WARNING, __VA_ARGS__)
#	define log_winfo(...)		prtx::LogFormatterW(prt::LOG_INFO, __VA_ARGS__)
#	define log_wdebug(...)		prtx::LogFormatterW(prt::LOG_DEBUG, __VA_ARGS__)
#	if defined(PRT_CC_DBG) || (PRTX_LOG_ENFORCE_TRACING == 1)
#		if (PRTX_LOG_PREPEND_PRETTY_FUNCTION_NAME == 1)
#			define log_wtrace(...)	prtx::LogFormatterW(prt::LOG_TRACE, __VA_ARGS__, __PRETTY_FUNCTION__)
#		else
#			define log_wtrace(...)	prtx::LogFormatterW(prt::LOG_TRACE, __VA_ARGS__)
#		endif
#	else
#		define log_wtrace(...)	if(0) prtx::LogFormatterW(prt::LOG_TRACE, __VA_ARGS__)
#	endif
#	define log_fatal(...)		prtx::LogFormatter(prt::LOG_FATAL, __VA_ARGS__)
#	define log_error(...)		prtx::LogFormatter(prt::LOG_ERROR, __VA_ARGS__)
#	define log_warn(...)		prtx::LogFormatter(prt::LOG_WARNING, __VA_ARGS__)
#	define log_info(...)		prtx::LogFormatter(prt::LOG_INFO, __VA_ARGS__)
#	define log_debug(...)		prtx::LogFormatter(prt::LOG_DEBUG, __VA_ARGS__)
#	if defined(PRT_CC_DBG) || (PRTX_LOG_ENFORCE_TRACING == 1)
#		if (PRTX_LOG_PREPEND_PRETTY_FUNCTION_NAME == 1)
#			define log_trace(...)	prtx::LogFormatter(prt::LOG_TRACE, __VA_ARGS__, __PRETTY_FUNCTION__)
#		else
#			define log_trace(...)	prtx::LogFormatter(prt::LOG_TRACE, __VA_ARGS__)
#		endif
#	else
#		define log_trace(...)	if(0) prtx::LogFormatter(prt::LOG_TRACE, __VA_ARGS__)
#	endif
#endif


class LogFormatterImpl;
class LogFormatterWImpl;


namespace prtx {


class BoundingBox;


/**
 * LogFormatter is a char based log message formatter (see wLogFormatter for a wchar_t version). Uses boost::format syntax to format the log message.
 * See http://www.boost.org/doc/libs/1_55_0/libs/format/doc/format.html#examples for the exact syntax.
 *
 * Each log message has an associated log level. The message will be logged
 * if its level is equal or greater than the globally set log level (see prt::init()).
 *
 * The logging is triggered when the LogFormatter instance is destroyed.
 *
 * It is recommended to use LogFormatter through these convenience macros (char / wchar_t version):
 * - log_fatal / wlog_fatal
 * - log_error / wlog_error
 * - log_warn / wlog_warn
 * - log_info / wlog_info
 * - log_debug / wlog_debug
 *
 *
 * Important: In order to output log messages to the console or into a log file,
 * a log handler must be added with prt::addLogHandler(). There are two default log handlers for your
 * convenience: prt::ConsoleLogHandler and prt::FileLogHandler.
 *
 * A typical use case:
 * \code{.cpp}
 *  // at initialization time
 *  prt::LogHandler* lh = prt::ConsoleLogHandler::create(prt::LogHandler::ALL, 6); // must be destroyed!
 *  prt::addLogHandler(lh);
 *
 *  int myInt = 6;
 *  std::string myString = "hello";
 *  log_info("my log message: %d, %s") % myInt % myString
 *
 *  // above code produces this log line:
 *  // [timestamp] [info] my log message: 6, hello
 * \endcode
 */
class PRTX_EXPORTS_API LogFormatter {
public:
	/**
	 * Generates a log message with the implicit formatting string "%s".
	 * Useful to just log a single string, e.g. \verbatim log_info() % myString \endverbatim
	 */
	LogFormatter(prt::LogLevel l);

	/**
	 * Generates a log message with the formatting string s. This is the most commonly used constructor.
	 */
	LogFormatter(prt::LogLevel l, const std::string& s);

	/**
	 * Generates a log message with the formatting string s and a prefix p.
	 * Useful for marking log messages from a submodule or class.
	 */
	LogFormatter(prt::LogLevel l, const std::string& s, const std::string& p);

	LogFormatter(prt::LogLevel l, const char* s, const char* p = 0);

	/**
	 * Convenience constructor to directly log an exception message.
	 */
	LogFormatter(prt::LogLevel l, const std::exception& e);

	/**
	 * Convenience constructor to log an exception message with a prefix string s.
	 */
	LogFormatter(prt::LogLevel l, const std::string& s, const std::exception& e);

	std::ostream& operator<<(std::ostream& x);

	LogFormatter& operator%(float x);
	LogFormatter& operator%(double x);
#ifndef __linux__
	LogFormatter& operator%(long int x);
#ifndef _MSC_VER
	LogFormatter& operator%(std::size_t x);
#endif
#endif

	LogFormatter& operator%(uint8_t x);
	LogFormatter& operator%(uint16_t x);
	LogFormatter& operator%(uint32_t x);
	LogFormatter& operator%(uint64_t x);

	LogFormatter& operator%(int8_t x);
	LogFormatter& operator%(int16_t x);
	LogFormatter& operator%(int32_t x);
	LogFormatter& operator%(int64_t x);

	LogFormatter& operator%(const char* x);
	LogFormatter& operator%(const std::string& x);
	LogFormatter& operator%(std::ostream& x);

	LogFormatter& operator%(const StringVector& x);

	LogFormatter& operator%(const prt::Status& x);
	LogFormatter& operator%(const prt::LogLevel& x);

	LogFormatter& operator%(const URIPtr& x);
	LogFormatter& operator%(const BoundingBox& x);
	LogFormatter& operator%(const DoubleVector& x);

	LogFormatter& log(uint32_t const* array, uint32_t count);

	virtual ~LogFormatter();
private:
	LogFormatterImpl* mLog;
};


/**
 * wchar_t version of LogFormatter with identical functionality.
 */
class PRTX_EXPORTS_API LogFormatterW {
public:
	LogFormatterW(prt::LogLevel l);
	LogFormatterW(prt::LogLevel l, const std::wstring& s);
	LogFormatterW(prt::LogLevel l, const std::wstring& s, const std::wstring& p);
	LogFormatterW(prt::LogLevel l, const std::wstring& s, const std::string& p);
	LogFormatterW(prt::LogLevel l, const wchar_t* s, const wchar_t* p = 0);

	std::wostream& operator<<(std::wostream& x);

	LogFormatterW& operator%(float x);
	LogFormatterW& operator%(double x);
#ifndef __linux__
	LogFormatterW& operator%(long int x);
#ifndef _MSC_VER
	LogFormatterW& operator%(std::size_t x);
#endif
#endif

	LogFormatterW& operator%(uint8_t x);
	LogFormatterW& operator%(uint16_t x);
	LogFormatterW& operator%(uint32_t x);
	LogFormatterW& operator%(uint64_t x);

	LogFormatterW& operator%(int8_t x);
	LogFormatterW& operator%(int16_t x);
	LogFormatterW& operator%(int32_t x);
	LogFormatterW& operator%(int64_t x);

	LogFormatterW& operator%(const wchar_t* x);
	LogFormatterW& operator%(const std::wstring& x);
	LogFormatterW& operator%(std::wostream& x);

	LogFormatterW& operator%(const WStringVector& x);

	LogFormatterW& operator%(const prt::Status& x);
	LogFormatterW& operator%(const prt::LogLevel& x);

	LogFormatterW& operator%(const URIPtr& x);
	LogFormatterW& operator%(const BoundingBox& x);
	LogFormatterW& operator%(const DoubleVector& x);

	LogFormatterW& log(uint32_t const* array, uint32_t count);

	virtual ~LogFormatterW();
private:
	LogFormatterWImpl* mLog;
};


} // namespace prtx


#endif /* PRTX_LOG_H_ */


/*
 * Trace.h
 *
 *  Created on: 2013-5-5
 *      Author: Administrator
 */

#ifndef TRACE_H_
#define TRACE_H_

#define DEBUGTRACE

#ifdef DEBUGTRACE

#ifdef WIN32
#include <stdarg.h>
#include <stdio.h>
enum LogPriority {
    LOG_UNKNOWN = 0,
    LOG_DEFAULT,
    LOG_VERBOSE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_SILENT,
};
inline bool OutTrace(LogPriority type,const char* tag,const char* format,...)
{
	va_list arg;
	va_start(arg,format);
	vprintf(format,arg);
	va_end(arg);
	return false;
}
#define LOG_Trace OutTrace
#else

#include <android/log.h>
enum LogPriority {
    LOG_UNKNOWN = ANDROID_LOG_UNKNOWN,
    LOG_DEFAULT = ANDROID_LOG_DEFAULT,
    LOG_VERBOSE = ANDROID_LOG_VERBOSE,
    LOG_DEBUG = ANDROID_LOG_DEBUG,
    LOG_INFO = ANDROID_LOG_INFO,
    LOG_WARN = ANDROID_LOG_WARN,
    LOG_ERROR = ANDROID_LOG_ERROR,
    LOG_FATAL = ANDROID_LOG_FATAL,
    LOG_SILENT = ANDROID_LOG_SILENT,
};
#define LOG_Trace __android_log_print

#endif

#else
#define LOG_Trace
#endif
#endif /* TRACE_H_ */

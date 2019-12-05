/*********************** Licensing *******************************************************
*
*   Copyright 2019 @ Evandro Coan, https://github.com/evandrocoan
*
*   Version: 1.0.0
*   Always ensure you are using the latest version by checking:
*   https://gist.github.com/evandrocoan/ecc2f48c0f46391d4c1cc4a0709c847c
*
*  This program is free software; you can redistribute it and/or modify it
*  under the terms of the GNU Lesser General Public License as published by the
*  Free Software Foundation; either version 2.1 of the License, or ( at
*  your option ) any later version.
*
*  This program is distributed in the hope that it will be useful, but
*  WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*****************************************************************************************
*/


// https://stackoverflow.com/questions/787533/is-pragma-once-a-safe-include-guard/1946730#1946730
#ifndef TINYFORMAT_FORMATTER_DEBUGGER_APP_H
#define TINYFORMAT_FORMATTER_DEBUGGER_APP_H

// https://en.cppreference.com/w/cpp/error/runtime_error
#include <stdexcept>

// https://github.com/c42f/tinyformat  --  C like printf support on C++
// https://github.com/bitcoin/bitcoin/issues/9423  --  tinyformat: Too many conversion specifiers in format string
#define TINYFORMAT_ERROR(reasonString) throw std::runtime_error(reasonString)
#include "tinyformat.h"

// Create a nth "variadic" template, see `tinyformat.h` variables TINYFORMAT_ARGTYPES_1, 2, 3... etc
#define TINYFORMAT_FORMATTER_CREATE_NTH_FORMAT(n) template<TINYFORMAT_ARGTYPES(n)> \
std::string secure_tinyformat(const char *formattings, TINYFORMAT_VARARGS(n)) \
{ \
  try { \
    return tfm::format( formattings, TINYFORMAT_PASSARGS(n) ); \
  } \
  catch (std::runtime_error &error) { \
    return std::string( error.what() ) + std::string( ": '" ) + std::string( formattings ) + std::string( "'" ); \
  } \
  catch (...) { \
    return std::string( "Unknown error on the formating string: " ) + std::string( ": '" ) + std::string( formattings ) + std::string( "'" ); \
  } \
}

// Define a basic "variadic" template case with 0 parameters
inline std::string secure_tinyformat(const char *formattings)
{
  try {
    return tfm::format( formattings );
  }
  catch (std::runtime_error &error) {
    return std::string( error.what() ) + std::string( ": '" ) + std::string( formattings ) + std::string( "'" );
  }
  catch (...) {
    return std::string( "Unknown error on the formating string: " ) + std::string( ": '" ) + std::string( formattings ) + std::string( "'" );
  }
}

// Create the "variadic" templates for C++ 98 from 1 up to the maximum defined on
// `tinyformat.h` variables TINYFORMAT_ARGTYPES_1, 2, 3... etc
TINYFORMAT_FOREACH_ARGNUM(TINYFORMAT_FORMATTER_CREATE_NTH_FORMAT)


// https://stackoverflow.com/questions/3781520/how-to-test-if-preprocessor-symbol-is-defined-but-has-no-value
#define TINYFORMAT_FORMATTER_DEBUGGER_DO_EXPAND(value)  value ## 1
#define TINYFORMAT_FORMATTER_DEBUGGER_EXPAND(value)     TINYFORMAT_FORMATTER_DEBUGGER_DO_EXPAND(value)


/**
 * This is to view internal program data while execution. Default value: 0
 *
 * A value like 127 binary(111111) enables all masked debugging levels.
 *
 *  0     - Disables this feature.
 *  1     - Error or very important messages.
 *  4     - Comment messages inside functions calls
 *  8     - High called functions, i.e., create very big massive text output
 *  1024  - Disable debugging with time stamp.
 *  2048  - Disable debugging with file path.
 *  4096  - Direct all `stderr` messages to a file.
 */
#if TINYFORMAT_FORMATTER_DEBUGGER_EXPAND(TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) == 1
  #undef TINYFORMAT_FORMATTER_DEBUGGER_LEVEL
#endif

#if !defined(TINYFORMAT_FORMATTER_DEBUGGER_LEVEL)
  #define TINYFORMAT_FORMATTER_DEBUGGER_LEVEL 0
#endif

#if !defined(TINYFORMAT_FORMATTER_STDERR_DEBUG_FILEPATH)
  #define TINYFORMAT_FORMATTER_STDERR_DEBUG_FILEPATH "stderr.log"
#endif

#define TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_DISABLED_DEBUG     0
#define TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_WITHOUT_TIME_STAMP 1024
#define TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_WITHOUT_PATHHEADER 2048
#define TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_PUT_STDERR_TO_FILE 4096



/**
 * Control all program debugging.
 */
#if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL > TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_DISABLED_DEBUG
  #include <iostream>
  #include <sys/time.h>

  #if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_PUT_STDERR_TO_FILE
    class FileDebugSingleton
    {
      static bool isstarted;
      static FileDebugSingleton* instance;

      FileDebugSingleton();

    public:
      ~FileDebugSingleton();
      static FileDebugSingleton* getInstance();
    };
  #endif

  inline int TINYFORMAT_FORMATTER_timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
  {
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;
    return (diff<0);
  }

  extern struct timeval TINYFORMAT_FORMATTER_timevalBegin;
  extern struct timeval TINYFORMAT_FORMATTER_timevalEnd;
  extern struct timeval TINYFORMAT_FORMATTER_timevalDiff;

  // Initialize the variable on system start up
  inline timeval TINYFORMAT_FORMATTER_gettimeofday(struct timeval *result) {
    gettimeofday(result, NULL);
    return *result;
  }

  #define DEBUGGER_TIME_HEADER \
    time_t theTime = time(NULL); \
    /* https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm */ \
    struct tm* aTime = localtime(&theTime); \
    gettimeofday(&TINYFORMAT_FORMATTER_timevalEnd, NULL); \
    TINYFORMAT_FORMATTER_timeval_subtract(&TINYFORMAT_FORMATTER_timevalDiff, &TINYFORMAT_FORMATTER_timevalEnd, &TINYFORMAT_FORMATTER_timevalBegin); \
    std::cerr << secure_tinyformat( "%04d/%02d/%02d %02d:%02d:%02d.%06i %ld.%06ld ", \
        aTime->tm_year + 1900, aTime->tm_mon + 1, aTime->tm_mday, \
        aTime->tm_hour, aTime->tm_min, aTime->tm_sec, TINYFORMAT_FORMATTER_timevalEnd.tv_usec, \
        TINYFORMAT_FORMATTER_timevalDiff.tv_sec, TINYFORMAT_FORMATTER_timevalDiff.tv_usec \
    ); \
    gettimeofday(&TINYFORMAT_FORMATTER_timevalBegin, NULL);

  #if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_WITHOUT_TIME_STAMP
    #define _TINYFORMAT_FORMATTER_DEBUGGER_TIME_STAMP_HEADER(level)
  #else
    #define _TINYFORMAT_FORMATTER_DEBUGGER_TIME_STAMP_HEADER(level) \
      if( !((level) & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_WITHOUT_TIME_STAMP) ) { \
        DEBUGGER_TIME_HEADER \
      }
  #endif

  // https://stackoverflow.com/questions/1706346/file-macro-manipulation-handling-at-compile-time/
  inline const char * const TINYFORMAT_FORMATTER_debugger_strend(const char * const str) {
    return *str ? TINYFORMAT_FORMATTER_debugger_strend( str + 1 ) : str;
  }

  inline const char * const TINYFORMAT_FORMATTER_debugger_fromlastslash(const char * const start, const char * const end) {
    return ( end >= start && *end != '/' && *end != '\\' ) ? TINYFORMAT_FORMATTER_debugger_fromlastslash( start, end - 1 ) : ( end + 1 );
  }

  inline const char * const TINYFORMAT_FORMATTER_debugger_pathlast(const char * const path) {
    return TINYFORMAT_FORMATTER_debugger_fromlastslash( path, TINYFORMAT_FORMATTER_debugger_strend( path ) );
  }

  #define DEBUGGER_PATH_HEADER \
    std::cerr << secure_tinyformat( "%s|%s:%s ", \
        TINYFORMAT_FORMATTER_debugger_pathlast( __FILE__ ) , __FUNCTION__, __LINE__ );

  #if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_WITHOUT_PATHHEADER
    #define _TINYFORMAT_FORMATTER_DEBUGGER_TIME_FILE_PATH_HEADER(level)
  #else
    #define _TINYFORMAT_FORMATTER_DEBUGGER_TIME_FILE_PATH_HEADER(level) \
      if( !((level) & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_WITHOUT_PATHHEADER) ) { \
        DEBUGGER_PATH_HEADER \
      }
  #endif

  /**
   * Print like function for logging putting a new line at the end of string. See the variables
   * 'TINYFORMAT_FORMATTER_DEBUGGER_LEVEL' for the available levels.
   *
   * On this function only, a time stamp on scientific notation as `d.dde+ddd d.ddde+ddd` will be
   * used. These values mean the `CPU time used` in milliseconds and the `Wall clock time passed`
   * respectively.
   *
   * @param level     the debugging desired level to be printed.
   * @param ...       variable number os formating arguments parameters.
   */
  #define LOG(level, ...) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      /* std::clock_t ctime_clock_now = std::clock(); */ \
      _TINYFORMAT_FORMATTER_DEBUGGER_TIME_STAMP_HEADER(level) \
      _TINYFORMAT_FORMATTER_DEBUGGER_TIME_FILE_PATH_HEADER( level ) \
      std::cerr << secure_tinyformat( __VA_ARGS__ ) << std::endl; \
      /* _debugger_current_saved_c_time = ctime_clock_now; */ \
    } \
  } \
  while( 0 )

  /**
   * The same as LOG(...) just above, but do not put automatically a new line.
   */
  #define LOGLN(level, ...) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      /* std::clock_t ctime_clock_now = std::clock(); */ \
      _TINYFORMAT_FORMATTER_DEBUGGER_TIME_STAMP_HEADER(level) \
      _TINYFORMAT_FORMATTER_DEBUGGER_TIME_FILE_PATH_HEADER( level ) \
      std::cerr << secure_tinyformat( __VA_ARGS__ ); \
      /* _debugger_current_saved_c_time = ctime_clock_now; */ \
    } \
  } \
  while( 0 )

  /**
   * The same as LOGLC(...) just above, but do not put automatically a new line, neither time stamp.
   */
  #define LOGLC(level, ...) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      std::cerr << secure_tinyformat( __VA_ARGS__ ) << std::flush; \
    } \
  } \
  while( 0 )

  /**
   * The same a LOG, but used to hide a whole code block behind the debug level.
   */
  #define LOGCD(level, code) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      code; \
    } \
  } \
  while( 0 )

  /**
   * The same as LOG(...), but it is for standard program output.
   */
  #define PRINT(level, ...) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      std::cerr << secure_tinyformat( __VA_ARGS__ ) << std::endl; \
    } \
  } \
  while( 0 )

  /**
   * The same as LOGLN(...), but it is for standard program output.
   */
  #define PRINTLN(level, ...) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      std::cerr << secure_tinyformat( __VA_ARGS__ ) << std::flush; \
    } \
  } \
  while( 0 )


#else

  #define DEBUGGER_TIME_HEADER
  #define DEBUGGER_PATH_HEADER
  #define LOG(level, ...)
  #define LOGLN(level, ...)
  #define LOGLC(level, ...)
  #define LOGCD(level, ...)

  /**
   * The same as LOG(...), but it is for standard program output when the debugging is disabled.
   */
  #define PRINT(level, ...) \
  do \
  { \
    std::cerr << secure_tinyformat( __VA_ARGS__ ) << std::endl; \
  } \
  while( 0 )

  /**
   * The same as LOGLN(...), but it is for standard program output when the debugging is disabled.
   */
  #define PRINTLN(level, ...) \
  do \
  { \
    std::cerr << secure_tinyformat( __VA_ARGS__ ) << std::flush; \
  } \
  while( 0 )


#endif // #if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL > TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_DISABLED_DEBUG


#endif // TINYFORMAT_FORMATTER_DEBUGGER_APP_H



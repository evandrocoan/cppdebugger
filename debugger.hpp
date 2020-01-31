/*********************** Licensing *******************************************************
*
*   Copyright 2019 @ Evandro Coan, https://github.com/evandrocoan
*
*   Tinyformat Formatter Debugger C++ 98 and 11 Header Version: 1.0.0
*   Always ensure you are using the latest version by checking:
*   https://github.com/evandrocoan/cppdebugger
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

#define TINYFORMAT_FORMATTER_STDERR_DEBUG_FILEPATH "stderr.log"


// https://en.cppreference.com/w/cpp/error/runtime_error
#include <stdexcept>

// https://stackoverflow.com/questions/3781520/how-to-test-if-preprocessor-symbol-is-defined-but-has-no-value
#define TINYFORMAT_FORMATTER_DEBUGGER_IS_MACRO_EMPTY_DO_EXPAND(value) value ## 1
#define TINYFORMAT_FORMATTER_DEBUGGER_IS_MACRO_EMPTY(value) TINYFORMAT_FORMATTER_DEBUGGER_IS_MACRO_EMPTY_DO_EXPAND(value)

// Uncomment this `TINYFORMAT_NO_VARIADIC_TEMPLATES` to force using C++ 98 Standard
// #define TINYFORMAT_NO_VARIADIC_TEMPLATES

#include <errno.h>
#include <string.h>

// https://github.com/c42f/tinyformat  --  C like printf support on C++
// https://github.com/bitcoin/bitcoin/issues/9423  --  tinyformat: Too many conversion specifiers in format string
#define TINYFORMAT_ERROR(reasonString) throw std::runtime_error(reasonString)
#include "tinyformat.h"
#include "cpp98templates.h"

#if defined(TINYFORMAT_USE_VARIADIC_TEMPLATES)
  #define TINYFORMAT_FORMATTER_CONSTEXPR constexpr

  // https://github.com/laanwj/bitcoin/blob/3b092bd9b6b3953d5c3052d57e4827dbd85941fd/src/util.h
  template<typename... Args>
  std::string secure_tinyformat(const char* formattings, const Args&... arguments)
  {
    try {
      return tfm::format( formattings, arguments... );
    }
    catch (std::runtime_error &error) {
      return std::string( error.what() ) + std::string( ": " ) + std::string( formattings );
    }
    catch (...) {
      return std::string( "Unknown error on the formatting string: " ) + std::string( formattings );
    }
  }

  template<typename... Args>
  std::ostream& secure_tinyformat(std::ostream& out, const char* formattings, const Args&... arguments)
  {
    try {
      tfm::format( out, formattings, arguments... );
    }
    catch (std::runtime_error &error) {
      out << std::string( error.what() ) + std::string( ": " ) + std::string( formattings );
    }
    catch (...) {
      out << std::string( "Unknown error on the formatting string: " ) + std::string( formattings );
    }
    return out;
  }

#else
  #define TINYFORMAT_FORMATTER_CONSTEXPR

  // Create a nth "variadic" template, see `tinyformat.h` variables TINYFORMAT_ARGTYPES_1, 2, 3... etc
  #define CPP98VARIADICTEMPLATE_FORMATTER_CREATE_NTH_FORMAT_STR(n) \
  template<class T0 CPP98VARIADICTEMPLATE_ARGTYPES(n,,,,)> \
  inline std::string secure_tinyformat(const T0& v0 CPP98VARIADICTEMPLATE_VARARGS(n,,)) \
  { \
    try { \
      return tfm::format( v0 CPP98VARIADICTEMPLATE_PASSARGS(n,,,,) ); \
    } \
    catch (std::runtime_error &error) { \
      return std::string( error.what() ) + std::string( ": '" ) + std::string( v0 ) + std::string( "'" ); \
    } \
    catch (...) { \
      return std::string( "Unknown error on the formating string: " ) + std::string( ": '" ) + std::string( v0 ) + std::string( "'" ); \
    } \
  }

  #define CPP98VARIADICTEMPLATE_FORMATTER_CREATE_NTH_FORMAT_OSS(n) \
  template<class T0 CPP98VARIADICTEMPLATE_ARGTYPES(n,,,,)> \
  inline std::ostream& secure_tinyformat(std::ostream& out, const T0& v0 CPP98VARIADICTEMPLATE_VARARGS(n,,)) \
  { \
    try { \
      tfm::format( out, v0 CPP98VARIADICTEMPLATE_PASSARGS(n,,,,) ); \
    } \
    catch (std::runtime_error &error) { \
      out << std::string( error.what() ) + std::string( ": '" ) + std::string( v0 ) + std::string( "'" ); \
    } \
    catch (...) { \
      out << std::string( "Unknown error on the formating string: " ) + std::string( ": '" ) + std::string( v0 ) + std::string( "'" ); \
    } \
    return out;\
  }

  // Create the "variadic" templates for C++ 98 from 1 up to the maximum defined on
  // `tinyformat.h` variables CPP98VARIADICTEMPLATE_ARGTYPES_1, 2, 3... etc
  CPP98VARIADICTEMPLATE_FOREACH_ARGNUM(CPP98VARIADICTEMPLATE_FORMATTER_CREATE_NTH_FORMAT_STR)
  CPP98VARIADICTEMPLATE_FOREACH_ARGNUM(CPP98VARIADICTEMPLATE_FORMATTER_CREATE_NTH_FORMAT_OSS)

  #undef CPP98VARIADICTEMPLATE_FORMATTER_CREATE_NTH_FORMAT_STR
  #undef CPP98VARIADICTEMPLATE_FORMATTER_CREATE_NTH_FORMAT_OSS
#endif



/**
 * This is to view internal program data while execution. Default value: 0
 *
 * A value like 127 binary(111111) enables all masked debugging levels
 *
 *  0     - Disables this feature
 *  1     - Error or very important messages
 *  4     - Comment messages inside functions calls
 *  8     - High called functions, i.e., create very big massive text output
 *
 *  4096  - Direct all `stderr` messages to a file
 *  8192  - Put a lock around the `stderr` messages for multithreading synchronization
 */
#if TINYFORMAT_FORMATTER_DEBUGGER_IS_MACRO_EMPTY(TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) == 1
  #undef TINYFORMAT_FORMATTER_DEBUGGER_LEVEL
#endif

#if !defined(TINYFORMAT_FORMATTER_DEBUGGER_LEVEL)
  #define TINYFORMAT_FORMATTER_DEBUGGER_LEVEL 0
#endif

#define TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_DISABLED_DEBUG     0
#define TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_PUT_STDERR_TO_FILE 4096
#define TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_STDERR_OUTPUT_LOCK 8192



/**
 * Control all program debugging.
 */
#if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL > TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_DISABLED_DEBUG
  #include <iostream>
  #include <cstdio>

  #if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_STDERR_OUTPUT_LOCK

    #if defined(TINYFORMAT_USE_VARIADIC_TEMPLATES)
      #include <mutex>
      extern std::recursive_mutex TINYFORMAT_FORMATTER_stderrlockoutput;
    #else
      #include <base/simple_lock.hpp>
      extern SimpleLock TINYFORMAT_FORMATTER_stderrlockoutput;
    #endif

    #define TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK \
      try { \
      TINYFORMAT_FORMATTER_stderrlockoutput.lock();

    #define TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK \
      TINYFORMAT_FORMATTER_stderrlockoutput.unlock(); \
      } \
      catch (...) { \
        std::cerr << secure_tinyformat( "Error: Unknown exception when locking the stderr output!" ); \
        std::cerr << std::flush; \
      }
  #else
    #define TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK
    #define TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK
  #endif


  #if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_PUT_STDERR_TO_FILE
    class TINYFORMAT_FORMATTER_FileDebugger
    {
      static bool isstarted;
      static TINYFORMAT_FORMATTER_FileDebugger* instance;

    public:
      TINYFORMAT_FORMATTER_FileDebugger();
      ~TINYFORMAT_FORMATTER_FileDebugger();

      static TINYFORMAT_FORMATTER_FileDebugger* getInstance();
    };
  #endif


  // https://stackoverflow.com/questions/1706346/file-macro-manipulation-handling-at-compile-time/
  TINYFORMAT_FORMATTER_CONSTEXPR inline const char* const TINYFORMAT_FORMATTER_debugger_strend(const char* const str) {
      return *str ? TINYFORMAT_FORMATTER_debugger_strend(str + 1) : str;
  }

  TINYFORMAT_FORMATTER_CONSTEXPR inline const char* const TINYFORMAT_FORMATTER_debugger_fromlastslash(const char* const start, const char* const end) {
      return (end >= start && *end != '/' && *end != '\\') ? TINYFORMAT_FORMATTER_debugger_fromlastslash(start, end - 1) : (end + 1);
  }

  TINYFORMAT_FORMATTER_CONSTEXPR inline const char* const TINYFORMAT_FORMATTER_debugger_pathlast(const char* const path) {
      return TINYFORMAT_FORMATTER_debugger_fromlastslash(path, TINYFORMAT_FORMATTER_debugger_strend(path));
  }

  // https://akrzemi1.wordpress.com/2011/05/11/parsing-strings-at-compile-time-part-i/
  #define TINYFORMAT_FORMATTER_DEBUGGER_PATH_HEADER do \
  { \
    TINYFORMAT_FORMATTER_CONSTEXPR const char* myExpression = TINYFORMAT_FORMATTER_debugger_pathlast( __FILE__ ); \
    std::cerr << secure_tinyformat( "%s|%s:%s ", myExpression , __FUNCTION__, __LINE__ ); \
  } \
  while( 0 );


  #if defined(TINYFORMAT_USE_VARIADIC_TEMPLATES)
    #include <chrono>
    #include <ctime>

    // http://en.cppreference.com/w/cpp/chrono/c/clock
    // https://stackoverflow.com/questions/12392278/measure-time-in-linux-time-vs-clock-vs-getrusage-vs-clock-gettime-vs-gettimeof
    extern std::clock_t TINYFORMAT_FORMATTER_debugger_current_saved_c_time;
    extern std::chrono::time_point< std::chrono::high_resolution_clock > TINYFORMAT_FORMATTER_debugger_current_saved_chrono_time;

    #define TINYFORMAT_FORMATTER_DEBUGGER_TIME_HEADER do \
    { \
      /* std::clock_t ctime_clock_now = std::clock(); */ \
      auto chrono_clock_now = std::chrono::high_resolution_clock::now(); \
      auto duration = chrono_clock_now.time_since_epoch(); \
      /* typedef std::chrono::duration< int, std::ratio_multiply< std::chrono::hours::period, std::ratio< 21 > >::type > Days; */ \
      /* Days days = std::chrono::duration_cast< Days >( duration ); */ \
      /* duration -= days; */ \
      auto hours = std::chrono::duration_cast< std::chrono::hours >( duration ); \
      duration -= hours; \
      auto minutes = std::chrono::duration_cast< std::chrono::minutes >( duration ); \
      duration -= minutes; \
      auto seconds = std::chrono::duration_cast< std::chrono::seconds >( duration ); \
      duration -= seconds; \
      auto milliseconds = std::chrono::duration_cast< std::chrono::milliseconds >( duration ); \
      duration -= milliseconds; \
      auto microseconds = std::chrono::duration_cast< std::chrono::microseconds >( duration ); \
      /* duration -= microseconds; */ \
      /* auto nanoseconds = std::chrono::duration_cast< std::chrono::nanoseconds >( duration ); */ \
      time_t theTime = time( NULL ); \
      /* https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm */ \
      struct tm* aTime = localtime( &theTime ); \
      std::cerr << secure_tinyformat( "%04d/%02d/%02d %02d:%02d:%02d:%03d.%03d %.3e ", /* %.3e */ \
          aTime->tm_year + 1900, aTime->tm_mon + 1, aTime->tm_mday, \
          aTime->tm_hour, minutes.count(), seconds.count(), milliseconds.count(), microseconds.count(), /* nanoseconds.count(), */ \
          std::chrono::duration<double, std::milli>( chrono_clock_now - TINYFORMAT_FORMATTER_debugger_current_saved_chrono_time ).count() \
          /* ( 1000.0 * ( ctime_clock_now - TINYFORMAT_FORMATTER_debugger_current_saved_c_time ) ) / CLOCKS_PER_SEC */ \
      ); \
      /* TINYFORMAT_FORMATTER_debugger_current_saved_c_time = ctime_clock_now; */ \
      TINYFORMAT_FORMATTER_debugger_current_saved_chrono_time = chrono_clock_now; \
    } \
    while( 0 );
  #else
    #include <sys/time.h>

    extern struct timeval TINYFORMAT_FORMATTER_timevalBegin;
    extern struct timeval TINYFORMAT_FORMATTER_timevalEnd;
    extern struct timeval TINYFORMAT_FORMATTER_timevalDiff;

    // Initialize the variable on system start up
    inline timeval TINYFORMAT_FORMATTER_gettimeofday(struct timeval *result) {
      gettimeofday( result, NULL );
      return *result;
    }

    #define TINYFORMAT_FORMATTER_timersub(a, b, result) do \
    { \
      (result)->tv_sec = (a)->tv_sec - (b)->tv_sec; \
      (result)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
      if ((result)->tv_usec < 0) { \
        --(result)->tv_sec; \
        (result)->tv_usec += 1000000; \
      } \
    } while( 0 );

    #define TINYFORMAT_FORMATTER_DEBUGGER_TIME_HEADER do \
    { \
      time_t theTime = time( NULL ); \
      /* https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm */ \
      struct tm* aTime = localtime( &theTime ); \
      gettimeofday( &TINYFORMAT_FORMATTER_timevalEnd, NULL ); \
      TINYFORMAT_FORMATTER_timersub( &TINYFORMAT_FORMATTER_timevalEnd, &TINYFORMAT_FORMATTER_timevalBegin, &TINYFORMAT_FORMATTER_timevalDiff ); \
      std::cerr << secure_tinyformat( "%04d/%02d/%02d %02d:%02d:%02d.%06i %ld.%06ld ", \
          aTime->tm_year + 1900, aTime->tm_mon + 1, aTime->tm_mday, \
          aTime->tm_hour, aTime->tm_min, aTime->tm_sec, TINYFORMAT_FORMATTER_timevalEnd.tv_usec, \
          TINYFORMAT_FORMATTER_timevalDiff.tv_sec, TINYFORMAT_FORMATTER_timevalDiff.tv_usec \
      ); \
      gettimeofday( &TINYFORMAT_FORMATTER_timevalBegin, NULL ); \
    } \
    while( 0 );
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
   * @param ...       variable number os formatting arguments parameters.
   */
  #define TLOG(level, ...) do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK \
      TINYFORMAT_FORMATTER_DEBUGGER_TIME_HEADER \
      TINYFORMAT_FORMATTER_DEBUGGER_PATH_HEADER \
      std::cerr << secure_tinyformat( __VA_ARGS__ ); \
      std::cerr << std::endl; \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK \
    } \
  } \
  while( 0 )

  /**
   * The same as TLOG(...) just above, but do not put automatically a new line.
   */
  #define TLOGLN(level, ...) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK \
      TINYFORMAT_FORMATTER_DEBUGGER_TIME_HEADER \
      TINYFORMAT_FORMATTER_DEBUGGER_PATH_HEADER \
      std::cerr << secure_tinyformat( __VA_ARGS__ ); \
      std::cerr << std::flush; \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK \
    } \
  } \
  while( 0 )

  /**
   * The same as TLOG(...) just above, but it also print the log message when disabled ignoring the log level.
   */
  #define TLOGERR(...) do \
  { \
    TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK \
    TINYFORMAT_FORMATTER_DEBUGGER_TIME_HEADER \
    TINYFORMAT_FORMATTER_DEBUGGER_PATH_HEADER \
    std::cerr << secure_tinyformat( __VA_ARGS__ ); \
    std::cerr << std::endl; \
    TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK \
  } \
  while( 0 )

  /**
   * The same as TLOGLC(...) just above, but do not put automatically a new line, neither time stamp.
   */
  #define TLOGLC(level, ...) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK \
      std::cerr << secure_tinyformat( __VA_ARGS__ ); \
      std::cerr << std::flush; \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK \
    } \
  } \
  while( 0 )

  /**
   * The same a LOG, but used to hide a whole code block behind the debug level.
   */
  #define TLOGCD(level, code) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK \
      code; \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK \
    } \
  } \
  while( 0 )

  /**
   * The same as TLOG(...), but it is for standard program output.
   */
  #define TPRINT(level, ...) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK \
      std::cerr << secure_tinyformat( __VA_ARGS__ ); \
      std::cerr << std::endl; \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK \
    } \
  } \
  while( 0 )

  /**
   * The same as TLOGLN(...), but it is for standard program output.
   */
  #define TPRINTLN(level, ...) \
  do \
  { \
    if( (level) & (TINYFORMAT_FORMATTER_DEBUGGER_LEVEL) ) \
    { \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK \
      std::cerr << secure_tinyformat( __VA_ARGS__ ); \
      std::cerr << std::flush; \
      TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK \
    } \
  } \
  while( 0 )


#else
  #define TINYFORMAT_FORMATTER_DEBUGGER_TIME_HEADER
  #define TINYFORMAT_FORMATTER_DEBUGGER_PATH_HEADER

  #define TINYFORMAT_FORMATTER_DEBUGGER_STDERR_LOCK
  #define TINYFORMAT_FORMATTER_DEBUGGER_STDERR_UNLOCK

  #define TLOG(level, ...)
  #define TLOGLN(level, ...)
  #define TLOGLC(level, ...)
  #define TLOGCD(level, ...)

  /**
   * The same as TLOG(...) just above, but it also print the log message when disabled ignoring the log level.
   */
  #define TLOGERR(...) do \
  { \
    std::cerr << secure_tinyformat( __VA_ARGS__ ); \
    std::cerr << std::endl; \
  } \
  while( 0 )

  /**
   * The same as TLOG(...), but it is for standard program output when the debugging is disabled.
   */
  #define TPRINT(level, ...) \
  do \
  { \
    std::cerr << secure_tinyformat( __VA_ARGS__ ); \
    std::cerr << std::endl; \
  } \
  while( 0 )

  /**
   * The same as TLOGLN(...), but it is for standard program output when the debugging is disabled.
   */
  #define TPRINTLN(level, ...) \
  do \
  { \
    std::cerr << secure_tinyformat( __VA_ARGS__ ); \
    std::cerr << std::flush; \
  } \
  while( 0 )


#endif // #if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL > TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_DISABLED_DEBUG


#endif // TINYFORMAT_FORMATTER_DEBUGGER_APP_H

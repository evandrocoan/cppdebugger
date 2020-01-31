/*********************** Licensing *******************************************************
*
*   Copyright 2019 @ Evandro Coan, https://github.com/evandrocoan
*
*   Tinyformat Formatter Debugger C++ 98 and 11 Cpp Version: 1.0.0
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


#include "debugger.hpp"

#if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL > TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_DISABLED_DEBUG \
      && !(TINYFORMAT_FORMATTER_DEBUGGER_LEVEL & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_WITHOUT_TIME_STAMP)

  #if defined(TINYFORMAT_USE_VARIADIC_TEMPLATES)
    std::clock_t TINYFORMAT_FORMATTER_debugger_current_saved_c_time = std::clock();
    std::chrono::time_point<std::chrono::high_resolution_clock> TINYFORMAT_FORMATTER_debugger_current_saved_chrono_time = std::chrono::high_resolution_clock::now();
  #else
    struct timeval TINYFORMAT_FORMATTER_timevalBegin = TINYFORMAT_FORMATTER_gettimeofday(&TINYFORMAT_FORMATTER_timevalBegin);
    struct timeval TINYFORMAT_FORMATTER_timevalEnd;
    struct timeval TINYFORMAT_FORMATTER_timevalDiff;
  #endif

#endif


#if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_STDERR_OUTPUT_LOCK
  #if defined(TINYFORMAT_USE_VARIADIC_TEMPLATES)
    std::recursive_mutex TINYFORMAT_FORMATTER_stderrlockoutput;
  #else
    SimpleLock TINYFORMAT_FORMATTER_stderrlockoutput;
  #endif
#endif


// https://forums.alliedmods.net/showthread.php?t=277682#Cpp  --  [TUT] How to use an efficient debug system
// https://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files
#if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_PUT_STDERR_TO_FILE

  TINYFORMAT_FORMATTER_FileDebugger::TINYFORMAT_FORMATTER_FileDebugger()
  {
    // http://www.cplusplus.com/reference/cstdio/freopen/
    if( TINYFORMAT_FORMATTER_FileDebugger::isstarted ) {
      std::cerr << "Error: freopen(stderr) is already open!" << std::endl;
    }
    else {
      TINYFORMAT_FORMATTER_FileDebugger::isstarted = true;
      FILE* stream = freopen( TINYFORMAT_FORMATTER_STDERR_DEBUG_FILEPATH, "a", stderr );

      if( stream == NULL ) {
        std::cerr << "Error: freopen(stderr) could not be opend: " << strerror(errno) << "!" << std::endl;
      }
    }
  }

  TINYFORMAT_FORMATTER_FileDebugger::~TINYFORMAT_FORMATTER_FileDebugger() {
    TINYFORMAT_FORMATTER_FileDebugger::isstarted = false;

    if( TINYFORMAT_FORMATTER_FileDebugger::isstarted ) {
      fclose( stderr );
      TINYFORMAT_FORMATTER_FileDebugger::instance = NULL;
    }
    else {
      std::cerr << "Error: freopen(stderr) is already closed!" << std::endl;
    }
  }

  TINYFORMAT_FORMATTER_FileDebugger* TINYFORMAT_FORMATTER_FileDebugger::getInstance()
  {
    if( TINYFORMAT_FORMATTER_FileDebugger::isstarted ) {
      return TINYFORMAT_FORMATTER_FileDebugger::instance;
    }

    TINYFORMAT_FORMATTER_FileDebugger::instance = new TINYFORMAT_FORMATTER_FileDebugger();
    return TINYFORMAT_FORMATTER_FileDebugger::instance;
  }

  bool TINYFORMAT_FORMATTER_FileDebugger::isstarted = false;
  TINYFORMAT_FORMATTER_FileDebugger* TINYFORMAT_FORMATTER_FileDebugger::instance = TINYFORMAT_FORMATTER_FileDebugger::getInstance();
#endif

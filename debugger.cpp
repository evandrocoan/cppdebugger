/*********************** Licensing *******************************************************
*
*   Copyright 2019 @ Evandro Coan, https://github.com/evandrocoan
*
*   Tinyformat Formatter Debugger C++ 98 and 11 Cpp Version: 1.0.0
*   Always ensure you are using the latest version by checking:
*   https://gist.github.com/evandrocoan/a3d13a0e7c852fd079189330201c88d7
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


// https://forums.alliedmods.net/showthread.php?t=277682#Cpp  --  [TUT] How to use an efficient debug system
// https://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files
#if TINYFORMAT_FORMATTER_DEBUGGER_LEVEL & TINYFORMAT_FORMATTER_DEBUGGER_LEVEL_PUT_STDERR_TO_FILE

  FileDebugSingleton::FileDebugSingleton()
  {
    // http://www.cplusplus.com/reference/cstdio/freopen/
    FileDebugSingleton::isstarted = true;
    freopen( TINYFORMAT_FORMATTER_STDERR_DEBUG_FILEPATH, "a", stderr );
  }

  FileDebugSingleton::~FileDebugSingleton() {
    fclose( stderr );
  }

  FileDebugSingleton* FileDebugSingleton::getInstance() {
    if( FileDebugSingleton::isstarted ) {
      return FileDebugSingleton::instance;
    }

    FileDebugSingleton::instance = new FileDebugSingleton();
    FileDebugSingleton::isstarted = true;
    return FileDebugSingleton::instance;
  }

  bool FileDebugSingleton::isstarted = false;
  FileDebugSingleton* FileDebugSingleton::instance = FileDebugSingleton::getInstance();
#endif

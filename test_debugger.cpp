/*********************** Licensing *******************************************************
*
*   Copyright 2019 @ Evandro Coan, https://github.com/evandrocoan
*
*   Tinyformat Formatter Debugger C++ 98 and 11 Testing Version: 1.0.0
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
#include <stdio.h>

int main(int argc, char const *argv[])
{
    fprintf( stderr, "First test\n" );
    LOG( 1, "Hi" );
    LOG( 1, "Hi %s", 1 );
    LOG( 1, "Hi %s" );
    LOG( 1, "Hi %s %s", 1 );

    fprintf( stderr, "Second test\n" );
    LOG( 1+1024, "Hi" );
    LOG( 1+1024, "Hi %s", 1 );
    LOG( 1+1024, "Hi %s" );
    LOG( 1+1024, "Hi %s %s", 1 );

    fprintf( stderr, "Third test\n" );
    LOG( 1+2048, "Hi" );
    LOG( 1+2048, "Hi %s", 1 );
    LOG( 1+2048, "Hi %s" );
    LOG( 1+2048, "Hi %s %s", 1 );
}

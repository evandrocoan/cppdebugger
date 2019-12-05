You need to first download the https://github.com/c42f/tinyformat/blob/master/tinyformat.h header and put it together with `debugger.h`.

This was first publised on https://github.com/evandrocoan/InteractiveGraphicSystem/blob/master/src/debugger.h

To use this, just build the `debugger.hpp` and `debugger.cpp` with `-DMY_CUSTOM_DEBUGGER_LEVEL=127+4096` and linking `debugger.cpp` with your project files, while including the `debugger.h` file headers where you would like to use it.
```
$ g++ -o main -g -ggdb debugger.cpp test_debugger.cpp -DTINYFORMAT_FORMATTER_DEBUGGER_LEVEL=127 && ./main
```

**test_debugger.cpp**
```c++
#include "debugger.h"
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
```

**Output result**
```
First test
2019/12/05 15:33:43.447807 0.000096 test_debugger.cpp|main:7 Hi
2019/12/05 15:33:43.447872 0.000016 test_debugger.cpp|main:8 Hi 1
2019/12/05 15:33:43.447913 0.000035 test_debugger.cpp|main:9 tinyformat: Too many conversion specifiers in format string: 'Hi %s'
2019/12/05 15:33:43.447987 0.000068 test_debugger.cpp|main:10 tinyformat: Too many conversion specifiers in format string: 'Hi %s %s'
Second test
test_debugger.cpp|main:13 Hi
test_debugger.cpp|main:14 Hi 1
test_debugger.cpp|main:15 tinyformat: Too many conversion specifiers in format string: 'Hi %s'
test_debugger.cpp|main:16 tinyformat: Too many conversion specifiers in format string: 'Hi %s %s'
Third test
2019/12/05 15:33:43.448108 0.000116 Hi
2019/12/05 15:33:43.448119 0.000005 Hi 1
2019/12/05 15:33:43.448147 0.000023 tinyformat: Too many conversion specifiers in format string: 'Hi %s'
2019/12/05 15:33:43.448181 0.000029 tinyformat: Too many conversion specifiers in format string: 'Hi %s %s'
```

There is not need to specify any other format specifier other than "%s", unless you would like custom behavior.

By default, this logging system will be disabled and no changes are required by any project using this include.

When enabled, it will create a file on `stderr.log`. The file `mylogger_stderr.txt` will contain all messaged outputted to the `stderr` stream, i.e., both `std::cerr << "My message" << std::endl;` or `LOG(1, "My message");` are going to be in that file.

It uses the http://www.cplusplus.com/reference/cstdio/freopen/ function from `<cstdio>` and it works with legacy `C++ 98` code.


//   Copyright (C) 2011, Chris Foster [chris42f (at) gmail (d0t) com]
//   Copyright 2020 @ Evandro Coan, https://github.com/evandrocoan
//
//   C++ 98 Variadic Templates Support Header Version: 1.0.0
//   Always ensure you are using the latest version by checking:
//   https://github.com/evandrocoan/cppdebugger
//
// Boost Software License - Version 1.0
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

//------------------------------------------------------------------------------
// Tools for emulating variadic templates in C++98.  The basic idea here is
// stolen from the boost preprocessor metaprogramming library and cut down to
// be just general enough for what we need.

#define CPP98VARIADICTEMPLATE_OPEN_PAREN (
#define CPP98VARIADICTEMPLATE_CLOSE_PAREN )

#define CPP98VARIADICTEMPLATE_ARGTYPES(n,begin,end,...) CPP98VARIADICTEMPLATE_ARGTYPES_ ## n (begin,end,__VA_ARGS__)
#define CPP98VARIADICTEMPLATE_VARARGS(n,...)            CPP98VARIADICTEMPLATE_VARARGS_  ## n (__VA_ARGS__)
#define CPP98VARIADICTEMPLATE_PASSARGS(n,begin,end,...) CPP98VARIADICTEMPLATE_PASSARGS_ ## n (begin,end,__VA_ARGS__)

// To keep it as transparent as possible, the macros below have been generated
// using python via the excellent cog code generation script.  This avoids
// the need for a bunch of complex (but more general) preprocessor tricks as
// used in boost.preprocessor.
//
// To rerun the code generation in place, use `cog -r cpp98templates.h`
// (see http://nedbatchelder.com/code/cog).  Alternatively you can just create
// extra versions by hand.

/*[[[cog
maxParams = 16

def makeCommaSepLists(lineTemplate, elemTemplate, startInd=1):
    for j in range(startInd,maxParams+1):
        list = ', '.join([elemTemplate % {'i':i} for i in range(startInd,j+1)])
        cog.outl(lineTemplate % {'j':j, 'list':list})

cog.outl('#define CPP98VARIADICTEMPLATE_ARGTYPES_0(...)')
makeCommaSepLists('#define CPP98VARIADICTEMPLATE_ARGTYPES_%(j)d(begin,end,...) begin __VA_ARGS__ %(list)s end',
                  'class T%(i)d')

cog.outl()
cog.outl('#define CPP98VARIADICTEMPLATE_VARARGS_0(...)')
makeCommaSepLists('#define CPP98VARIADICTEMPLATE_VARARGS_%(j)d(...) __VA_ARGS__ %(list)s',
                  'const T%(i)d& v%(i)d')

cog.outl()
cog.outl('#define CPP98VARIADICTEMPLATE_PASSARGS_0(...)')
makeCommaSepLists('#define CPP98VARIADICTEMPLATE_PASSARGS_%(j)d(begin,end,...) __VA_ARGS__ %(list)s', 'begin v%(i)d end')

cog.outl()
cog.outl('#define CPP98VARIADICTEMPLATE_FOREACH_ARGNUM(m) \\\n    m(0) ' +
         ' '.join(['m(%d)' % (j,) for j in range(1,maxParams+1)]))
]]]*/
#define CPP98VARIADICTEMPLATE_ARGTYPES_0(...)
#define CPP98VARIADICTEMPLATE_ARGTYPES_1(begin,end,...) begin __VA_ARGS__ class T1 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_2(begin,end,...) begin __VA_ARGS__ class T1, class T2 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_3(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_4(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_5(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_6(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_7(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_8(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_9(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_10(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_11(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_12(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_13(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_14(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_15(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15 end
#define CPP98VARIADICTEMPLATE_ARGTYPES_16(begin,end,...) begin __VA_ARGS__ class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class T16 end

#define CPP98VARIADICTEMPLATE_VARARGS_0(...)
#define CPP98VARIADICTEMPLATE_VARARGS_1(...) __VA_ARGS__ const T1& v1
#define CPP98VARIADICTEMPLATE_VARARGS_2(...) __VA_ARGS__ const T1& v1, const T2& v2
#define CPP98VARIADICTEMPLATE_VARARGS_3(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3
#define CPP98VARIADICTEMPLATE_VARARGS_4(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4
#define CPP98VARIADICTEMPLATE_VARARGS_5(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5
#define CPP98VARIADICTEMPLATE_VARARGS_6(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6
#define CPP98VARIADICTEMPLATE_VARARGS_7(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7
#define CPP98VARIADICTEMPLATE_VARARGS_8(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8
#define CPP98VARIADICTEMPLATE_VARARGS_9(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8, const T9& v9
#define CPP98VARIADICTEMPLATE_VARARGS_10(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8, const T9& v9, const T10& v10
#define CPP98VARIADICTEMPLATE_VARARGS_11(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8, const T9& v9, const T10& v10, const T11& v11
#define CPP98VARIADICTEMPLATE_VARARGS_12(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12
#define CPP98VARIADICTEMPLATE_VARARGS_13(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13
#define CPP98VARIADICTEMPLATE_VARARGS_14(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14
#define CPP98VARIADICTEMPLATE_VARARGS_15(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15
#define CPP98VARIADICTEMPLATE_VARARGS_16(...) __VA_ARGS__ const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15, const T16& v16

#define CPP98VARIADICTEMPLATE_PASSARGS_0(...)
#define CPP98VARIADICTEMPLATE_PASSARGS_1(begin,end,...) __VA_ARGS__ begin v1 end
#define CPP98VARIADICTEMPLATE_PASSARGS_2(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end
#define CPP98VARIADICTEMPLATE_PASSARGS_3(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end
#define CPP98VARIADICTEMPLATE_PASSARGS_4(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end
#define CPP98VARIADICTEMPLATE_PASSARGS_5(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end
#define CPP98VARIADICTEMPLATE_PASSARGS_6(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end
#define CPP98VARIADICTEMPLATE_PASSARGS_7(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end
#define CPP98VARIADICTEMPLATE_PASSARGS_8(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end, begin v8 end
#define CPP98VARIADICTEMPLATE_PASSARGS_9(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end, begin v8 end, begin v9 end
#define CPP98VARIADICTEMPLATE_PASSARGS_10(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end, begin v8 end, begin v9 end, begin v10 end
#define CPP98VARIADICTEMPLATE_PASSARGS_11(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end, begin v8 end, begin v9 end, begin v10 end, begin v11 end
#define CPP98VARIADICTEMPLATE_PASSARGS_12(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end, begin v8 end, begin v9 end, begin v10 end, begin v11 end, begin v12 end
#define CPP98VARIADICTEMPLATE_PASSARGS_13(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end, begin v8 end, begin v9 end, begin v10 end, begin v11 end, begin v12 end, begin v13 end
#define CPP98VARIADICTEMPLATE_PASSARGS_14(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end, begin v8 end, begin v9 end, begin v10 end, begin v11 end, begin v12 end, begin v13 end, begin v14 end
#define CPP98VARIADICTEMPLATE_PASSARGS_15(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end, begin v8 end, begin v9 end, begin v10 end, begin v11 end, begin v12 end, begin v13 end, begin v14 end, begin v15 end
#define CPP98VARIADICTEMPLATE_PASSARGS_16(begin,end,...) __VA_ARGS__ begin v1 end, begin v2 end, begin v3 end, begin v4 end, begin v5 end, begin v6 end, begin v7 end, begin v8 end, begin v9 end, begin v10 end, begin v11 end, begin v12 end, begin v13 end, begin v14 end, begin v15 end, begin v16 end

#define CPP98VARIADICTEMPLATE_FOREACH_ARGNUM(m) \
    m(0) m(1) m(2) m(3) m(4) m(5) m(6) m(7) m(8) m(9) m(10) m(11) m(12) m(13) m(14) m(15) m(16)
//[[[end]]]

// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// This file may be used under the terms and conditions of the License
// Agreement supplied with the software.
//
// This file is provided "AS IS" WITH NO WARRANTY OF ANY KIND, EITHER EXPRESSED
// OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE WARRANTY OF DESIGN,
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// ****************************************************************************


#ifndef _Base_EnvironmentChecker_HeaderFile
#define _Base_EnvironmentChecker_HeaderFile

#include <cadex/Base_Macro.hxx>

namespace cadex {

class Base_EnvironmentChecker
{
public:

    //! Checks consistency of build environment.
    __CADEX_EXPORT static bool CheckEnvironment (
        FILE* theErrorStream = 0,
#if _WIN32
#if _MSC_VER
#if _MSC_VER < 1500
        const char* theCompiler = "Microsoft Visual C++ 2005",
#elif _MSC_VER == 1500
        const char* theCompiler = "Microsoft Visual C++ 2008",
#elif _MSC_VER == 1600
        const char* theCompiler = "Microsoft Visual C++ 2010",
#elif _MSC_VER == 1700
        const char* theCompiler = "Microsoft Visual C++ 2012",
#elif _MSC_VER == 1800
        const char* theCompiler = "Microsoft Visual C++ 2013",
#elif _MSC_VER == 1900
        const char* theCompiler = "Microsoft Visual C++ 2015",
#elif _MSC_VER > 1900 && _MSC_VER < 1920
        const char* theCompiler = "Microsoft Visual C++ 2017",
#else
#error Unsupported version of Microsoft Visual C++ detected
#endif
        const int theCompilerVersion = _MSC_FULL_VER,
#else /* _MSC_VER */
#error Unsupported compiler detected
#endif
#elif __clang__
         const char* theCompiler = "LLVM Clang compiler",
         const int theCompilerVersion =
            (__clang_major__ * 10000) + (__clang_minor__ * 100) + (__clang_patchlevel__),
#elif __GNUC__
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8))
        const char* theCompiler = "GNU C++ compiler",
        const int theCompilerVersion =
            (__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + (__GNUC_PATCHLEVEL__),
#else /* __GNUC__ */
#error Unsupported version of GNU compiler detected
#endif
#else
#error Unsupported compiler detected
#endif

#if _DEBUG
        const char* theMode = "Debug"
#else
        const char* theMode = "Release"
#endif
        );
};

}

#endif

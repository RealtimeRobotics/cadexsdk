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


#ifndef _Base_LoggerFileAppender_HeaderFile
#define _Base_LoggerFileAppender_HeaderFile

#include <cadex/Base_LoggerAppender.hxx>

namespace cadex {

class Base_LoggerFileAppender : public Base_LoggerAppender
{
public:
    //! Constructor.
    __CADEX_EXPORT Base_LoggerFileAppender (const char* theFileName);

#if _WIN32
    //! Constructor.
    __CADEX_EXPORT Base_LoggerFileAppender (const wchar_t* theFileName);
#endif

    //! Returns true if the output file is in a valid state.
    /*! Returns false if the file could not be opened or some other error occured.*/
    __CADEX_EXPORT bool IsValid() const;

    //! Outputs a message into the file.
    __CADEX_EXPORT virtual void Append (CharPointerType theMessage);

};

}

#endif

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


#ifndef _OBJ_WriterParameters_HeaderFile
#define _OBJ_WriterParameters_HeaderFile

#include <cadex/Base_WriterParameters.hxx>

namespace cadex {

class OBJ_WriterParameters : public Base_WriterParameters
{
public:

    __CADEX_EXPORT OBJ_WriterParameters();

    __CADEX_EXPORT bool  ToGenerateMtlFile() const;
    __CADEX_EXPORT bool& ToGenerateMtlFile();

    __CADEX_EXPORT bool  WriteNormals() const;
    __CADEX_EXPORT bool& WriteNormals();

    __CADEX_EXPORT bool  OverrideDuplicateNames() const;
    __CADEX_EXPORT bool& OverrideDuplicateNames();

    __CADEX_EXPORT bool  ReplaceSpacesInNames() const;
    __CADEX_EXPORT bool& ReplaceSpacesInNames();
};

}

#endif

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


#ifndef _JT_FileModelTools_HeaderFile
#define _JT_FileModelTools_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_FILE_MODEL_TOOLS

#include <cadex/ModelData_Model.hxx>

namespace cadex {

namespace internal {
class JT_FileModelToolsImpl;
}

class JT_FileModelTools
{
public:

    JT_FileModelTools (const std::shared_ptr <internal::JT_FileModelToolsImpl>& theImpl);

    __CADEX_EXPORT ModelData_Model SavePerPart (const Base_UTF16String& theSaveDir);

private:

    std::shared_ptr <internal::JT_FileModelToolsImpl> myImpl;
};

}

#endif // __CADEX_PREVIEW_FILE_MODEL_TOOLS
#endif

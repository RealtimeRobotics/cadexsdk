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


#ifndef _ModelPrs_Exploder_HeaderFile
#define _ModelPrs_Exploder_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>

namespace cadex {
class ModelPrs_SceneNode;

namespace internal {
class ModelPrs_ExploderImpl;
}

class ModelPrs_Exploder : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_ExploderImpl    ImplType;

    __CADEX_EXPORT ModelPrs_Exploder();

    __CADEX_EXPORT void SetValue (double theValue);
    __CADEX_EXPORT double Value() const;
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_Exploder_HeaderFile

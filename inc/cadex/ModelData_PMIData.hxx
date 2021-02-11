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


#ifndef _ModelData_PMIData_HeaderFile
#define _ModelData_PMIData_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/ModelData_BaseObject.hxx>
#include <cadex/ModelData_PMIType.hxx>


namespace cadex {
class ModelData_PMIGraphicalElement;
class ModelData_PMISemanticElement;
class ModelData_PropertyTable;

namespace internal {
class ModelData_PMIDataImpl;
}

class ModelData_PMIData : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_PMIDataImpl  ImplType;

    __CADEX_EXPORT ModelData_PMIData();
    __CADEX_EXPORT explicit ModelData_PMIData (initialized);
    __CADEX_EXPORT explicit ModelData_PMIData (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIData (const ModelData_PMIGraphicalElement& theElement);
    __CADEX_EXPORT explicit ModelData_PMIData (ModelData_PMIType theType);
    __CADEX_EXPORT ModelData_PMIData (ModelData_PMIType theType, const Base_UTF16String& theName);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetGraphicalElement (const ModelData_PMIGraphicalElement& theElement);
    __CADEX_EXPORT ModelData_PMIGraphicalElement GraphicalElement() const;

    __CADEX_EXPORT void SetSemanticElement (const ModelData_PMISemanticElement& theElement);
    __CADEX_EXPORT ModelData_PMISemanticElement SemanticElement() const;

    __CADEX_EXPORT void AddProperties (const ModelData_PropertyTable& theProperties);
    __CADEX_EXPORT ModelData_PropertyTable Properties() const;

    __CADEX_EXPORT void SetType (ModelData_PMIType theType);
    __CADEX_EXPORT ModelData_PMIType Type() const;

    __CADEX_EXPORT bool IsEmpty() const;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

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


#ifndef _ModelData_PMISemanticElement_HeaderFile
#define _ModelData_PMISemanticElement_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/ModelData_BaseObject.hxx>


namespace cadex {
class ModelData_PMISemanticElementComponent;
class ModelData_PMISemanticElementComponentVisitor;

namespace internal {
class ModelData_PMISemanticElementImpl;
}

class ModelData_PMISemanticElement : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_PMISemanticElementImpl  ImplType;

    __CADEX_EXPORT ModelData_PMISemanticElement();
    __CADEX_EXPORT explicit ModelData_PMISemanticElement (initialized);
    __CADEX_EXPORT explicit ModelData_PMISemanticElement (ImplType* theImpl);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void AddComponent (const ModelData_PMISemanticElementComponent& theComponent);
    __CADEX_EXPORT bool IsEmpty() const;
    __CADEX_EXPORT size_t NumberOfComponents() const;

    __CADEX_EXPORT void Accept (ModelData_PMISemanticElementComponentVisitor& theVisitor) const;

    class ComponentIterator
    {
    public:
        __CADEX_EXPORT ComponentIterator (const ModelData_PMISemanticElement& theElement);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_PMISemanticElementComponent& Next() const;
        __CADEX_EXPORT ModelData_PMISemanticElementComponent& Next();
    protected:
        internal::Base_Handle myImpl;
    };
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

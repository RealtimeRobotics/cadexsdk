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


#ifndef _ModelData_PMISavedView_HeaderFile
#define _ModelData_PMISavedView_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/ModelData_BaseObject.hxx>


namespace cadex {
class ModelData_PMICamera;
class ModelData_PMIGraphicalElement;

namespace internal {
class ModelData_PMISavedViewImpl;
}

class ModelData_PMISavedView : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_PMISavedViewImpl ImplType;

    __CADEX_EXPORT ModelData_PMISavedView();
    __CADEX_EXPORT explicit ModelData_PMISavedView (initialized);
    __CADEX_EXPORT explicit ModelData_PMISavedView (const ModelData_PMICamera& theCamera);
    __CADEX_EXPORT ModelData_PMISavedView (const ModelData_PMICamera& theCamera, const Base_UTF16String& theName);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetCamera (const ModelData_PMICamera& theCamera);
    __CADEX_EXPORT ModelData_PMICamera Camera() const;

    __CADEX_EXPORT void AddGraphicalElement (const ModelData_PMIGraphicalElement& theElement);
    __CADEX_EXPORT size_t NumberOfGraphicalElements() const;

    class GraphicalElementIterator
    {
    public:
        __CADEX_EXPORT GraphicalElementIterator (const ModelData_PMISavedView& theView);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_PMIGraphicalElement& Next() const;
        __CADEX_EXPORT ModelData_PMIGraphicalElement& Next();
    protected:
        internal::Base_Handle myImpl;
    };
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

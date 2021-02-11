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


#ifndef _ModelData_PMITable_HeaderFile
#define _ModelData_PMITable_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/ModelData_BaseObject.hxx>
#include <memory>


namespace cadex {
class ModelData_PMIData;
class ModelData_PMIPlane;
class ModelData_PMISavedView;

namespace internal {
class ModelData_PMITableImpl;
}

class ModelData_PMITable : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_PMITableImpl ImplType;

    __CADEX_EXPORT ModelData_PMITable();
    __CADEX_EXPORT explicit ModelData_PMITable (initialized);
    __CADEX_EXPORT explicit ModelData_PMITable (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMITable (const Base_UTF16String& theName);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void Add (const ModelData_PMIData& theData);
    __CADEX_EXPORT void Add (const ModelData_PMITable& theTable);

    __CADEX_EXPORT void AddView (const ModelData_PMISavedView& theView);

    __CADEX_EXPORT void AddPlane (const ModelData_PMIPlane& thePlane);

    class Provider
    {
    public:
        __CADEX_DEFINE_MEMORY_MANAGEMENT

        __CADEX_EXPORT virtual ~Provider();

        //! Feeds the PMI table.
        /*! Subclasses must redefine this method to call Add() of \a theTable.*/
        virtual void Feed (ModelData_PMITable& theTable) = 0;
    };

    __CADEX_EXPORT void AddProvider (const std::shared_ptr<Provider>& theProvider);

    __CADEX_EXPORT bool IsEmpty() const;
    __CADEX_EXPORT size_t NumberOfPMIData() const;
    __CADEX_EXPORT size_t NumberOfSavedViews() const;
    __CADEX_EXPORT size_t NumberOfPlanes() const;

    __CADEX_EXPORT void Clear();

    class PMIDataIterator
    {
    public:
        __CADEX_EXPORT PMIDataIterator (const ModelData_PMITable& theTable);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_PMIData& Next() const;
        __CADEX_EXPORT ModelData_PMIData& Next();
    protected:
        internal::Base_Handle myImpl;
    };

    class SavedViewIterator
    {
    public:
        __CADEX_EXPORT SavedViewIterator (const ModelData_PMITable& theTable);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_PMISavedView& Next() const;
        __CADEX_EXPORT ModelData_PMISavedView& Next();
    protected:
        internal::Base_Handle myImpl;
    };

    class PlaneIterator
    {
    public:
        __CADEX_EXPORT PlaneIterator (const ModelData_PMITable& theTable);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_PMIPlane& Next() const;
        __CADEX_EXPORT ModelData_PMIPlane& Next();
    protected:
        internal::Base_Handle myImpl;
    };
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

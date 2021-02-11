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


#ifndef _ModelData_BRepRepresentation_HeaderFile
#define _ModelData_BRepRepresentation_HeaderFile

#include <cadex/ModelData_Representation.hxx>

class TopoDS_Shape;

namespace cadex {

class ModelData_Appearance;
class ModelData_BodyList;
class ModelData_Layer;
class ModelData_PMIData;
class ModelData_Shape;

namespace internal {
class ModelData_BRepRepresentationImpl;
}

class ModelData_BRepRepresentation : public ModelData_Representation
{
public:

    typedef cadex::internal::ModelData_BRepRepresentationImpl  ImplType;

    __CADEX_EXPORT ModelData_BRepRepresentation();
    __CADEX_EXPORT ModelData_BRepRepresentation (initialized);
    __CADEX_EXPORT ModelData_BRepRepresentation (ImplType* theImpl);

    __CADEX_EXPORT ModelData_BRepRepresentation (const ModelData_Shape& theShape);
    __CADEX_EXPORT ModelData_BRepRepresentation (const TopoDS_Shape& theShape);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT ModelData_Shape Add (const ModelData_Shape& theShape);
    __CADEX_EXPORT ModelData_Shape Add (const TopoDS_Shape& theShape);

    __CADEX_EXPORT const ModelData_BodyList& Get() const;

    class Provider
    {
    public:
        __CADEX_DEFINE_MEMORY_MANAGEMENT

        __CADEX_EXPORT virtual ~Provider();

        //! Feeds the representation.
        /*! Subclasses must redefine this method to call \ref ModelData_BRepRepresentation::Add() "Add()"
            of \a theRepresentation.

            Redefined method Feed() may not call the ModelData_BRepRepresentation::Get() method
            of \a theRepresentation, otherwise this will cause a stack overflow (due to cyclic
            calls).
        */
        virtual void Feed (ModelData_BRepRepresentation& theRepresentation) const = 0;
    };

    //! Adds a B-Rep model provider.
    __CADEX_EXPORT void AddProvider (const std::shared_ptr<Provider>& theProvider);

    //! Discards associated data.
    __CADEX_EXPORT void Clear();


    //subhapes

    __CADEX_EXPORT bool HasSubshapes() const;
    __CADEX_EXPORT size_t NumberOfSubshapes() const;

    __CADEX_EXPORT void SetName (const ModelData_Shape& theSubshape, const Base_UTF16String& theName);
    __CADEX_EXPORT void SetName (const TopoDS_Shape& theSubshape, const Base_UTF16String& theName);

    __CADEX_EXPORT void SetAppearance (const ModelData_Shape& theSubshape, const ModelData_Appearance& theAppearance);
    __CADEX_EXPORT void SetAppearance (const TopoDS_Shape& theSubshape, const ModelData_Appearance& theAppearance);

    __CADEX_EXPORT void SetPropertyTable (const ModelData_Shape& theSubshape, const ModelData_PropertyTable& thePTable);
    __CADEX_EXPORT void SetPropertyTable (const TopoDS_Shape& theSubshape, const ModelData_PropertyTable& thePTable);

#if __CADEX_PREVIEW_PMI
    __CADEX_EXPORT void AddPMIData (const ModelData_Shape& theSubshape, const ModelData_PMIData& thePMIData);
    __CADEX_EXPORT void AddPMIData (const TopoDS_Shape& theSubshape, const ModelData_PMIData& thePMIData);
#endif

    __CADEX_EXPORT Base_UTF16String Name (const ModelData_Shape& theSubshape) const;
    __CADEX_EXPORT Base_UTF16String Name (const TopoDS_Shape& theSubshape) const;

    __CADEX_EXPORT ModelData_Appearance Appearance (const ModelData_Shape& theSubshape) const;
    __CADEX_EXPORT ModelData_Appearance Appearance (const TopoDS_Shape& theSubshape) const;

    __CADEX_EXPORT ModelData_PropertyTable PropertyTable (const ModelData_Shape& theSubshape) const;
    __CADEX_EXPORT ModelData_PropertyTable PropertyTable (const TopoDS_Shape& theSubshape) const;

    // Layers management

    __CADEX_EXPORT void AddToLayer (const ModelData_Shape& theSubshape, const ModelData_Layer& theLayer);
    __CADEX_EXPORT void AddToLayer (const TopoDS_Shape& theSubshape, const ModelData_Layer& theLayer);

    __CADEX_EXPORT bool RemoveFromLayer (const ModelData_Shape& theSubshape, const ModelData_Layer& theLayer);
    __CADEX_EXPORT bool RemoveFromLayer (const TopoDS_Shape& theSubshape, const ModelData_Layer& theLayer);

    __CADEX_EXPORT bool FindInLayer (const ModelData_Shape& theSubshape, const ModelData_Layer& theLayer) const;
    __CADEX_EXPORT bool FindInLayer (const TopoDS_Shape& theSubshape, const ModelData_Layer& theLayer) const;

    class LayerIterator
    {
    public:
        __CADEX_EXPORT LayerIterator (const ModelData_Shape& theSubshape, const ModelData_BRepRepresentation& theRep);
        __CADEX_EXPORT LayerIterator (const TopoDS_Shape& theSubshape, const ModelData_BRepRepresentation& theRep);

        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT ModelData_Layer Next();
    private:
        internal::Base_Handle myImpl;
    };

#if __CADEX_PREVIEW_PMI
    class PMIDataIterator
    {
    public:
        __CADEX_EXPORT PMIDataIterator (const ModelData_Shape& theSubshape, const ModelData_BRepRepresentation& theRep);
        __CADEX_EXPORT PMIDataIterator (const TopoDS_Shape& theSubshape, const ModelData_BRepRepresentation& theRep);

        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT ModelData_PMIData Next();
    private:
        internal::Base_Handle myImpl;
    };
#endif

    class SubshapeIterator
    {
    public:
        __CADEX_EXPORT SubshapeIterator (const ModelData_BRepRepresentation& theRep);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_Shape& Next();
    protected:
        internal::Base_Handle myImpl;
    };

    class SubshapeVisitor
    {
    public:

        //! Destructor.
        virtual ~SubshapeVisitor() {}

        //! Visits a subshape.
        virtual void operator() (const ModelData_Shape& theShape) = 0;
    };

    //! Applies the visitor to visit the subshapes.
    __CADEX_EXPORT void Accept (SubshapeVisitor& theVisitor) const;

    using ModelData_Representation::Accept;
    using ModelData_BaseObject::Name;
    using ModelData_BaseObject::SetName;

private:

    friend class internal::ModelData_BRepRepresentationImpl;
};

}

#endif

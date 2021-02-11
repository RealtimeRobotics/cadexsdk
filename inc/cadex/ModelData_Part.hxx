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


#ifndef _ModelData_Part_HeaderFile
#define _ModelData_Part_HeaderFile

#include <cadex/ModelData_RepresentationMask.hxx>
#include <cadex/ModelData_SceneGraphElement.hxx>

namespace cadex {
class ModelData_BRepRepresentation;
class ModelData_PolyRepresentation;
class ModelData_Representation;

namespace internal {
class ModelData_PartImpl;
}

class ModelData_Part : public ModelData_SceneGraphElement
{
public:

    typedef cadex::internal::ModelData_PartImpl    ImplType;

    __CADEX_EXPORT ModelData_Part();
    __CADEX_EXPORT explicit ModelData_Part (initialized);
    __CADEX_EXPORT explicit ModelData_Part (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_Part (const Base_UTF16String& theName);

    __CADEX_EXPORT explicit ModelData_Part (const ModelData_Representation& theRep,
        const Base_UTF16String& theName = Base_UTF16String());
    __CADEX_EXPORT ModelData_Part (const ModelData_BRepRepresentation& theRep,
        const ModelData_PolyRepresentation& theLOD,
        const Base_UTF16String& theName = Base_UTF16String());
    __CADEX_EXPORT ModelData_Part (const ModelData_BRepRepresentation& theRep,
        const ModelData_PolyRepresentation& theFineLOD,
        const ModelData_PolyRepresentation& theCoarseLOD,
        const Base_UTF16String& theName = Base_UTF16String());
    __CADEX_EXPORT ModelData_Part (const ModelData_BRepRepresentation& theRep,
        const ModelData_PolyRepresentation& theFineLOD,
        const ModelData_PolyRepresentation& theMediumLOD,
        const ModelData_PolyRepresentation& theCoarseLOD,
        const Base_UTF16String& theName = Base_UTF16String());

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void AddRepresentation (const ModelData_Representation& theRepresentation);

    __CADEX_EXPORT ModelData_BRepRepresentation BRepRepresentation() const;

    __CADEX_EXPORT ModelData_PolyRepresentation PolyRepresentation (
        ModelData_RepresentationMask theRepresentationMask) const;
#ifndef SWIG
    using ModelData_SceneGraphElement::Accept;
#endif

    /*! \class Visitor
    */
    class RepresentationVisitor
    {
    public:
        virtual ~RepresentationVisitor() {}
        virtual void operator() (const ModelData_BRepRepresentation& theRep) = 0;
        virtual void operator() (const ModelData_PolyRepresentation& theRep) = 0;
    };

    /*! \class VoidRepresentationVisitor
    */
    class VoidRepresentationVisitor : public RepresentationVisitor
    {
    public:
        virtual void operator() (const ModelData_BRepRepresentation& /*theRep*/) {}
        virtual void operator() (const ModelData_PolyRepresentation& /*theRep*/) {}
    };

    /*! \internal
        \class CombinedRepresentationVisitor
        \brief Provides combined method Visit() to visit all representations.

        All individual operator() methods call the method Visit() which accepts a base class
        object.

        This is a convenience class allowing to redefine a single method Visit() in the
        subclasses.
    */
    class CombinedRepresentationVisitor : public RepresentationVisitor
    {
    public:
        __CADEX_EXPORT virtual void operator() (const ModelData_BRepRepresentation& theRep);
        __CADEX_EXPORT virtual void operator() (const ModelData_PolyRepresentation& theRep);
        virtual void Visit (const ModelData_Representation& theRep) = 0;
    };

    //! Accepts a visitor of the associated representations.
    __CADEX_EXPORT void Accept (RepresentationVisitor& theVisitor) const;

    //! Accepts a visitor of the associated representations.
    __CADEX_EXPORT void Accept (RepresentationVisitor& theVisitor, int theRepresentationMask) const;

    class RepresentationIterator
    {
    public:
        __CADEX_EXPORT RepresentationIterator (const ModelData_Part& thePart);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_Representation& Next() const;
        __CADEX_EXPORT ModelData_Representation& Next();
    protected:
        internal::Base_Handle myImpl;
    };

private:
    friend class internal::ModelData_PartImpl;
};

}

#endif

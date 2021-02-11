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


#ifndef _ModelData_PMIGraphicalElementComponent_HeaderFile
#define _ModelData_PMIGraphicalElementComponent_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/Base_PublicObject.hxx>


namespace cadex {
class Base_UTF16String;
class ModelData_IndexedTriangleSet;
class ModelData_PMIGraphicalElementComponentVisitor;
class ModelData_PMIOutline;
class ModelData_Point2d;

namespace internal {
class ModelData_PMIGraphicalElementComponentImpl;
class ModelData_PMIOutlinedComponentImpl;
class ModelData_PMITextComponentImpl;
class ModelData_PMITriangulatedComponentImpl;
}

class ModelData_PMIGraphicalElementComponent : public Base_PublicObject
{
public:

    __CADEX_EXPORT void Accept (ModelData_PMIGraphicalElementComponentVisitor& theVisitor) const;

    //! Returns true if the object has a type \a T.
    /*! Helper method which uses static method T::CompareType().*/
    template <typename T>
    bool IsOfType() const
    { return T::CompareType (*this); }

protected:

    //! Constructor.
    /*! Creates a null object (see IsNull()).*/
    ModelData_PMIGraphicalElementComponent() {}

    explicit ModelData_PMIGraphicalElementComponent (internal::ModelData_PMIGraphicalElementComponentImpl* theImpl);
};

class ModelData_PMIOutlinedComponent : public ModelData_PMIGraphicalElementComponent
{
public:

    typedef cadex::internal::ModelData_PMIOutlinedComponentImpl ImplType;

    __CADEX_EXPORT ModelData_PMIOutlinedComponent();
    __CADEX_EXPORT explicit ModelData_PMIOutlinedComponent (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIOutlinedComponent (const ModelData_PMIOutline& theOutline);

    __CADEX_EXPORT static bool CompareType (const ModelData_PMIGraphicalElementComponent& theComponent);

    __CADEX_EXPORT void SetOutline (const ModelData_PMIOutline& theOutline);
    __CADEX_EXPORT ModelData_PMIOutline Outline() const;
};

class ModelData_PMITextComponent : public ModelData_PMIGraphicalElementComponent
{
public:

    typedef cadex::internal::ModelData_PMITextComponentImpl     ImplType;

    __CADEX_EXPORT ModelData_PMITextComponent();
    __CADEX_EXPORT explicit ModelData_PMITextComponent (ImplType* theImpl);

    __CADEX_EXPORT static bool CompareType (const ModelData_PMIGraphicalElementComponent& theComponent);

    __CADEX_EXPORT void SetText (const Base_UTF16String& theText);
    __CADEX_EXPORT Base_UTF16String Text() const;

    __CADEX_EXPORT void SetTextOrigin (const ModelData_Point2d& theTextOrigin);
    __CADEX_EXPORT ModelData_Point2d TextOrigin() const;

    __CADEX_EXPORT void SetFontSize (float theFontSize);
    __CADEX_EXPORT float FontSize() const;

    __CADEX_EXPORT void SetOutline (const ModelData_PMIOutline& theOutline);
    __CADEX_EXPORT ModelData_PMIOutline Outline() const;
};

class ModelData_PMITriangulatedComponent : public ModelData_PMIGraphicalElementComponent
{
public:

    typedef cadex::internal::ModelData_PMITriangulatedComponentImpl ImplType;

    __CADEX_EXPORT ModelData_PMITriangulatedComponent();
    __CADEX_EXPORT explicit ModelData_PMITriangulatedComponent (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMITriangulatedComponent (const ModelData_IndexedTriangleSet& theTriangleSet);

    __CADEX_EXPORT static bool CompareType (const ModelData_PMIGraphicalElementComponent& theComponent);

    __CADEX_EXPORT void SetTriangleSet (const ModelData_IndexedTriangleSet& theTriangleSet);
    __CADEX_EXPORT ModelData_IndexedTriangleSet TriangleSet() const;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

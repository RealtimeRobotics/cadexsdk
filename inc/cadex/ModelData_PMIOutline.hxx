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


#ifndef _ModelData_PMIOutline_HeaderFile
#define _ModelData_PMIOutline_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/Base_PublicObject.hxx>


namespace cadex {
class ModelData_Curve;
class ModelData_Curve2d;
class ModelData_PMIOutlineVisitor;
class ModelData_PolyLineSet;
class ModelData_PolyLine2dSet;

namespace internal {
class ModelData_PMICompositeOutlineImpl;
class ModelData_PMICurveOutlineImpl;
class ModelData_PMICurve2dOutlineImpl;
class ModelData_PMIPolyOutlineImpl;
class ModelData_PMIPoly2dOutlineImpl;
class ModelData_PMIOutlineImpl;
}

class ModelData_PMIOutline : public Base_PublicObject
{
public:

    //! Constructor.
    /*! Creates a null object (see IsNull()).*/
    ModelData_PMIOutline() {}

    __CADEX_EXPORT void Accept (ModelData_PMIOutlineVisitor& theVisitor) const;

    //! Returns true if the object has a type \a T.
    /*! Helper method which uses static method T::CompareType().*/
    template <typename T>
    bool IsOfType() const
    { return T::CompareType (*this); }

protected:
    explicit ModelData_PMIOutline (internal::ModelData_PMIOutlineImpl* theImpl);
};

class ModelData_PMIPolyOutline : public ModelData_PMIOutline
{
public:

    typedef cadex::internal::ModelData_PMIPolyOutlineImpl   ImplType;

    __CADEX_EXPORT ModelData_PMIPolyOutline();
    __CADEX_EXPORT explicit ModelData_PMIPolyOutline (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIPolyOutline (const ModelData_PolyLineSet& theLineSet);

    __CADEX_EXPORT static bool CompareType (const ModelData_PMIOutline& theOutline);

    __CADEX_EXPORT void SetLineSet (const ModelData_PolyLineSet& theLineSet);
    __CADEX_EXPORT ModelData_PolyLineSet LineSet() const;
};

class ModelData_PMIPoly2dOutline : public ModelData_PMIOutline
{
public:

    typedef cadex::internal::ModelData_PMIPoly2dOutlineImpl ImplType;

    __CADEX_EXPORT ModelData_PMIPoly2dOutline();
    __CADEX_EXPORT explicit ModelData_PMIPoly2dOutline (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIPoly2dOutline (const ModelData_PolyLine2dSet& theLineSet);

    __CADEX_EXPORT static bool CompareType (const ModelData_PMIOutline& theOutline);

    __CADEX_EXPORT void SetLineSet (const ModelData_PolyLine2dSet& theLineSet);
    __CADEX_EXPORT ModelData_PolyLine2dSet LineSet() const;
};

class ModelData_PMICurveOutline : public ModelData_PMIOutline
{
public:

    typedef cadex::internal::ModelData_PMICurveOutlineImpl      ImplType;

    __CADEX_EXPORT ModelData_PMICurveOutline();
    __CADEX_EXPORT explicit ModelData_PMICurveOutline (ImplType* theImpl);
    __CADEX_EXPORT static bool CompareType (const ModelData_PMIOutline& theOutline);

    __CADEX_EXPORT void Append (const ModelData_Curve& theCurve);
    __CADEX_EXPORT bool IsEmpty() const;
    __CADEX_EXPORT size_t NumberOfCurves() const;
    __CADEX_EXPORT const ModelData_Curve& Curve (size_t theIndex) const;
};

class ModelData_PMICurve2dOutline : public ModelData_PMIOutline
{
public:

    typedef cadex::internal::ModelData_PMICurve2dOutlineImpl    ImplType;

    __CADEX_EXPORT ModelData_PMICurve2dOutline();
    __CADEX_EXPORT explicit ModelData_PMICurve2dOutline (ImplType* theImpl);
    __CADEX_EXPORT static bool CompareType (const ModelData_PMIOutline& theOutline);

    __CADEX_EXPORT void Append (const ModelData_Curve2d& theCurve);
    __CADEX_EXPORT bool IsEmpty() const;
    __CADEX_EXPORT size_t NumberOfCurves() const;
    __CADEX_EXPORT const ModelData_Curve2d& Curve (size_t theIndex) const;
};

class ModelData_PMICompositeOutline : public ModelData_PMIOutline
{
public:

    typedef cadex::internal::ModelData_PMICompositeOutlineImpl  ImplType;

    __CADEX_EXPORT ModelData_PMICompositeOutline();
    __CADEX_EXPORT explicit ModelData_PMICompositeOutline (ImplType* theImpl);
    __CADEX_EXPORT static bool CompareType (const ModelData_PMIOutline& theOutline);

    __CADEX_EXPORT void Append (const ModelData_PMIOutline& theOutline);
    __CADEX_EXPORT bool IsEmpty() const;
    __CADEX_EXPORT size_t NumberOfOutlines() const;
    __CADEX_EXPORT const ModelData_PMIOutline& Outline (size_t theIndex) const;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

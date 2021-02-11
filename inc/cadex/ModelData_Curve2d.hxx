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


#ifndef _ModelData_Curve2d_HeaderFile
#define _ModelData_Curve2d_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/ModelData_Continuity.hxx>
#include <cadex/ModelData_CurveType.hxx>

__CADEX_DEFINE_HANDLE_TYPE_FWD_PUBLIC
__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom2d_Curve)

namespace cadex {

class ModelData_Direction2d;
class ModelData_Point2d;
class ModelData_Transformation2d;
class ModelData_Vector2d;

namespace internal {
class ModelData_Curve2dImpl;
class ModelData_Factory;
}

class ModelData_Curve2d
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelData_Curve2d ();
    __CADEX_EXPORT ModelData_Curve2d (const ModelData_Curve2d& theOther);
    __CADEX_EXPORT ModelData_Curve2d (ModelData_Curve2d&& theOther);

    __CADEX_EXPORT ~ModelData_Curve2d();

    __CADEX_EXPORT ModelData_Curve2d& operator= (const ModelData_Curve2d& theOther);
    __CADEX_EXPORT ModelData_Curve2d& operator= (ModelData_Curve2d&& theOther);

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom2d_Curve)

    __CADEX_EXPORT ModelData_CurveType Type() const;

    __CADEX_EXPORT bool IsNull() const;
    __CADEX_EXPORT void Nullify();

    //! Returns if the object has been initialized.
    /*! Returns the value opposite to IsNull().*/
    operator bool() const
    {
        return !IsNull();
    }

    __CADEX_EXPORT bool IsPeriodic() const;

    __CADEX_EXPORT double UMin() const;
    __CADEX_EXPORT double UMax() const;
    __CADEX_EXPORT void Domain (double& theUMin, double& theUMax) const;
    __CADEX_EXPORT ModelData_Point2d Value (double theParameter) const;

    __CADEX_EXPORT ModelData_Curve2d Reversed() const;

    __CADEX_EXPORT void Transform (const ModelData_Transformation2d& theTransformation);

    __CADEX_EXPORT ModelData_Curve2d Transformed (const ModelData_Transformation2d& theTransformation) const;

    __CADEX_EXPORT ModelData_Continuity Continuity() const;

    __CADEX_EXPORT void D0 (double theParameter, ModelData_Point2d& theValue) const;
    __CADEX_EXPORT void D1 (double theParameter, ModelData_Point2d& theValue, ModelData_Vector2d& theD1) const;
    __CADEX_EXPORT void D2 (double theParameter,
        ModelData_Point2d& theValue,
        ModelData_Vector2d& theD1,
        ModelData_Vector2d& theD2) const;

    __CADEX_EXPORT bool DN (double theParameter,
        size_t theDerivativeOrder,
        ModelData_Point2d& theValue,
        ModelData_Vector2d theD[]) const;

    __CADEX_EXPORT double Curvature (double theParameter) const;

    __CADEX_EXPORT void Normal (double theParameter, ModelData_Direction2d& theNormal) const;

#if !defined(__CADEX_DOXYGEN)
    __CADEX_EXPORT const internal::ModelData_Curve2dImpl& Impl () const;
    __CADEX_EXPORT       internal::ModelData_Curve2dImpl& Impl ();
    __CADEX_EXPORT internal::ModelData_Curve2dImpl* operator->() const;
    internal::ModelData_Curve2dImpl* get() const { return operator->(); }

    template<typename T>
    T* Impl() const { return static_cast<T*> (operator->()); }
#endif

protected:

#if !defined(__CADEX_DOXYGEN)
    ModelData_Curve2d (internal::ModelData_Curve2dImpl* theImpl);
    friend class internal::ModelData_Factory;

    __CADEX_DEFINE_ALIGNED_MEMBER (sizeof (void*) * 3, void*)
#endif

private:
#if !defined(__CADEX_DOXYGEN)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE2(ModelData_Curve2d,Geom2d_Curve,ModelData_CurveType)
#endif
};

class ModelData_Curve2dHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Curve2d& theCurve) const;
};

__CADEX_EXPORT bool operator== (const ModelData_Curve2d& theCurve1, const ModelData_Curve2d& theCurve2);

inline bool operator!= (const ModelData_Curve2d& theCurve1, const ModelData_Curve2d& theCurve2)
{
    return !(theCurve1 == theCurve2);
}

}

#endif

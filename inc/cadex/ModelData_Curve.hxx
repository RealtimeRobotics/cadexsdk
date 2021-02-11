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


#ifndef _ModelData_Curve_HeaderFile
#define _ModelData_Curve_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/ModelData_Continuity.hxx>
#include <cadex/ModelData_CurveType.hxx>

__CADEX_DEFINE_HANDLE_TYPE_FWD_PUBLIC
__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_Curve)

namespace cadex {

class ModelData_Axis1Placement;
class ModelData_Axis2Placement;
class ModelData_Direction;
class ModelData_Point;
class ModelData_Transformation;
class ModelData_Vector;

namespace internal {
class ModelData_CurveImpl;
class ModelData_Factory;
}

class ModelData_Curve
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelData_Curve ();
    __CADEX_EXPORT ModelData_Curve (const ModelData_Curve& theOther);
    __CADEX_EXPORT ModelData_Curve (ModelData_Curve&& theOther);

    __CADEX_EXPORT ~ModelData_Curve();

    __CADEX_EXPORT ModelData_Curve& operator= (const ModelData_Curve& theOther);
    __CADEX_EXPORT ModelData_Curve& operator= (ModelData_Curve&& theOther);

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_Curve)

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
    __CADEX_EXPORT ModelData_Point Value (double theParameter) const;

    __CADEX_EXPORT ModelData_Curve Reversed() const;

    __CADEX_EXPORT void Transform (const ModelData_Transformation& theTransformation);

    __CADEX_EXPORT ModelData_Curve Transformed (const ModelData_Transformation& theTransformation) const;

    __CADEX_EXPORT ModelData_Continuity Continuity() const;

    __CADEX_EXPORT void D0 (double theParameter, ModelData_Point& theValue) const;
    __CADEX_EXPORT void D1 (double theParameter, ModelData_Point& theValue, ModelData_Vector& theD1) const;
    __CADEX_EXPORT void D2 (double theParameter,
        ModelData_Point& theValue,
        ModelData_Vector& theD1,
        ModelData_Vector& theD2) const;

    __CADEX_EXPORT bool DN (double theParameter,
        size_t theDerivativeOrder,
        ModelData_Point& theValue,
        ModelData_Vector theD[]) const;

    __CADEX_EXPORT double Curvature (double theParameter) const;

    __CADEX_EXPORT void Normal (double theParameter, ModelData_Direction& theNormal) const;


    __CADEX_EXPORT void Mirror (const ModelData_Point& thePoint);

    __CADEX_EXPORT void Mirror (const ModelData_Axis1Placement& theAxis);

    __CADEX_EXPORT void Mirror (const ModelData_Axis2Placement& theAxis);

    __CADEX_EXPORT ModelData_Curve Mirrored (const ModelData_Point& theRef) const;

    __CADEX_EXPORT ModelData_Curve Mirrored (const ModelData_Axis1Placement& theAxis) const;

    __CADEX_EXPORT ModelData_Curve Mirrored (const ModelData_Axis2Placement& theAxis) const;


    __CADEX_EXPORT void Rotate (const ModelData_Axis1Placement& theAxis, double theAngle);

    __CADEX_EXPORT ModelData_Curve Rotated (const ModelData_Axis1Placement& theAxis, double theAngle) const;

    __CADEX_EXPORT void Translate (const ModelData_Vector& theVector);

    __CADEX_EXPORT ModelData_Curve Translated (const ModelData_Vector& theVector) const;

    __CADEX_EXPORT void Scale (const ModelData_Point& thePoint, double theScale);

    __CADEX_EXPORT ModelData_Curve Scaled (const ModelData_Point& thePoint, double theScale) const;

#if !defined(__CADEX_DOXYGEN)
    __CADEX_EXPORT const internal::ModelData_CurveImpl& Impl() const;
    __CADEX_EXPORT internal::ModelData_CurveImpl& Impl ();

    __CADEX_EXPORT internal::ModelData_CurveImpl* operator->() const;
    internal::ModelData_CurveImpl* get() const { return operator->(); }

    template<typename T>
    T* Impl() const { return static_cast<T*> (operator->()); }
#endif

protected:

#if !defined(__CADEX_DOXYGEN)
    ModelData_Curve (internal::ModelData_CurveImpl* theImpl);
    friend class internal::ModelData_Factory;

    __CADEX_DEFINE_ALIGNED_MEMBER (sizeof (void*) * 3, void*)
#endif

private:
#if !defined(__CADEX_DOXYGEN)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE2(ModelData_Curve,Geom_Curve,ModelData_CurveType)
#endif
};

class ModelData_CurveHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Curve& theCurve) const;
};

__CADEX_EXPORT bool operator== (const ModelData_Curve& theCurve1, const ModelData_Curve& theCurve2);

inline bool operator!= (const ModelData_Curve& theCurve1, const ModelData_Curve& theCurve2)
{
    return !(theCurve1 == theCurve2);
}

}

#endif

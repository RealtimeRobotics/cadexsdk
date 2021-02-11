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


#ifndef _ModelData_Surface_HeaderFile
#define _ModelData_Surface_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/ModelData_Continuity.hxx>
#include <cadex/ModelData_SurfaceType.hxx>

__CADEX_DEFINE_HANDLE_TYPE_FWD_PUBLIC
__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_Surface)

namespace cadex {

class ModelData_Axis1Placement;
class ModelData_Axis2Placement;
class ModelData_Direction;
class ModelData_Point;
class ModelData_Transformation;
class ModelData_Vector;

namespace internal {
class ModelData_Factory;
class ModelData_SurfaceImpl;
}

class ModelData_Surface
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelData_Surface ();
    __CADEX_EXPORT ModelData_Surface (const ModelData_Surface& theOther);
    __CADEX_EXPORT ModelData_Surface (ModelData_Surface&& theOther);

    __CADEX_EXPORT ~ModelData_Surface();

    __CADEX_EXPORT ModelData_Surface& operator= (const ModelData_Surface& theOther);
    __CADEX_EXPORT ModelData_Surface& operator= (ModelData_Surface&& theOther);

    __CADEX_EXPORT ModelData_SurfaceType Type() const;

    __CADEX_EXPORT bool IsNull() const;
    __CADEX_EXPORT void Nullify();

    operator bool() const
    {
        return !IsNull();
    }

    __CADEX_EXPORT bool IsUPeriodic() const;
    __CADEX_EXPORT bool IsVPeriodic() const;

    __CADEX_EXPORT double UMin() const;
    __CADEX_EXPORT double UMax() const;
    __CADEX_EXPORT double VMin() const;
    __CADEX_EXPORT double VMax() const;
    __CADEX_EXPORT void Domain (double& theUMin, double& theUMax, double& theVMin, double& theVMax) const;

    __CADEX_EXPORT ModelData_Point Value (double theParameterU, double theParameterV) const;

    __CADEX_EXPORT void Transform (const ModelData_Transformation& theTransformation);

    __CADEX_EXPORT ModelData_Surface Transformed (const ModelData_Transformation& theTransformation) const;

    __CADEX_EXPORT ModelData_Continuity Continuity() const;

    __CADEX_EXPORT void D0 (double theParameterU, double theParameterV, ModelData_Point& theValue) const;

    __CADEX_EXPORT void D1 (double theParameterU,
        double theParameterV,
        ModelData_Point& theValue,
        ModelData_Vector& theD1U,
        ModelData_Vector& theD1V) const;

    __CADEX_EXPORT void D2 (double theParameterU,
        double theParameterV,
        ModelData_Point& theValue,
        ModelData_Vector& theD1U,
        ModelData_Vector& theD1V,
        ModelData_Vector& theD2U,
        ModelData_Vector& theD2V,
        ModelData_Vector& theD2UV) const;

    __CADEX_EXPORT bool DN (double theParameterU,
        double theParameterV,
        size_t theDerivativeOrder,
        ModelData_Point& theValue,
        ModelData_Vector theD[]) const;

    __CADEX_EXPORT void Curvature (double theParameterU,
        double theParameterV,
        ModelData_Vector& thePrincipalMaxDirection,
        ModelData_Vector& thePrincipalMinDirection) const;

    __CADEX_EXPORT void Curvature (double theParameterU,
        double theParameterV,
        ModelData_Direction& thePrincipalMaxDirection,
        ModelData_Direction& thePrincipalMinDirection,
        double& theMaxCurvature,
        double& theMinCurvature) const;

    __CADEX_EXPORT void Normal (double theParameterU, double theParameterV, ModelData_Direction& theNormal) const;


    __CADEX_EXPORT void Mirror (const ModelData_Point& thePoint);

    __CADEX_EXPORT void Mirror (const ModelData_Axis1Placement& theAxis);

    __CADEX_EXPORT void Mirror (const ModelData_Axis2Placement& theAxis);

    __CADEX_EXPORT ModelData_Surface Mirrored (const ModelData_Point& theRef) const;

    __CADEX_EXPORT ModelData_Surface Mirrored (const ModelData_Axis1Placement& theAxis) const;

    __CADEX_EXPORT ModelData_Surface Mirrored (const ModelData_Axis2Placement& theAxis) const;

    __CADEX_EXPORT void Rotate (const ModelData_Axis1Placement& theAxis, double theAngle);

    __CADEX_EXPORT ModelData_Surface Rotated (const ModelData_Axis1Placement& theAxis, double theAngle) const;

    __CADEX_EXPORT void Translate (const ModelData_Vector& theVector);

    __CADEX_EXPORT ModelData_Surface Translated (const ModelData_Vector& theVector) const;

    __CADEX_EXPORT void Scale (const ModelData_Point& thePoint, double theScale);

    __CADEX_EXPORT ModelData_Surface Scaled (const ModelData_Point& thePoint, double theScale) const;

    
#if !defined(__CADEX_DOXYGEN)
    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_Surface)

    __CADEX_EXPORT const internal::ModelData_SurfaceImpl& Impl() const;
    __CADEX_EXPORT internal::ModelData_SurfaceImpl& Impl();
    __CADEX_EXPORT internal::ModelData_SurfaceImpl* operator->() const;
    internal::ModelData_SurfaceImpl* get() const { return operator->(); }

    template<typename T>
    T* Impl() const { return static_cast<T*> (operator->()); }
#endif

protected:

#if !defined(__CADEX_DOXYGEN)
    ModelData_Surface (internal::ModelData_SurfaceImpl* theImpl);
    friend class internal::ModelData_Factory;

    __CADEX_DEFINE_ALIGNED_MEMBER (sizeof (void*) * 3, void*)
#endif

private:

#if !defined(__CADEX_DOXYGEN)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE2(ModelData_Surface,Geom_Surface,ModelData_SurfaceType)
#endif
};

class ModelData_SurfaceHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Surface& theSurface) const;
};

__CADEX_EXPORT bool operator== (const ModelData_Surface& theSurface1, const ModelData_Surface& theSurface2);

inline bool operator!= (const ModelData_Surface& theSurface1, const ModelData_Surface& theSurface2)
{
    return !(theSurface1 == theSurface2);
}

}

#endif

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


#ifndef _ModelData_Axis3Placement_HeaderFile
#define _ModelData_Axis3Placement_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>

class gp_Ax3;

namespace cadex {


class ModelData_Axis1Placement;
class ModelData_Axis2Placement;
class ModelData_Direction;
class ModelData_Point;
class ModelData_Transformation;
class ModelData_Vector;

class ModelData_Axis3Placement
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelData_Axis3Placement ();

    __CADEX_EXPORT ModelData_Axis3Placement (const ModelData_Point& theLocation,
        const ModelData_Direction& theAxis,
        const ModelData_Direction& theRefDirection);

    __CADEX_EXPORT ModelData_Axis3Placement (const ModelData_Axis2Placement& theOther);

    __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(ModelData_Axis3Placement, gp_Ax3)

    __CADEX_EXPORT const ModelData_Point& Location () const;
    __CADEX_EXPORT const ModelData_Direction& Axis() const;
    __CADEX_EXPORT const ModelData_Direction& XDirection() const;
    __CADEX_EXPORT const ModelData_Direction& YDirection() const;

    __CADEX_EXPORT bool IsRightHanded() const;


    //! Transforms the axis with a transformation matrix.
    __CADEX_EXPORT void Transform (const ModelData_Transformation& theTransformation);

    //! Returns an axis which is transformed with a transformation matrix.
    /*! \sa Transform().*/
    ModelData_Axis3Placement Transformed (const ModelData_Transformation& theTransformation) const
    {
        auto r = *this;
        r.Transform (theTransformation);
        return r;
    }

    __CADEX_EXPORT void Mirror (const ModelData_Point& theAxis);

    __CADEX_EXPORT void Mirror (const ModelData_Axis1Placement& theAxis);

    __CADEX_EXPORT void Mirror (const ModelData_Axis2Placement& theAxis);

    template <typename T>
    ModelData_Axis3Placement Mirrored (const T& theRef) const
    {
        auto r = *this;
        r.Mirror (theRef);
        return r;
    }

    __CADEX_EXPORT void Rotate (const ModelData_Axis1Placement& theAxis, double theAngle);

    ModelData_Axis3Placement Rotated (const ModelData_Axis1Placement& theAxis, double theAngle)
    {
        auto r = *this;
        r.Rotate (theAxis, theAngle);
        return r;
    }

    __CADEX_EXPORT void Translate (const ModelData_Vector& theVector);

    ModelData_Axis3Placement Translated (const ModelData_Vector& theVector)
    {
        auto r = *this;
        r.Translate (theVector);
        return r;
    }

protected:
    __CADEX_DEFINE_ALIGNED_MEMBER (sizeof (double) * 12, double)
};

}

#endif

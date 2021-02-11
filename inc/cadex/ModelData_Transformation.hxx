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


#ifndef _ModelData_Transformation_HeaderFile
#define _ModelData_Transformation_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelData_Vector.hxx>

class gp_Trsf;

namespace cadex {

class ModelData_Axis1Placement;
class ModelData_Axis3Placement;

class ModelData_Transformation
{
public:
    __CADEX_EXPORT ModelData_Transformation();
    __CADEX_EXPORT ModelData_Transformation (const ModelData_Transformation& theOther);

    __CADEX_EXPORT ModelData_Transformation (const ModelData_Vector& theTranslation);

    __CADEX_EXPORT ModelData_Transformation (const ModelData_Axis1Placement& theAxis,
        double theAngle,
        const ModelData_Vector& theTranslation = ModelData_Vector(),
        double theAngularPrecision = 1e-12);

    __CADEX_EXPORT ModelData_Transformation (const ModelData_Axis3Placement& theSource,
        const ModelData_Axis3Placement& theTarget);

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_Transformation, gp_Trsf)

    __CADEX_EXPORT bool IsIdentity() const;

    __CADEX_EXPORT void SetRotation (const ModelData_Axis1Placement& theAx1, double theAngle);

    __CADEX_EXPORT void Rotation (ModelData_XYZ& theXYZ, double& theAngle) const;

    __CADEX_EXPORT void SetRotationPart (
        double theV00, double theV01, double theV02,
        double theV10, double theV11, double theV12,
        double theV20, double theV21, double theV22);

    __CADEX_EXPORT void RotationPart (
        double& theV00, double& theV01, double& theV02,
        double& theV10, double& theV11, double& theV12,
        double& theV20, double& theV21, double& theV22) const;

    __CADEX_EXPORT void SetTranslation (const ModelData_Vector& theVec);
    __CADEX_EXPORT void SetTranslation (double theX, double theY, double theZ);
    __CADEX_EXPORT void SetTranslationPart (const ModelData_Vector& theVec);
    __CADEX_EXPORT void SetTranslationPart (double theX, double theY, double theZ);
    __CADEX_EXPORT void TranslationPart (double& theX, double& theY, double& theZ) const;
    __CADEX_EXPORT ModelData_Vector TranslationPart() const;

    __CADEX_EXPORT void SetScaleFactor (double theScale);
    __CADEX_EXPORT double ScaleFactor() const;

    __CADEX_EXPORT double Data (int i, int j) const;

    __CADEX_EXPORT void operator *= (const gp_Trsf& theOther);
    __CADEX_EXPORT ModelData_Transformation operator * (const gp_Trsf& theOther) const;

    __CADEX_EXPORT void Multiply (const ModelData_Transformation& theOther);

    ModelData_Transformation Multiplied (const ModelData_Transformation& theOther) const
    {
        auto r = *this;
        r.Multiply (theOther);
        return r;
    }

    void operator *= (const ModelData_Transformation& theOther)
    {
        Multiply (theOther);
    }

    ModelData_Transformation operator * (const ModelData_Transformation& theOther) const
    {
        return Multiplied (theOther);
    }

    __CADEX_EXPORT void Invert();

    //! Returns an inverse of \a this matrix.
    /*! \sa Invert().*/
    ModelData_Transformation Inverted() const
    {
        ModelData_Transformation r = *this;
        r.Invert();
        return r;
    }

    //! Transforms the coordinates using \a this transformation.
    __CADEX_EXPORT void Transform (double& theX, double& theY, double& theZ) const;

private:
#if _WIN32 || __x86_64__
    __CADEX_DEFINE_ALIGNED_MEMBER(sizeof(double) * 14, double)
#else
    __CADEX_DEFINE_ALIGNED_MEMBER(sizeof(double) * 13 + sizeof(int), double)
#endif
};

__CADEX_EXPORT bool operator== (const ModelData_Transformation& theV1, const ModelData_Transformation& theV2);

class ModelData_TransformationHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Transformation& theValue) const;
};

}

#endif

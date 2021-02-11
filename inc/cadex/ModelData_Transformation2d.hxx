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


#ifndef _ModelData_Transformation2d_HeaderFile
#define _ModelData_Transformation2d_HeaderFile

#include <cadex/Base_Macro.hxx>

class gp_Trsf2d;

namespace cadex {

class ModelData_Vector2d;

class ModelData_Transformation2d
{
public:
    __CADEX_EXPORT ModelData_Transformation2d();
    __CADEX_EXPORT ModelData_Transformation2d (const ModelData_Transformation2d& theOther);
    __CADEX_EXPORT ModelData_Transformation2d (const ModelData_Vector2d& theTranslation);

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_Transformation2d, gp_Trsf2d)

    __CADEX_EXPORT bool IsIdentity() const;

    __CADEX_EXPORT void SetRotationPart (
        double theV00, double theV01,
        double theV10, double theV11);

    __CADEX_EXPORT void RotationPart (
        double& theV00, double& theV01,
        double& theV10, double& theV11) const;

    __CADEX_EXPORT void SetTranslation (double theX, double theY);
    __CADEX_EXPORT void SetTranslation (const ModelData_Vector2d& theVec);
    __CADEX_EXPORT void SetTranslationPart (double theX, double theY);
    __CADEX_EXPORT void SetTranslationPart (const ModelData_Vector2d& theVec);
    __CADEX_EXPORT void TranslationPart (double& theX, double& theY) const;
    __CADEX_EXPORT ModelData_Vector2d TranslationPart() const;

    __CADEX_EXPORT void SetScaleFactor (double theScale);
    __CADEX_EXPORT double ScaleFactor() const;

    __CADEX_EXPORT double Data (int i, int j) const;

    __CADEX_EXPORT void operator *= (const gp_Trsf2d& theOther);
    __CADEX_EXPORT ModelData_Transformation2d operator * (const gp_Trsf2d& theOther) const;

    __CADEX_EXPORT void Multiply (const ModelData_Transformation2d& theOther);

    ModelData_Transformation2d Multiplied (const ModelData_Transformation2d& theOther) const
    {
        auto r = *this;
        r.Multiply (theOther);
        return r;
    }

    void operator *= (const ModelData_Transformation2d& theOther)
    {
        Multiply (theOther);
    }

    ModelData_Transformation2d operator * (const ModelData_Transformation2d& theOther) const
    {
        return Multiplied (theOther);
    }

    __CADEX_EXPORT void Invert();

    //! Returns an inverse of \a this matrix.
    /*! \sa Invert().*/
    ModelData_Transformation2d Inverted() const
    {
        ModelData_Transformation2d r = *this;
        r.Invert();
        return r;
    }

    //! Transforms the coordinates using \a this transformation.
    __CADEX_EXPORT void Transform (double& theX, double& theY) const;

private:
#if _WIN32 || __x86_64__
    __CADEX_DEFINE_ALIGNED_MEMBER (sizeof(double) * 8, double)
#else
    __CADEX_DEFINE_ALIGNED_MEMBER (sizeof(double) * 7 + sizeof(int), double)
#endif
};

__CADEX_EXPORT bool operator== (const ModelData_Transformation2d& theV1, const ModelData_Transformation2d& theV2);

class ModelData_Transformation2dHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Transformation2d& theValue) const;
};

}

#endif

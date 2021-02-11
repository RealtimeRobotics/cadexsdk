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


#ifndef _ModelPrs_Geometry_HeaderFile
#define _ModelPrs_Geometry_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelPrs_GeometryType.hxx>

#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_PublicObject.hxx>

namespace cadex {
class ModelPrs_GeometryVisitor;

namespace internal {
class ModelPrs_GeometryImpl;
}

class ModelPrs_Geometry : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_GeometryImpl    ImplType;

    __CADEX_EXPORT ModelPrs_Geometry();

    __CADEX_EXPORT ~ModelPrs_Geometry();

    __CADEX_EXPORT void Accept (ModelPrs_GeometryVisitor& theVisitor) const;

    __CADEX_EXPORT ModelPrs_GeometryType Type() const;

    __CADEX_EXPORT ModelPrs_Geometry (const ImplType* theImpl);
};


__CADEX_EXPORT bool operator== (const ModelPrs_Geometry& theFirstGeometry, const ModelPrs_Geometry& theSecondGeometry);

//! Non-equality operator.
inline bool operator!= (const ModelPrs_Geometry& theFirstGeometry, const ModelPrs_Geometry& theSecondGeometry)
{
    return !(theFirstGeometry == theSecondGeometry);
}

class ModelPrs_GeometryHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelPrs_Geometry& theGeometry) const;
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_Geometry_HeaderFile

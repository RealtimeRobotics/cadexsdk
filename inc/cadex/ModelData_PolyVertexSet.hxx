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

#ifndef _ModelData_PolyVertexSet_HeaderFile
#define _ModelData_PolyVertexSet_HeaderFile

#include <cadex/Base_Templates.hxx>
#include <cadex/ModelData_Point.hxx>
#include <cadex/ModelData_Color.hxx>
#include <cadex/ModelData_PolyShape.hxx>

namespace cadex {

class ModelData_Appearance;

class ModelData_PolyVertexSet : public ModelData_PolyShape
{
public:

    //! Type of indices.
    typedef int                                                IndexType;
    typedef cadex::internal::cadex_vector <IndexType>::type    IndexVecType;
    typedef ModelData_Point                                    CoordType;
    typedef ModelData_Color                                    ColorType;

    __CADEX_EXPORT ModelData_PolyVertexSet();

    __CADEX_EXPORT void SetAppearance (const ModelData_Appearance& theAppearance);
    __CADEX_EXPORT ModelData_Appearance Appearance() const;

    __CADEX_EXPORT const CoordType& Coordinate (IndexType theVertexIndex) const;

    __CADEX_EXPORT bool HasColors() const;

    //currently always returns true
    //__CADEX_EXPORT bool IsColorPerVertex() const;

    __CADEX_EXPORT const ColorType& Color (IndexType theIndex) const;

    __CADEX_EXPORT IndexType NumberOfVertices() const;

    __CADEX_EXPORT IndexType NumberOfColors() const;

    __CADEX_EXPORT bool IsEmpty() const;

protected:

    //! Constructor (reserved for internal use).
    ModelData_PolyVertexSet (internal::ModelData_BaseObjectImpl* theImpl) : ModelData_PolyShape (theImpl) {}
};

}

#endif 
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

#ifndef _ModelData_IndexedTriangleSet_HeaderFile
#define _ModelData_IndexedTriangleSet_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelData_Vector.hxx>
#include <cadex/ModelData_PolyVertexSet.hxx>

namespace cadex {
class ModelData_Point2d;

namespace internal {
class ModelData_IndexedTriangleSetImpl;
class ModelData_PolyShapeFactory;
class X3DGeometry3D_IndexedFaceSet;
}

class ModelData_IndexedTriangleSet : public ModelData_PolyVertexSet
{
public:

    //! Defines a type of the normal vector.
    /*! The vector can be not-normalized and even have a zero-length (in the case of incorrect input
        data or degenerated triangle).
    */
    typedef ModelData_Vectorf     NormalType;

    //! Defines a type of the UV coordinate.
    typedef ModelData_Point2d     UVCoordinateType;

    __CADEX_EXPORT ModelData_IndexedTriangleSet();
    __CADEX_EXPORT ModelData_IndexedTriangleSet (initialized);
    __CADEX_EXPORT ModelData_IndexedTriangleSet (internal::ModelData_IndexedTriangleSetImpl* theImpl);

    __CADEX_EXPORT IndexType NumberOfFaces() const;

    __CADEX_EXPORT IndexType NumberOfNormals() const;

    __CADEX_EXPORT IndexType NumberOfUVCoordinates() const;


    using ModelData_PolyVertexSet::Coordinate;

    __CADEX_EXPORT const CoordType& Coordinate (IndexType theFace, IndexType theVertexSlot) const;

    __CADEX_EXPORT IndexType CoordinateIndex (IndexType theFace, IndexType theVertexSlot) const;


    __CADEX_EXPORT NormalType FaceNormal (IndexType theFace) const;

    __CADEX_EXPORT bool HasNormals() const;

    __CADEX_EXPORT const NormalType& VertexNormal (IndexType theFace, IndexType theVertexSlot) const;

    __CADEX_EXPORT const NormalType& Normal (IndexType theIndex) const;

    __CADEX_EXPORT IndexType NormalIndex (IndexType theFace, IndexType theVertexSlot) const;


    __CADEX_EXPORT const ColorType& VertexColor (IndexType theFace, IndexType theVertexSlot) const;

    __CADEX_EXPORT IndexType ColorIndex (IndexType theFace, IndexType theVertexSlot) const;


    __CADEX_EXPORT bool HasUVCoordinates() const;

    __CADEX_EXPORT const ModelData_Point2d& UVCoordinate (IndexType theFace, IndexType theVertexSlot) const;

    __CADEX_EXPORT const ModelData_Point2d& UVCoordinate (IndexType theIndex) const;

    __CADEX_EXPORT IndexType UVCoordinateIndex (IndexType theFace, IndexType theVertexSlot) const;

    //construction API

    __CADEX_EXPORT void AddCoordinates (
        const CoordType theVertices[], size_t theVertexNb);

    //! Adds vertex coordinates and triangles.
    __CADEX_EXPORT void AddCoordinates (
        const CoordType theVertices[], size_t theVertexNb,
        const IndexType theIndices[],  size_t theIndexNb);

    //! Adds vertex coordinates and their indices.
    __CADEX_EXPORT void AddCoordinates (
        const CoordType theVertices[], size_t theVertexNb,
        const IndexType theIndices[],
        const IndexType theCounts[],   size_t theCountNb);

    //! Adds vertex normals.
    __CADEX_EXPORT void AddNormals (
        const NormalType theNormals[], size_t theNormalNb,
        const IndexType theIndices[],  size_t theIndexNb);

    //! Adds vertex normals.
    __CADEX_EXPORT void AddNormals (
        const NormalType theNormals[], size_t theNormalNb,
        const IndexType theIndices[],
        const IndexType theCounts[],   size_t theCountNb);

    //! Adds vertex colors.
    __CADEX_EXPORT void AddColors (
        const ColorType theColors[],  size_t theColorNb,
        const IndexType theIndices[], size_t theIndexNb);

    //! Adds vertex colors.
    __CADEX_EXPORT void AddColors (
        const ColorType theColors[],  size_t theColorNb,
        const IndexType theIndices[],
        const IndexType theCounts[],   size_t theCountNb);

    //! Adds UV coordinates.
    __CADEX_EXPORT void AddUVCoordinates (
        const UVCoordinateType theUVCoordinates[], size_t theUVCoordinateNb,
        const IndexType theIndices[], size_t theIndexNb);

    //! Adds UV coordinates.
    __CADEX_EXPORT void AddUVCoordinates (
        const UVCoordinateType theUVCoordinates[], size_t theUVCoordinateNb,
        const IndexType theIndices[],
        const IndexType theCounts[], size_t theCountNb);

    __CADEX_EXPORT void Merge();

    __CADEX_MODELDATA_DEFINE_TYPEID

private:

    __CADEX_EXPORT ModelData_IndexedTriangleSet (const internal::X3DGeometry3D_IndexedFaceSet& theIFS);
    friend class internal::ModelData_PolyShapeFactory;
};

}

#endif

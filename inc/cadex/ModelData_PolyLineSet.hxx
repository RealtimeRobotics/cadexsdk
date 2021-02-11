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

#ifndef _ModelData_PolyLineSet_HeaderFile
#define _ModelData_PolyLineSet_HeaderFile

#include <cadex/ModelData_PolyVertexSet.hxx>

namespace cadex {
namespace internal {
class ModelData_PolyLineSetImpl;
class ModelData_PolyShapeFactory;
class X3DRendering_LineSet;
}

class ModelData_PolyLineSet : public ModelData_PolyVertexSet
{
public:

    typedef cadex::internal::ModelData_PolyLineSetImpl ImplType;

    __CADEX_EXPORT ModelData_PolyLineSet();
    __CADEX_EXPORT ModelData_PolyLineSet (initialized);
    __CADEX_EXPORT ModelData_PolyLineSet (ImplType* theImpl);

    using ModelData_PolyVertexSet::NumberOfVertices;

    //! Returns a number of vertices in a polyline.
    __CADEX_EXPORT IndexType NumberOfVertices (IndexType thePolyline) const;

    //! Returns a number of polylines.
    __CADEX_EXPORT IndexType NumberOfPolyLines() const;

    using ModelData_PolyVertexSet::Coordinate;

    //! Returns a vertex coordinate.
    __CADEX_EXPORT const CoordType& Coordinate (IndexType thePolyline, IndexType theVertexSlot) const;

    //! Adds a polyline into the set.
    __CADEX_EXPORT void AddPolyLine (const CoordType* theVertices, size_t theSize);

    //! Adds all polylines from another set.
    __CADEX_EXPORT void AddPolyLines (const ModelData_PolyLineSet& theSet);

    __CADEX_MODELDATA_DEFINE_TYPEID

private:

    //! Constructor (reserved for internal use).
    __CADEX_EXPORT ModelData_PolyLineSet (const internal::X3DRendering_LineSet& theLS);
    friend class internal::ModelData_PolyShapeFactory;
};

}

#endif

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


#ifndef _ModelData_PolyLine2dSet_HeaderFile
#define _ModelData_PolyLine2dSet_HeaderFile

#include <cadex/ModelData_PolyVertex2dSet.hxx>


namespace cadex {
namespace internal {
class ModelData_PolyLine2dSetImpl;
}

class ModelData_PolyLine2dSet : public ModelData_PolyVertex2dSet
{
public:

    typedef cadex::internal::ModelData_PolyLine2dSetImpl    ImplType;

    __CADEX_EXPORT ModelData_PolyLine2dSet();
    __CADEX_EXPORT explicit ModelData_PolyLine2dSet (initialized);
    __CADEX_EXPORT explicit ModelData_PolyLine2dSet (ImplType* theImpl);

    using ModelData_PolyVertex2dSet::NumberOfVertices;

    __CADEX_EXPORT IndexType NumberOfVertices (IndexType thePolyline) const;

    __CADEX_EXPORT IndexType NumberOfPolyLines() const;

    using ModelData_PolyVertex2dSet::Coordinate;

    __CADEX_EXPORT const CoordType& Coordinate (IndexType thePolyline, IndexType theVertexSlot) const;

    __CADEX_EXPORT void AddPolyLine (const CoordType theVertices[], size_t theSize);

    __CADEX_EXPORT void AddPolyLines (const ModelData_PolyLine2dSet& theSet);

    __CADEX_MODELDATA_DEFINE_TYPEID
};

}

#endif

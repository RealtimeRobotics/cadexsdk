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

#ifndef _ModelData_PolyPointSet_HeaderFile
#define _ModelData_PolyPointSet_HeaderFile

#include <cadex/ModelData_PolyVertexSet.hxx>

namespace cadex {
namespace internal {
class ModelData_PolyPointSetImpl;
class ModelData_PolyShapeFactory;
class X3DRendering_PointSet;
}

class ModelData_PolyPointSet : public ModelData_PolyVertexSet
{
public:

    typedef cadex::internal::ModelData_PolyPointSetImpl    ImplType;

    __CADEX_EXPORT ModelData_PolyPointSet();
    __CADEX_EXPORT ModelData_PolyPointSet (initialized);
    __CADEX_EXPORT ModelData_PolyPointSet (ImplType* theImpl);

    __CADEX_EXPORT void Add (const CoordType* thePoints, size_t theSize);

    __CADEX_MODELDATA_DEFINE_TYPEID

private:

    __CADEX_EXPORT ModelData_PolyPointSet (const internal::X3DRendering_PointSet& thePS);
    friend class internal::ModelData_PolyShapeFactory;
};

}

#endif

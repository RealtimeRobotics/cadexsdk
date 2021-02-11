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

#ifndef _ModelData_PolyShapeList_HeaderFile
#define _ModelData_PolyShapeList_HeaderFile

#include <cadex/ModelData_PolyShape.hxx>

namespace cadex {

class ModelData_PolyVertexSet;
class ModelData_Appearance;

class ModelData_PolyShapeList : public ModelData_PolyShape
{
public:

    typedef size_t  SizeType;

    __CADEX_EXPORT ModelData_PolyShapeList();
    __CADEX_EXPORT ModelData_PolyShapeList (initialized);

    __CADEX_EXPORT void Append (const ModelData_PolyShape& theShape);

    __CADEX_EXPORT SizeType Size() const;

    __CADEX_EXPORT const ModelData_PolyVertexSet& Element (SizeType theIndex) const;

    const ModelData_PolyVertexSet& operator[] (SizeType theIndex) const { return Element (theIndex); }

    __CADEX_MODELDATA_DEFINE_TYPEID

};

}

#endif

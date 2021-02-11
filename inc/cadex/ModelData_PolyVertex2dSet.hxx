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


#ifndef _ModelData_PolyVertex2dSet_HeaderFile
#define _ModelData_PolyVertex2dSet_HeaderFile

#include <cadex/ModelData_Point2d.hxx>
#include <cadex/ModelData_PolyShape2d.hxx>


namespace cadex {

class ModelData_PolyVertex2dSet : public ModelData_PolyShape2d
{
public:

    //! Type of indices.
    typedef int                 IndexType;
    typedef ModelData_Point2d   CoordType;

    __CADEX_EXPORT ModelData_PolyVertex2dSet();

    __CADEX_EXPORT const CoordType& Coordinate (IndexType theVertexIndex) const;

    __CADEX_EXPORT IndexType NumberOfVertices() const;

    __CADEX_EXPORT bool IsEmpty() const;

protected:

    //! Constructor (reserved for internal use).
    explicit ModelData_PolyVertex2dSet (internal::ModelData_BaseObjectImpl* theImpl) :
        ModelData_PolyShape2d (theImpl)
    {}
};

}

#endif 
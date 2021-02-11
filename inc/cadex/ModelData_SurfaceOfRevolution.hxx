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


#ifndef _ModelData_SurfaceOfRevolution_HeaderFile
#define _ModelData_SurfaceOfRevolution_HeaderFile

#include <cadex/ModelData_SweptSurface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_SurfaceOfRevolution)

namespace cadex {
namespace internal {
class ModelData_SurfaceOfRevolutionImpl;
}

class ModelData_Direction;
class ModelData_Point;

class ModelData_SurfaceOfRevolution : public ModelData_SweptSurface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_SurfaceOfRevolutionImpl ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_SurfaceOfRevolution () {}

    __CADEX_EXPORT ModelData_SurfaceOfRevolution (
        const ModelData_Curve& theBasisCurve, const ModelData_Point& theLocation, const ModelData_Direction& theDirection);

    __CADEX_EXPORT const ModelData_Point& Location() const;

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_SurfaceOfRevolution,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_SurfaceOfRevolution,Geom_SurfaceOfRevolution)

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_SurfaceOfRevolution)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

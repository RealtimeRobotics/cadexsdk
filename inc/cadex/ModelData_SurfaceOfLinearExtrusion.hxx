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


#ifndef _ModelData_SurfaceOfLinearExtrusion_HeaderFile
#define _ModelData_SurfaceOfLinearExtrusion_HeaderFile

#include <cadex/ModelData_SweptSurface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_SurfaceOfLinearExtrusion)

namespace cadex {
namespace internal {
class ModelData_SurfaceOfLinearExtrusionImpl;
}

class ModelData_Direction;

class ModelData_SurfaceOfLinearExtrusion : public ModelData_SweptSurface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_SurfaceOfLinearExtrusionImpl    ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_SurfaceOfLinearExtrusion () {}

    __CADEX_EXPORT ModelData_SurfaceOfLinearExtrusion (
        const ModelData_Curve& theBasisCurve, const ModelData_Direction& theDirection);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_SurfaceOfLinearExtrusion,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_SurfaceOfLinearExtrusion,Geom_SurfaceOfLinearExtrusion)

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_SurfaceOfLinearExtrusion)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

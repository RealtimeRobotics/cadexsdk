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


#ifndef _ModelData_SphericalSurface_HeaderFile
#define _ModelData_SphericalSurface_HeaderFile

#include <cadex/ModelData_ElementarySurface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_SphericalSurface)

namespace cadex {
namespace internal {
class ModelData_SphericalSurfaceImpl;
}

class ModelData_SphericalSurface : public ModelData_ElementarySurface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_SphericalSurfaceImpl    ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_SphericalSurface () {}

    __CADEX_EXPORT ModelData_SphericalSurface (const ModelData_Axis3Placement& thePosition, double theRadius);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_SphericalSurface,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_SphericalSurface,Geom_SphericalSurface)

    __CADEX_EXPORT double Radius() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_SphericalSurface)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

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


#ifndef _ModelData_ConicalSurface_HeaderFile
#define _ModelData_ConicalSurface_HeaderFile

#include <cadex/ModelData_ElementarySurface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_ConicalSurface)

namespace cadex {
namespace internal {
class ModelData_ConicalSurfaceImpl;
}

class ModelData_ConicalSurface : public ModelData_ElementarySurface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_ConicalSurfaceImpl  ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_ConicalSurface () {}

    __CADEX_EXPORT ModelData_ConicalSurface (const ModelData_Axis3Placement& thePosition,
        double theSemiAngle, double theRadius);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_ConicalSurface,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_ConicalSurface,Geom_ConicalSurface)

    __CADEX_EXPORT double Angle() const;
    __CADEX_EXPORT double SemiAngle() const;

    __CADEX_EXPORT double Radius() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_ConicalSurface)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

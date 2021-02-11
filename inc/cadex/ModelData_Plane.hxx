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


#ifndef _ModelData_Plane_HeaderFile
#define _ModelData_Plane_HeaderFile

#include <cadex/ModelData_ElementarySurface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_Plane)

namespace cadex {
namespace internal {
class ModelData_PlaneImpl;
}

class ModelData_Plane : public ModelData_ElementarySurface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_PlaneImpl   ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_Plane() {}

    __CADEX_EXPORT ModelData_Plane (const ModelData_Axis3Placement& theAxis3);

    __CADEX_EXPORT ModelData_Plane (const ModelData_Point& theLocation, const ModelData_Direction& theDirection);

    __CADEX_EXPORT ModelData_Plane (double A, double B, double C, double D);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_Plane,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_Plane,Geom_Plane)

    __CADEX_EXPORT const ModelData_Point& Location() const;
    __CADEX_EXPORT const ModelData_Direction& Direction() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_Plane)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

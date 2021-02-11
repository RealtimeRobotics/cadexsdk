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


#ifndef _ModelData_Circle_HeaderFile
#define _ModelData_Circle_HeaderFile

#include <cadex/ModelData_Conic.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_Circle)

namespace cadex {

namespace internal {
class ModelData_CircleImpl;
}

class ModelData_Circle : public ModelData_Conic
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_CircleImpl  ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_Circle() {}

    __CADEX_EXPORT ModelData_Circle (const ModelData_Axis2Placement& thePosition, double theRadius);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_Circle,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_Circle,Geom_Circle)

    __CADEX_EXPORT double Radius() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_Circle)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

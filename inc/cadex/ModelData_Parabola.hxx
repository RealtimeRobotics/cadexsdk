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


#ifndef _ModelData_Parabola_HeaderFile
#define _ModelData_Parabola_HeaderFile

#include <cadex/ModelData_Conic.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_Parabola)

namespace cadex {
namespace internal {
class ModelData_ParabolaImpl;
}

class ModelData_Parabola : public ModelData_Conic
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_ParabolaImpl    ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_Parabola() {}

    __CADEX_EXPORT ModelData_Parabola (const ModelData_Axis2Placement& thePosition, double theFocal);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_Parabola,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_Parabola,Geom_Parabola)

    __CADEX_EXPORT double Focal() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_Parabola)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

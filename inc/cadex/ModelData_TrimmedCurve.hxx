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


#ifndef _ModelData_TrimmedCurve_HeaderFile
#define _ModelData_TrimmedCurve_HeaderFile

#include <cadex/ModelData_Curve.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_TrimmedCurve)

namespace cadex {
namespace internal {
class ModelData_TrimmedCurveImpl;
}

class ModelData_TrimmedCurve : public ModelData_Curve
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_TrimmedCurveImpl    ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_TrimmedCurve() {}

    __CADEX_EXPORT ModelData_TrimmedCurve (const ModelData_Curve& theBasisCurve, double U1, double U2);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_TrimmedCurve,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_TrimmedCurve,Geom_TrimmedCurve)

    __CADEX_EXPORT ModelData_Curve BasisCurve() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_TrimmedCurve)
    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

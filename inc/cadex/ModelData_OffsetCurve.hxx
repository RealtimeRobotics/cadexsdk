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


#ifndef _ModelData_OffsetCurve_HeaderFile
#define _ModelData_OffsetCurve_HeaderFile

#include <cadex/ModelData_Curve.hxx>
#include <cadex/ModelData_Direction.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_OffsetCurve)

namespace cadex {
namespace internal {
class ModelData_OffsetCurveImpl;
}

class ModelData_OffsetCurve : public ModelData_Curve
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_OffsetCurveImpl ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_OffsetCurve() {}

    __CADEX_EXPORT ModelData_OffsetCurve (const ModelData_Curve& theBasisCurve, double theOffset, const ModelData_Direction& theDir);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_OffsetCurve,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_OffsetCurve,Geom_OffsetCurve)

    __CADEX_EXPORT ModelData_Curve BasisCurve() const;

    __CADEX_EXPORT const ModelData_Direction& Direction() const;

    __CADEX_EXPORT double Offset() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_OffsetCurve)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

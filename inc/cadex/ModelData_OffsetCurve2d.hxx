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


#ifndef _ModelData_OffsetCurve2d_HeaderFile
#define _ModelData_OffsetCurve2d_HeaderFile

#include <cadex/ModelData_Curve2d.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom2d_OffsetCurve)

namespace cadex {
namespace internal {
class ModelData_OffsetCurve2dImpl;
}

class ModelData_OffsetCurve2d : public ModelData_Curve2d
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_OffsetCurve2dImpl   ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_OffsetCurve2d() {}

    __CADEX_EXPORT ModelData_OffsetCurve2d (const ModelData_Curve2d& theBasisCurve, double theOffset);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_OffsetCurve2d,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_OffsetCurve2d,Geom2d_OffsetCurve)

    __CADEX_EXPORT ModelData_Curve2d BasisCurve() const;

    __CADEX_EXPORT double Offset() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom2d_OffsetCurve)
    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

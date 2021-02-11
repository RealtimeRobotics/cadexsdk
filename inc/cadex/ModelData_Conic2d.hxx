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


#ifndef _ModelData_Conic2d_HeaderFile
#define _ModelData_Conic2d_HeaderFile

#include <cadex/ModelData_Curve2d.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom2d_Conic)

namespace cadex {
namespace internal {
class ModelData_Conic2dImpl;
}

class ModelData_Axis2Placement2d;

class ModelData_Conic2d : public ModelData_Curve2d
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_Conic2dImpl   ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_Conic2d() {}

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_Conic2d,ImplType*)

    __CADEX_EXPORT const ModelData_Axis2Placement2d& Position() const;

    __CADEX_EXPORT double Parameter (const ModelData_Point2d& thePoint) const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom2d_Conic)
    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)

#if !defined(SWIG) && !defined(__CADEX_DOXYGEN)
private:
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE2(ModelData_Conic2d,Geom2d_Conic,ModelData_CurveType)
#endif

};

}

#endif

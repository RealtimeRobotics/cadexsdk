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


#ifndef _ModelData_Line2d_HeaderFile
#define _ModelData_Line2d_HeaderFile

#include <cadex/ModelData_Curve2d.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom2d_Line)

namespace cadex {
namespace internal {
class ModelData_Line2dImpl;
}

class ModelData_Direction2d;
class ModelData_Point2d;

class ModelData_Line2d : public ModelData_Curve2d
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_Line2dImpl  ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_Line2d () {}

    __CADEX_EXPORT ModelData_Line2d (const ModelData_Point2d& theLocation, const ModelData_Direction2d& theDirection);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_Line2d,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_Line2d,Geom2d_Line)

    __CADEX_EXPORT const ModelData_Point2d& Location() const;
    __CADEX_EXPORT const ModelData_Direction2d& Direction () const;

    __CADEX_EXPORT double Parameter (const ModelData_Point2d& thePoint) const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom2d_Line)
    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

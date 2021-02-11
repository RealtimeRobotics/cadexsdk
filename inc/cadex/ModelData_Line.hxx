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


#ifndef _ModelData_Line_HeaderFile
#define _ModelData_Line_HeaderFile

#include <cadex/ModelData_Curve.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_Line)

namespace cadex {

class ModelData_Direction;
class ModelData_Point;

namespace internal {
class ModelData_LineImpl;
}

class ModelData_Line : public ModelData_Curve
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_LineImpl    ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_Line () {}

    __CADEX_EXPORT ModelData_Line (const ModelData_Point& theLocation, const ModelData_Direction& theDirection);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_Line,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_Line,Geom_Line)

    __CADEX_EXPORT const ModelData_Point& Location() const;
    __CADEX_EXPORT const ModelData_Direction& Direction () const;

    __CADEX_EXPORT double Parameter (const ModelData_Point& thePoint) const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_Line)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

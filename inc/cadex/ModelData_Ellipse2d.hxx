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


#ifndef _ModelData_Ellipse2d_HeaderFile
#define _ModelData_Ellipse2d_HeaderFile

#include <cadex/ModelData_Conic2d.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom2d_Ellipse)

namespace cadex {
namespace internal {
class ModelData_Ellipse2dImpl;
}

class ModelData_Ellipse2d : public ModelData_Conic2d
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_Ellipse2dImpl   ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_Ellipse2d() {}

    __CADEX_EXPORT ModelData_Ellipse2d (const ModelData_Axis2Placement2d& thePosition,
                                        double theMajorRadius, double theMinorRadius);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_Ellipse2d,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_Ellipse2d,Geom2d_Ellipse)

    __CADEX_EXPORT double MajorRadius() const;

    __CADEX_EXPORT double MinorRadius() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom2d_Ellipse)
    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

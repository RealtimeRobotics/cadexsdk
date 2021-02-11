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


#ifndef _ModelData_BezierCurve2d_HeaderFile
#define _ModelData_BezierCurve2d_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/ModelData_Curve2d.hxx>
#include <cadex/ModelData_Point2d.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom2d_BezierCurve)

namespace cadex {
namespace internal {
class ModelData_BezierCurve2dImpl;
}

class ModelData_BezierCurve2d : public ModelData_Curve2d
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_BezierCurve2dImpl   ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_BezierCurve2d() {}

    __CADEX_EXPORT ModelData_BezierCurve2d (const ModelData_Point2d thePoles[], int theNumberOfPoles);

    __CADEX_EXPORT ModelData_BezierCurve2d (const ModelData_Point2d thePoles[], const double thePoleWeights[], int theNumberOfPoles);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_BezierCurve2d,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_BezierCurve2d,Geom2d_BezierCurve)

    __CADEX_EXPORT int Degree() const;

    __CADEX_EXPORT int NumberOfPoles() const;

    __CADEX_EXPORT ModelData_Point2d Pole (const int theIndex) const;

    __CADEX_EXPORT int Poles (ModelData_Point2d thePoles[]) const;

    __CADEX_EXPORT double Weight (const int theIndex) const;

    __CADEX_EXPORT int Weights (double theWeights[]) const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom2d_BezierCurve)
    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

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


#ifndef _ModelData_BSplineCurve_HeaderFile
#define _ModelData_BSplineCurve_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/ModelData_Curve.hxx>
#include <cadex/ModelData_Point.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_BSplineCurve)

namespace cadex {
namespace internal {
class ModelData_BSplineCurveImpl;
}

class ModelData_BSplineCurve : public ModelData_Curve
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_BSplineCurveImpl    ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_BSplineCurve() {}

    __CADEX_EXPORT ModelData_BSplineCurve (
        const ModelData_Point thePoles[], int theNumberOfPoles,
        const double theKnots[], int theNumberOfKnots, const int theMultiplicities[], int theDegree,
        bool theIsPeriodic = false);

    __CADEX_EXPORT ModelData_BSplineCurve (
        const ModelData_Point thePoles[], const double thePoleWeights[], int theNumberOfPoles,
        const double theKnots[], int theNumberOfKnots, const int theMultiplicities[], int theDegree,
        bool theIsPeriodic = false);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_BSplineCurve,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_BSplineCurve,Geom_BSplineCurve)

    __CADEX_EXPORT int Degree() const;

    __CADEX_EXPORT int NumberOfKnots() const;

    __CADEX_EXPORT int NumberOfPoles() const;

    __CADEX_EXPORT double Knot (int theIndex) const;
    __CADEX_EXPORT int Knots (double theKnots[]) const;

    __CADEX_EXPORT int Multiplicity (int theIndex) const;
    __CADEX_EXPORT int Multiplicities (int theMultiplicities[]) const;

    __CADEX_EXPORT ModelData_Point Pole (int theIndex) const;
    __CADEX_EXPORT int Poles (ModelData_Point thePoles[]) const;

    __CADEX_EXPORT bool IsRational() const;

    __CADEX_EXPORT double Weight (int theIndex) const;
    __CADEX_EXPORT int Weights (double theWeights[]) const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_BSplineCurve)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

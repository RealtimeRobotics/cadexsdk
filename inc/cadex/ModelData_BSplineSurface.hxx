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


#ifndef _ModelData_BSplineSurface_HeaderFile
#define _ModelData_BSplineSurface_HeaderFile

#include <cadex/ModelData_Surface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_BSplineSurface)

namespace cadex {
namespace internal {
class ModelData_BSplineSurfaceImpl;
}

class ModelData_Point;

class ModelData_BSplineSurface : public ModelData_Surface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_BSplineSurfaceImpl  ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_BSplineSurface() {}

    __CADEX_EXPORT ModelData_BSplineSurface (
        const ModelData_Point thePoles[], int theNumberOfUPoles, int theNumberOfVPoles,
        const double theUKnots[], const double theVKnots[], int theNumberOfUKnots, int theNumberOfVKnots,
        const int theUMults[], const int theVMults[], int theUDegree, int theVDegree,
        bool theIsUPeriodic = false, bool theIsVPeriodic = false);

    __CADEX_EXPORT ModelData_BSplineSurface (
        const ModelData_Point thePoles[], const double thePoleWeights[], int theNumberOfUPoles, int theNumberOfVPoles,
        const double theUKnots[], const double theVKnots[], int theNumberOfUKnots, int theNumberOfVKnots,
        const int theUMults[], const int theVMults[], int theUDegree, int theVDegree,
        bool theIsUPeriodic = false, bool theIsVPeriodic = false);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_BSplineSurface,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_BSplineSurface,Geom_BSplineSurface)

    __CADEX_EXPORT int UDegree() const;

    __CADEX_EXPORT int VDegree() const;

    __CADEX_EXPORT int NumberOfUKnots() const;

    __CADEX_EXPORT int NumberOfUPoles() const;

    __CADEX_EXPORT int NumberOfVKnots() const;

    __CADEX_EXPORT int NumberOfVPoles() const;

    __CADEX_EXPORT double UKnot (int theUIndex) const;
    __CADEX_EXPORT int UKnots (double theUKnots[]) const;

    __CADEX_EXPORT double VKnot (int theVIndex) const;
    __CADEX_EXPORT int VKnots (double theVKnots[]) const;

    __CADEX_EXPORT int UMultiplicity (int theUIndex) const;
    __CADEX_EXPORT int UMultiplicities (int theUMultiplicities[]) const;

    __CADEX_EXPORT int VMultiplicity (int theVIndex) const;
    __CADEX_EXPORT int VMultiplicities (int theVMultiplicities[]) const;

    __CADEX_EXPORT ModelData_Point Pole (int theUIndex, int theVIndex) const;
    __CADEX_EXPORT int Poles (ModelData_Point thePoles[]) const;

    __CADEX_EXPORT bool IsURational() const;
    __CADEX_EXPORT bool IsVRational() const;

    __CADEX_EXPORT double Weight (int theUIndex, int theVIndex) const;
    __CADEX_EXPORT int Weights (double theWeights[]) const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_BSplineSurface)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

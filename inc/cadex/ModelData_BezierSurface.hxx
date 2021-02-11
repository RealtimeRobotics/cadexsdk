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


#ifndef _ModelData_BezierSurface_HeaderFile
#define _ModelData_BezierSurface_HeaderFile

#include <cadex/ModelData_Surface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_BezierSurface)

namespace cadex {
namespace internal {
class ModelData_BezierSurfaceImpl;
}

class ModelData_Point;

class ModelData_BezierSurface : public ModelData_Surface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_BezierSurfaceImpl   ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_BezierSurface() {}

    __CADEX_EXPORT ModelData_BezierSurface (
        const ModelData_Point thePoles[], int theNumberOfUPoles, int theNumberOfVPoles);

    __CADEX_EXPORT ModelData_BezierSurface (
        const ModelData_Point thePoles[], const double thePoleWeights[], int theNumberOfUPoles, int theNumberOfVPoles);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_BezierSurface,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_BezierSurface,Geom_BezierSurface)

    __CADEX_EXPORT int UDegree() const;

    __CADEX_EXPORT int VDegree() const;

    __CADEX_EXPORT int NumberOfUPoles() const;

    __CADEX_EXPORT int NumberOfVPoles() const;

    __CADEX_EXPORT ModelData_Point Pole (const int theUIndex, const int theVIndex) const;

    __CADEX_EXPORT int Poles (ModelData_Point thePoles[]) const;

    __CADEX_EXPORT double Weight (const int theUIndex, const int theVIndex) const;

    __CADEX_EXPORT int Weights (double theWeights[]) const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_BezierSurface)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

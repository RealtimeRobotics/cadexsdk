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


#ifndef _ModelData_ToroidalSurface_HeaderFile
#define _ModelData_ToroidalSurface_HeaderFile

#include <cadex/ModelData_ElementarySurface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_ToroidalSurface)

namespace cadex {
namespace internal {
class ModelData_ToroidalSurfaceImpl;
}

class ModelData_ToroidalSurface : public ModelData_ElementarySurface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_ToroidalSurfaceImpl ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_ToroidalSurface () {}

    __CADEX_EXPORT ModelData_ToroidalSurface (const ModelData_Axis3Placement& thePosition,
        double theMajorRadius, double theMinorRadius);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_ToroidalSurface,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_ToroidalSurface,Geom_ToroidalSurface)

    __CADEX_EXPORT double MajorRadius () const;

    __CADEX_EXPORT double MinorRadius () const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_ToroidalSurface)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

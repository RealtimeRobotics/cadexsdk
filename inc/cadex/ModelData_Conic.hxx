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


#ifndef _ModelData_Conic_HeaderFile
#define _ModelData_Conic_HeaderFile

#include <cadex/ModelData_Curve.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_Conic)

namespace cadex {
namespace internal {
class ModelData_ConicImpl;
}

class ModelData_Axis2Placement;

class ModelData_Conic : public ModelData_Curve
{
public:

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_Conic() {}

    __CADEX_EXPORT const ModelData_Axis2Placement& Position() const;

    __CADEX_EXPORT double Parameter (const ModelData_Point& thePoint) const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_Conic)
    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(internal::ModelData_ConicImpl)

#if !defined(SWIG) && !defined(__CADEX_DOXYGEN)
protected:

    ModelData_Conic (internal::ModelData_ConicImpl* theImpl);

private:
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE2(ModelData_Conic,Geom_Conic,ModelData_CurveType)
#endif
};

}

#endif

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


#ifndef _ModelData_ElementarySurface_HeaderFile
#define _ModelData_ElementarySurface_HeaderFile

#include <cadex/ModelData_Surface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_ElementarySurface)

namespace cadex {

class ModelData_Axis3Placement;
class ModelData_Direction;
class ModelData_Point;
class ModelData_Point2d;

namespace internal {
class ModelData_ElementarySurfaceImpl;
}

class ModelData_ElementarySurface : public ModelData_Surface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_ElementarySurfaceImpl   ImplType;

    //! Constructor.
    /*! Empty constructor. Creates null object.*/
    ModelData_ElementarySurface() {}

    __CADEX_EXPORT const ModelData_Axis3Placement& Position() const;

    __CADEX_EXPORT const ModelData_Point& Location() const;
    __CADEX_EXPORT const ModelData_Direction& Direction() const;

    __CADEX_EXPORT ModelData_Point2d Parameter (const ModelData_Point& thePoint) const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_ElementarySurface)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)

protected:
    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_ElementarySurface,ImplType*)

#if !defined(SWIG) && !defined(__CADEX_DOXYGEN)
private:
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE2(ModelData_ElementarySurface,Geom_Surface,ModelData_SurfaceType)
#endif
};

}

#endif

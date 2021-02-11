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


#ifndef _ModelData_OffsetSurface_HeaderFile
#define _ModelData_OffsetSurface_HeaderFile

#include <cadex/ModelData_Surface.hxx>

__CADEX_DEFINE_HANDLE_FWD_PUBLIC(Geom_OffsetSurface)

namespace cadex {
namespace internal {
class ModelData_OffsetSurfaceImpl;
}

class ModelData_OffsetSurface : public ModelData_Surface
{
public:

    /*! \internal */
    typedef cadex::internal::ModelData_OffsetSurfaceImpl   ImplType;

    //! Constructor.
    /*! Empty constructor.*/
    ModelData_OffsetSurface() {}

    __CADEX_EXPORT ModelData_OffsetSurface (const ModelData_Surface& theBasisSurface, double theOffset);

    __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(ModelData_OffsetSurface,ImplType*)
    __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(ModelData_OffsetSurface,Geom_OffsetSurface)

    __CADEX_EXPORT ModelData_Surface BasisSurface() const;

    __CADEX_EXPORT double Offset() const;

    __CADEX_DEFINE_HANDLE_CAST_OPERATOR(Geom_OffsetSurface)

    __CADEX_DEFINE_TYPED_POINTER_OPERATOR(ImplType)
};

}

#endif

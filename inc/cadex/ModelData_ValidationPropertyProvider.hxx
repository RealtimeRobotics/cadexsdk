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


#ifndef _ModelData_ValidationPropertyProvider_HeaderFile
#define _ModelData_ValidationPropertyProvider_HeaderFile

#include <cadex/ModelData_RefPropertyProvider.hxx>

namespace cadex {

class ModelData_ValidationPropertyProvider : public ModelData_RefPropertyProvider
{
public:

    //! Defines a mask used to select validation properties to compute
    enum MaskType {
        SurfaceArea = 0x01,
        Volume      = 0x02,
        Centroid    = 0x04,
        All         = SurfaceArea | Volume | Centroid
    };

    __CADEX_EXPORT ModelData_ValidationPropertyProvider (int theMask = All);

    __CADEX_EXPORT ModelData_ValidationPropertyProvider (
        const ModelData_SceneGraphElement& theRef,
        int theMask = All);

    //! Feeds the property table.
    __CADEX_EXPORT virtual void Feed (ModelData_PropertyTable& theTable) const;

    //! Returns the mask.
    /*! Returns the value specified in the constructor.*/
    __CADEX_DEFINE_PRIMITIVE_PROPERTY (int, Mask)
};

}

#endif

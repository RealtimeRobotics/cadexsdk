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


#ifndef _ModelData_BoundingBoxProvider_HeaderFile
#define _ModelData_BoundingBoxProvider_HeaderFile

#include <cadex/ModelData_RefPropertyProvider.hxx>

namespace cadex {

class ModelData_BoundingBoxProvider : public ModelData_RefPropertyProvider
{
public:

    __CADEX_EXPORT ModelData_BoundingBoxProvider();

    __CADEX_EXPORT ModelData_BoundingBoxProvider (
        const ModelData_SceneGraphElement& theRef);

    //! Feeds the property table.
    __CADEX_EXPORT virtual void Feed (ModelData_PropertyTable& theTable) const;
};

}

#endif

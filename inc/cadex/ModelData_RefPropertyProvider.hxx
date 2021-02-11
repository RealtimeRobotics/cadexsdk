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


#ifndef _ModelData_RefPropertyProvider_HeaderFile
#define _ModelData_RefPropertyProvider_HeaderFile

#include <cadex/ModelData_PropertyTable.hxx>
#include <cadex/ModelData_SceneGraphElement.hxx>

namespace cadex {
namespace internal {
class ModelData_SceneGraphElementImpl;
}

class ModelData_RefPropertyProvider : public ModelData_PropertyTable::Provider
{
public:

    __CADEX_EXPORT ModelData_RefPropertyProvider();

    __CADEX_EXPORT ModelData_RefPropertyProvider (const ModelData_SceneGraphElement& theRef);

    __CADEX_EXPORT ModelData_SceneGraphElement Ref() const;

    __CADEX_EXPORT void SetRef (const ModelData_SceneGraphElement& theRef);

protected:
    internal::ModelData_SceneGraphElementImpl*  myRef;
};

}

#endif

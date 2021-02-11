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


#ifndef _ModelCheck_ModelChecker_HeaderFile
#define _ModelCheck_ModelChecker_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_SharedPtr.hxx>
#include <cadex/ModelCheck_ErrorLevel.hxx>

namespace cadex {

namespace internal {
class ModelCheck_Result;
}

class ModelData_BRepRepresentation;
class ModelData_Model;
class ModelData_PolyRepresentation;
class ModelData_SceneGraphElement;

class ModelCheck_ModelChecker
{
public:
    __CADEX_EXPORT ModelCheck_ModelChecker();

    __CADEX_EXPORT bool Check (const ModelData_Model& theModel);
    __CADEX_EXPORT bool Check (const ModelData_SceneGraphElement& theElement);

    __CADEX_EXPORT bool Check (const ModelData_BRepRepresentation& theRep);
    __CADEX_EXPORT bool Check (const ModelData_PolyRepresentation& theRep);

    __CADEX_EXPORT int NumberOfErrors (ModelCheck_ErrorLevel theLevel) const;

    //! Returns internal resulting object.
    /*! \internal
    */
    const std::shared_ptr<internal::ModelCheck_Result>& Result() const
    { return myResult; }

private:
    std::shared_ptr<internal::ModelCheck_Result>    myResult;
};

}

#endif

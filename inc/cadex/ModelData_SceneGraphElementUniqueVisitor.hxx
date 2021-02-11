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


#ifndef _ModelData_SceneGraphElementUniqueVisitor_HeaderFile
#define _ModelData_SceneGraphElementUniqueVisitor_HeaderFile

#include <cadex/Base_SharedPtr.hxx>
#include <cadex/ModelData_BaseObject.hxx>
#include <cadex/ModelData_SceneGraphElementVisitorDecorator.hxx>

namespace cadex {
namespace internal {
class ModelData_SceneGraphElementUniqueVisitorImpl;
}

class ModelData_SceneGraphElementUniqueVisitor :
    public internal::ModelData_SceneGraphElementVisitorDecorator
{
public:

    __CADEX_EXPORT ModelData_SceneGraphElementUniqueVisitor (ModelData_Model::ElementVisitor& theRef);

    __CADEX_EXPORT virtual void operator() (const ModelData_Part& thePart) override;
    __CADEX_EXPORT virtual bool VisitEnter (const ModelData_Assembly& theAssembly) override;
    __CADEX_EXPORT virtual void VisitLeave (const ModelData_Assembly& theAssembly) override;
    __CADEX_EXPORT virtual bool VisitEnter (const ModelData_Instance& theInstance) override;
    __CADEX_EXPORT virtual void VisitLeave (const ModelData_Instance& theInstance) override;


private:
    std::shared_ptr<internal::ModelData_SceneGraphElementUniqueVisitorImpl> myImpl;

};

}


#endif

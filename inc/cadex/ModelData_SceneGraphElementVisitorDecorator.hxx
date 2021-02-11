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


#ifndef _ModelData_SceneGraphElementVisitorDecorator_HeaderFile
#define _ModelData_SceneGraphElementVisitorDecorator_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_NoCopy.hxx>
#include <cadex/ModelData_Model.hxx>

namespace cadex {
namespace internal {

class ModelData_SceneGraphElementVisitorDecorator : public ModelData_Model::ElementVisitor,
                                                           private Base_NoAssignment
{
public:

    //! Constructor.
    ModelData_SceneGraphElementVisitorDecorator (
        ModelData_Model::ElementVisitor& theRef) : myRef (theRef) {}

    //! Returns the associated visitor.
    ModelData_Model::ElementVisitor& Reference() const { return myRef; }

    __CADEX_EXPORT virtual void VisitLeave (const ModelData_Assembly& theAssembly) override;
    __CADEX_EXPORT virtual void VisitLeave (const ModelData_Instance& theInstance) override;

protected:

    //! Referenced visitor specified in the constructor.
    /*! \sa Reference().*/
    ModelData_Model::ElementVisitor& myRef;
};

}}

#endif

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


#ifndef _ModelData_PMIGraphicalElementComponentVisitor_HeaderFile
#define _ModelData_PMIGraphicalElementComponentVisitor_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

namespace cadex {
class ModelData_PMIOutlinedComponent;
class ModelData_PMITextComponent;
class ModelData_PMITriangulatedComponent;

class ModelData_PMIGraphicalElementComponentVisitor
{
public:

    __CADEX_EXPORT virtual ~ModelData_PMIGraphicalElementComponentVisitor();

    virtual void operator() (const ModelData_PMIOutlinedComponent&     theComponent) = 0;
    virtual void operator() (const ModelData_PMITextComponent&         theComponent) = 0;
    virtual void operator() (const ModelData_PMITriangulatedComponent& theComponent) = 0;
};

class ModelData_PMIGraphicalElementComponentVoidVisitor : public ModelData_PMIGraphicalElementComponentVisitor
{
public:

    __CADEX_EXPORT void operator() (const ModelData_PMIOutlinedComponent&     theComponent) override;
    __CADEX_EXPORT void operator() (const ModelData_PMITextComponent&         theComponent) override;
    __CADEX_EXPORT void operator() (const ModelData_PMITriangulatedComponent& theComponent) override;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

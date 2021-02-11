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


#ifndef _ModelData_PMISemanticElementComponentVisitor_HeaderFile
#define _ModelData_PMISemanticElementComponentVisitor_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

namespace cadex {
class ModelData_PMIDatumComponent;
class ModelData_PMIDimensionComponent;
class ModelData_PMIGeometricToleranceComponent;

class ModelData_PMISemanticElementComponentVisitor
{
public:

    __CADEX_EXPORT virtual ~ModelData_PMISemanticElementComponentVisitor();

    virtual void operator() (const ModelData_PMIDimensionComponent&          theComponent) = 0;
    virtual void operator() (const ModelData_PMIGeometricToleranceComponent& theComponent) = 0;
    virtual void operator() (const ModelData_PMIDatumComponent&              theComponent) = 0;
};

class ModelData_PMISemanticElementComponentVoidVisitor : public ModelData_PMISemanticElementComponentVisitor
{
public:

    __CADEX_EXPORT void operator() (const ModelData_PMIDimensionComponent&          theComponent) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIGeometricToleranceComponent& theComponent) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIDatumComponent&              theComponent) override;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

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


#ifndef _ModelData_PMISemanticAttributeVisitor_HeaderFile
#define _ModelData_PMISemanticAttributeVisitor_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

namespace cadex {
class ModelData_PMIAngleUnitAttribute;
class ModelData_PMIDatumRefAttribute;
class ModelData_PMIDatumRefCompartmentAttribute;
class ModelData_PMIDatumTargetAttribute;
class ModelData_PMIDisplacementAttribute;
class ModelData_PMILengthUnitAttribute;
class ModelData_PMILimitsAndFitsAttribute;
class ModelData_PMIMaximumValueAttribute;
class ModelData_PMIModifierAttribute;
class ModelData_PMIModifierWithValueAttribute;
class ModelData_PMIPlusMinusBoundsAttribute;
class ModelData_PMIQualifierAttribute;
class ModelData_PMIRangeAttribute;

class ModelData_PMISemanticAttributeVisitor
{
public:

    __CADEX_EXPORT virtual ~ModelData_PMISemanticAttributeVisitor();

    virtual void operator() (const ModelData_PMIModifierAttribute&            theAttribute) = 0;
    virtual void operator() (const ModelData_PMIModifierWithValueAttribute&   theAttribute) = 0;
    virtual void operator() (const ModelData_PMIQualifierAttribute&           theAttribute) = 0;
    virtual void operator() (const ModelData_PMIPlusMinusBoundsAttribute&     theAttribute) = 0;
    virtual void operator() (const ModelData_PMIRangeAttribute&               theAttribute) = 0;
    virtual void operator() (const ModelData_PMILimitsAndFitsAttribute&       theAttribute) = 0;
    virtual void operator() (const ModelData_PMIDatumTargetAttribute&         theAttribute) = 0;
    virtual void operator() (const ModelData_PMIDatumRefAttribute&            theAttribute) = 0;
    virtual void operator() (const ModelData_PMIDatumRefCompartmentAttribute& theAttribute) = 0;
    virtual void operator() (const ModelData_PMIMaximumValueAttribute&        theAttribute) = 0;
    virtual void operator() (const ModelData_PMIDisplacementAttribute&        theAttribute) = 0;
    virtual void operator() (const ModelData_PMILengthUnitAttribute&          theAttribute) = 0;
    virtual void operator() (const ModelData_PMIAngleUnitAttribute&           theAttribute) = 0;
};

class ModelData_PMISemanticAttributeVoidVisitor : public ModelData_PMISemanticAttributeVisitor
{
public:

    __CADEX_EXPORT void operator() (const ModelData_PMIModifierAttribute&            theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIModifierWithValueAttribute&   theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIQualifierAttribute&           theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIPlusMinusBoundsAttribute&     theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIRangeAttribute&               theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMILimitsAndFitsAttribute&       theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIDatumTargetAttribute&         theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIDatumRefAttribute&            theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIDatumRefCompartmentAttribute& theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIMaximumValueAttribute&        theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIDisplacementAttribute&        theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMILengthUnitAttribute&          theAttribute) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIAngleUnitAttribute&           theAttribute) override;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

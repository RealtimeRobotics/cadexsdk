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


#ifndef _ModelData_PMIOutlineVisitor_HeaderFile
#define _ModelData_PMIOutlineVisitor_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

namespace cadex {
class ModelData_PMICurveOutline;
class ModelData_PMICurve2dOutline;
class ModelData_PMICompositeOutline;
class ModelData_PMIPolyOutline;
class ModelData_PMIPoly2dOutline;

class ModelData_PMIOutlineVisitor
{
public:

    __CADEX_EXPORT virtual ~ModelData_PMIOutlineVisitor();

    virtual void operator() (const ModelData_PMIPolyOutline&      theOutline) = 0;
    virtual void operator() (const ModelData_PMIPoly2dOutline&    theOutline) = 0;
    virtual void operator() (const ModelData_PMICurveOutline&     theOutline) = 0;
    virtual void operator() (const ModelData_PMICurve2dOutline&   theOutline) = 0;
    virtual bool VisitEnter (const ModelData_PMICompositeOutline& theOutline) = 0;
    virtual void VisitLeave (const ModelData_PMICompositeOutline& theOutline) = 0;
};

class ModelData_PMIOutlineVoidVisitor : public ModelData_PMIOutlineVisitor
{
public:

    __CADEX_EXPORT void operator() (const ModelData_PMIPolyOutline&      theOutline) override;
    __CADEX_EXPORT void operator() (const ModelData_PMIPoly2dOutline&    theOutline) override;
    __CADEX_EXPORT void operator() (const ModelData_PMICurveOutline&     theOutline) override;
    __CADEX_EXPORT void operator() (const ModelData_PMICurve2dOutline&   theOutline) override;
    __CADEX_EXPORT bool VisitEnter (const ModelData_PMICompositeOutline& theOutline) override;
    __CADEX_EXPORT void VisitLeave (const ModelData_PMICompositeOutline& theOutline) override;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

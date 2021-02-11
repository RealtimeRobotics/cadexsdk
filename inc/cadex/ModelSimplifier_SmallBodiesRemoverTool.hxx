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


#ifndef _ModelSimplifier_SmallBodiesRemoverTool_HeaderFile
#define _ModelSimplifier_SmallBodiesRemoverTool_HeaderFile

#include <cadex/ModelSimplifier_SimplifierTool.hxx>

#include <memory>

namespace cadex {

namespace internal {
class ModelSimplifierImpl_SmallBodiesRemoverTool;
}

class ModelSimplifier_SmallBodiesRemoverTool : public ModelSimplifier_SimplifierTool
{
public:

    __CADEX_EXPORT ModelSimplifier_SmallBodiesRemoverTool();

    __CADEX_EXPORT ModelData_Model Perform (const ModelData_Model& theSource) const override;

    __CADEX_EXPORT double Threshold() const;
    __CADEX_EXPORT void SetThreshold (double theValue);

    __CADEX_EXPORT bool RemovalIsVisualQualityAware() const;
    __CADEX_EXPORT void SetRemovalIsVisualQualityAware (bool theValue);

    __CADEX_EXPORT double VisualQualityThreshold() const;
    __CADEX_EXPORT void SetVisualQualityThreshold (double theValue);
};

}

#endif

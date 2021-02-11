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


#ifndef _ModelSimplifier_HoleRemoverTool_HeaderFile
#define _ModelSimplifier_HoleRemoverTool_HeaderFile

#include <cadex/ModelSimplifier_SimplifierTool.hxx>

#include <memory>

namespace cadex {

namespace internal {
class ModelSimplifierImpl_HoleRemoverTool;
}

class ModelSimplifier_HoleRemoverTool : public ModelSimplifier_SimplifierTool
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelSimplifier_HoleRemoverTool();

    __CADEX_EXPORT ModelData_Model Perform (const ModelData_Model& theSource) const override;

    __CADEX_EXPORT double ExtentThreshold() const;
    __CADEX_EXPORT void SetExtentThreshold (double theValue);

    __CADEX_EXPORT double VolumeThreshold() const;
    __CADEX_EXPORT void SetVolumeThreshold (double theValue);

    __CADEX_EXPORT double DiagonalThreshold() const;
    __CADEX_EXPORT void SetDiagonalThreshold (double theValue);

    __CADEX_EXPORT bool PerformInterferenceCheck() const;
    __CADEX_EXPORT void SetPerformInterferenceCheck (bool theValue);
};

}

#endif

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


#ifndef _ModelSimplifier_InternalFacesRemoverTool_HeaderFile
#define _ModelSimplifier_InternalFacesRemoverTool_HeaderFile

#include <cadex/ModelSimplifier_SimplifierTool.hxx>

#include <memory>

namespace cadex {

namespace internal {
class ModelSimplifierImpl_InternalFacesRemoverTool;
}

class ModelSimplifier_InternalFacesRemoverTool : public ModelSimplifier_SimplifierTool
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelSimplifier_InternalFacesRemoverTool();

    __CADEX_EXPORT ModelData_Model Perform (const ModelData_Model& theSource) const override;

    __CADEX_EXPORT double AngularTolerance() const;
    __CADEX_EXPORT void SetAngularTolerance (double theValue);

    __CADEX_EXPORT double LinearTolerance() const;
    __CADEX_EXPORT void SetLinearTolerance (double theValue);

    __CADEX_EXPORT bool IsLinearToleranceRelative() const;
    __CADEX_EXPORT void SetIsLinearToleranceRelative (bool theValue);

    __CADEX_EXPORT bool PreserveSharing() const;
    __CADEX_EXPORT void SetPreserveSharing (bool theValue);
};

}

#endif

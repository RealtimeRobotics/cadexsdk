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


#ifndef _ModelSimplifier_MeshSimplifierTool_HeaderFile
#define _ModelSimplifier_MeshSimplifierTool_HeaderFile

#include <cadex/ModelSimplifier_SimplifierTool.hxx>

#include <memory>

namespace cadex {
class ModelSimplifier_MeshSimplifierParameters;

namespace internal {
class ModelSimplifierImpl_MeshSimplifierTool;
}

class ModelSimplifier_MeshSimplifierTool : public ModelSimplifier_SimplifierTool
{
public:

    __CADEX_EXPORT ModelSimplifier_MeshSimplifierTool();

    __CADEX_EXPORT ModelData_Model Perform (const ModelData_Model& theSource) const override;

    __CADEX_EXPORT void SetParameters (const ModelSimplifier_MeshSimplifierParameters& theParameters);

    __CADEX_EXPORT const ModelSimplifier_MeshSimplifierParameters& Parameters() const;

private:
    std::shared_ptr <internal::ModelSimplifierImpl_MeshSimplifierTool>  myImpl;
};

}

#endif


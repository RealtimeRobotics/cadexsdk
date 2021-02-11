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


#ifndef _ModelSimplifier_MeshSimplifier_HeaderFile
#define _ModelSimplifier_MeshSimplifier_HeaderFile

#if __CADEX_PREVIEW_ADVANCED_GEOMETRY
#include <memory>

namespace cadex {

namespace internal {
class ModelSimplifierImpl_MeshSimplifier;
}
class ModelData_Model;
class ModelData_PolyRepresentation;
class ModelSimplifier_MeshSimplifierParameters;

class ModelSimplifier_MeshSimplifier
{
public:
    __CADEX_EXPORT ModelSimplifier_MeshSimplifier();

    __CADEX_EXPORT ModelData_Model Perform (const ModelData_Model& theSource);
    __CADEX_EXPORT ModelData_PolyRepresentation Perform (const ModelData_PolyRepresentation& theSource);

    __CADEX_EXPORT void SetParameters (const ModelSimplifier_MeshSimplifierParameters& theParameters);
    __CADEX_EXPORT const ModelSimplifier_MeshSimplifierParameters& Parameters() const;

private:
    std::shared_ptr <internal::ModelSimplifierImpl_MeshSimplifier>  myImpl;
};

}

#endif //__CADEX_PREVIEW_ADVANCED_GEOMETRY
#endif

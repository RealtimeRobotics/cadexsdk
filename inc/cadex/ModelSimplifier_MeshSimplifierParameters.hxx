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

#ifndef _ModelSimplifier_MeshSimplifierParameters_HeaderFile
#define _ModelSimplifier_MeshSimplifierParameters_HeaderFile

#if __CADEX_PREVIEW_ADVANCED_GEOMETRY

#include <cadex/Base_Allocator.hxx>

#include <memory>

namespace cadex {
namespace internal {

class ModelSimplifierImpl_MeshSimplifierParameters;
}

class ModelSimplifier_MeshSimplifierParameters
{
public:

    enum DegreeOfSimplificationType {
        Low,
        Medium,
        High
    };

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelSimplifier_MeshSimplifierParameters();

    __CADEX_EXPORT DegreeOfSimplificationType DegreeOfSimplification() const;
    __CADEX_EXPORT void SetDegreeOfSimplification (DegreeOfSimplificationType theValue);

    __CADEX_EXPORT double MaxDeviation() const;
    __CADEX_EXPORT void SetMaxDeviation (double theValue);

    __CADEX_EXPORT bool ForceSimplification() const;
    __CADEX_EXPORT void SetForceSimplification (bool theValue);

    internal::ModelSimplifierImpl_MeshSimplifierParameters* Impl();

private:
    std::shared_ptr <internal::ModelSimplifierImpl_MeshSimplifierParameters> myImpl;
};

}
#endif //__CADEX_PREVIEW_ADVANCED_GEOMETRY
#endif
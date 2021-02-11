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


#ifndef _ModelSimplifier_SimplifierBuilder_HeaderFile
#define _ModelSimplifier_SimplifierBuilder_HeaderFile

#include <cadex/ModelSimplifier_Simplifier.hxx>

namespace cadex {
class ModelSimplifier_ShapePredicate;

namespace internal {
class ModelSimplifierImpl_SimplifierBuilder;
}

class ModelSimplifier_SimplifierBuilder
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    enum SimplificationLevel {
        Low,
        Middle,
        High
    };

    enum SimplifiedFeatureSize {
        Small,
        Medium,
        Large
    };

    __CADEX_EXPORT ModelSimplifier_SimplifierBuilder();

    __CADEX_EXPORT ModelSimplifier_Simplifier CreatePipeline() const;

    __CADEX_EXPORT SimplificationLevel Level() const;
    __CADEX_EXPORT void SetLevel (SimplificationLevel theValue);

    __CADEX_EXPORT SimplifiedFeatureSize FeatureSize() const;
    __CADEX_EXPORT void SetFeatureSize (SimplifiedFeatureSize theValue);

    __CADEX_EXPORT void SetShapePredicate (std::shared_ptr<ModelSimplifier_ShapePredicate> theFunction);

private:
    std::shared_ptr <internal::ModelSimplifierImpl_SimplifierBuilder> myImpl;
};

}

#endif

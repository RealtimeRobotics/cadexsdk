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


#ifndef _ModelSimplifier_SimplifierTool_HeaderFile
#define _ModelSimplifier_SimplifierTool_HeaderFile

#include <cadex/ModelData_Model.hxx>

#include <memory>

namespace cadex {
class ModelSimplifier_ShapePredicate;

namespace internal {
class ModelSimplifierImpl_SimplifierTool;
}

class ModelSimplifier_SimplifierTool
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT
    
    ModelSimplifier_SimplifierTool() = default;
    ModelSimplifier_SimplifierTool (const std::shared_ptr <internal::ModelSimplifierImpl_SimplifierTool>& theImpl);

    void SetShapePredicate (const std::shared_ptr <ModelSimplifier_ShapePredicate>& theShapePredicate);
    
    virtual ~ModelSimplifier_SimplifierTool()
    {}

    virtual ModelData_Model Perform (const ModelData_Model& theSource) const = 0;
    
protected:
    template <typename T>
    T* Impl() const
    {
        return static_cast<T*> (myImpl.get());
    }

private:
    std::shared_ptr <internal::ModelSimplifierImpl_SimplifierTool> myImpl;
};

}

#endif

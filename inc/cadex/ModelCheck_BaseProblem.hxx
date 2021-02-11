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


#ifndef _ModelCheck_BaseProblem_HeaderFile
#define _ModelCheck_BaseProblem_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_SharedPtr.hxx>

#include <cadex/ModelCheck_ErrorLevel.hxx>
#include <cadex/ModelCheck_ProblemType.hxx>
#include <cadex/ModelCheck_ProblemVisitor.hxx>


namespace cadex {
namespace internal {
class ModelCheck_BaseProblemImpl;
}

class ModelCheck_BaseProblem
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Desctructor.
    virtual ~ModelCheck_BaseProblem() {}

    //! Returns type of the problem.
    __CADEX_EXPORT ModelCheck_ProblemType Type() const;

    //! Returns level of the problem.
    __CADEX_EXPORT ModelCheck_ErrorLevel Level() const;

    //! Accepts a problem visitor.
    virtual void Accept (const ModelCheck_ProblemVisitor&) const = 0;

    __CADEX_DEFINE_BASE_IMPL (ModelCheck_BaseProblem)

protected:

    //! Internal.
    template <typename T>
    T* CastImpl() const
    { return static_cast<T*> (myImpl.get()); }
};

}

#endif

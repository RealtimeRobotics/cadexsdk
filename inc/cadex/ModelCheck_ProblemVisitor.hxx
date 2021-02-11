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


#ifndef _ModelCheck_ProblemVisitor_HeaderFile
#define _ModelCheck_ProblemVisitor_HeaderFile

#include <cadex/Base_Allocator.hxx>


namespace cadex {

class ModelCheck_ContinuityProblem;
class ModelCheck_EdgeToleranceProblem;
class ModelCheck_IntersectionProblem;
class ModelCheck_OverlapProblem;
class ModelCheck_SizeProblem;
class ModelCheck_TopologyProblem;
class ModelCheck_VertexToleranceProblem;

class ModelCheck_ProblemVisitor
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT virtual ~ModelCheck_ProblemVisitor();

    __CADEX_EXPORT virtual void Visit (const ModelCheck_ContinuityProblem&     ) const;
    __CADEX_EXPORT virtual void Visit (const ModelCheck_EdgeToleranceProblem&  ) const;
    __CADEX_EXPORT virtual void Visit (const ModelCheck_IntersectionProblem&   ) const;
    __CADEX_EXPORT virtual void Visit (const ModelCheck_OverlapProblem&        ) const;
    __CADEX_EXPORT virtual void Visit (const ModelCheck_SizeProblem&           ) const;
    __CADEX_EXPORT virtual void Visit (const ModelCheck_TopologyProblem&       ) const;
    __CADEX_EXPORT virtual void Visit (const ModelCheck_VertexToleranceProblem&) const;
};

}

#endif

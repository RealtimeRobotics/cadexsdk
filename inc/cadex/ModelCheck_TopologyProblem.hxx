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


#ifndef _ModelCheck_TopologyProblem_HeaderFile
#define _ModelCheck_TopologyProblem_HeaderFile

#include <cadex/ModelCheck_BaseProblem.hxx>


class TopoDS_Compound;

namespace cadex {

class ModelCheck_TopologyProblem : public ModelCheck_BaseProblem
{
public:

    enum ReasonEnum
    {
        BadEdgesOrientation,
        BadWiresOrientation,
        CodirectionalEdges,
        NoGeometry,
        NoSubshapes,
        NotClosed,
        RepeatingSubshape,
    };

    //! Constructor.
    __CADEX_EXPORT ModelCheck_TopologyProblem (ReasonEnum theReason);

    //! Constructor.
    __CADEX_EXPORT ModelCheck_TopologyProblem (ReasonEnum theReason, const TopoDS_Compound& theCompound);

    //! Returns the compound of associated shapes.
    __CADEX_EXPORT const TopoDS_Compound& Compound() const;

    //! Returns the reason of problem.
    __CADEX_EXPORT ReasonEnum Reason() const;

    __CADEX_ACCEPT_VISITOR (ModelCheck_ProblemVisitor)
};

}

#endif

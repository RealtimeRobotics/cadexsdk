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


#ifndef _ModelCheck_ProblemType_HeaderFile
#define _ModelCheck_ProblemType_HeaderFile

namespace cadex {

/*! \enum ModelCheck_ProblemType
    \brief Type of the problem from ModelCheck_BRepChecker.
*/
enum ModelCheck_ProblemType
{
    ModelCheck_PT_Undefined       = -1, // internal
    ModelCheck_PT_NoProblem       =  0, // internal

    ModelCheck_PT_Composite,            // internal
    ModelCheck_PT_Continuity,           //!< ModelCheck_ContinuityProblem
    ModelCheck_PT_EdgeTolerance,        //!< ModelCheck_EdgeToleranceProblem
    ModelCheck_PT_Intersection,         //!< ModelCheck_IntersectionProblem
    ModelCheck_PT_Overlap,              //!< ModelCheck_OverlapProblem
    ModelCheck_PT_Size,                 //!< ModelCheck_SizeProblem
    ModelCheck_PT_Tolerance,            //!< ModelCheck_ToleranceProblem
    ModelCheck_PT_Topology,             //!< ModelCheck_TopologyProblem
    ModelCheck_PT_VertexTolerance       //!< ModelCheck_VertexToleranceProblem
};

}

#endif

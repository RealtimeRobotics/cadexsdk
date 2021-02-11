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


#ifndef _ModelCheck_OverlapProblem_HeaderFile
#define _ModelCheck_OverlapProblem_HeaderFile

#include <cadex/ModelCheck_BaseProblem.hxx>

#include <cadex/Base_Templates.hxx>


class TopoDS_Edge;

namespace cadex {
class ModelCheck_DeviationSegment;

class ModelCheck_OverlapProblem : public ModelCheck_BaseProblem
{
public:

    //! Defines type of container for deviation segments.
    typedef cadex::internal::cadex_vector <ModelCheck_DeviationSegment>::type    SegmentsContainerType;

    //! Constructor.
    __CADEX_EXPORT ModelCheck_OverlapProblem (const TopoDS_Edge&           theEdge1,
                                              const TopoDS_Edge&           theEdge2,
                                              const SegmentsContainerType& theSegments,
                                              double                       theReqDistance);

    //! Returns first edge from two which overlap.
    __CADEX_EXPORT const TopoDS_Edge& Edge1() const;

    //! Returns second edge from two which overlap.
    __CADEX_EXPORT const TopoDS_Edge& Edge2() const;

    //! Returns deviation segments.
    __CADEX_EXPORT const SegmentsContainerType& Segments() const;

    //! Returns the minimum distance required for problem to disappear.
    __CADEX_EXPORT double ReqDistance() const;

    __CADEX_ACCEPT_VISITOR (ModelCheck_ProblemVisitor)
};

}

#endif

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


#ifndef _ModelCheck_EdgeToleranceProblem_HeaderFile
#define _ModelCheck_EdgeToleranceProblem_HeaderFile

#include <cadex/ModelCheck_ToleranceProblem.hxx>

#include <cadex/Base_Templates.hxx>


class TopoDS_Face;

namespace cadex {
class ModelCheck_DeviationSegment;

class ModelCheck_EdgeToleranceProblem : public ModelCheck_ToleranceProblem
{
public:

    //! Defines type of container for deviation segments.
    typedef cadex::internal::cadex_vector <ModelCheck_DeviationSegment>::type    SegmentsContainerType;

    //! Constructor.
    __CADEX_EXPORT ModelCheck_EdgeToleranceProblem (const TopoDS_Face&           theFace,
                                                    const SegmentsContainerType& theSegments,
                                                    double                       theStoredTolerance);

    //! Returns a face, pcurve of which has tolerance problem with edge's curve.
    __CADEX_EXPORT const TopoDS_Face& Face() const;

    //! Returns deviation segments.
    __CADEX_EXPORT const SegmentsContainerType& Segments() const;

    __CADEX_ACCEPT_VISITOR (ModelCheck_ProblemVisitor)
};

}

#endif

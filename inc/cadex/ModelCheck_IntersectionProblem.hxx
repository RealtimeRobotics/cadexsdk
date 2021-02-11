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


#ifndef _ModelCheck_IntersectionProblem_HeaderFile
#define _ModelCheck_IntersectionProblem_HeaderFile

#include <cadex/ModelCheck_BaseProblem.hxx>

#include <cadex/Base_Templates.hxx>


namespace cadex {
class ModelData_Point;

class ModelCheck_IntersectionProblem : public ModelCheck_BaseProblem
{
public:

    //! Defines type of container for intersection points.
    typedef cadex::internal::cadex_vector <ModelData_Point>::type    PointsContainerType;

    //! Constructor.
    __CADEX_EXPORT ModelCheck_IntersectionProblem();

    //! Returns intersection points.
    __CADEX_EXPORT const PointsContainerType& Points() const;

    __CADEX_ACCEPT_VISITOR (ModelCheck_ProblemVisitor)
};

}

#endif

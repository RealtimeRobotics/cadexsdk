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


#ifndef _ModelCheck_ContinuityProblem_HeaderFile
#define _ModelCheck_ContinuityProblem_HeaderFile

#include <cadex/ModelCheck_BaseProblem.hxx>

#include <cadex/ModelCheck_Continuity.hxx>


namespace cadex {

class ModelCheck_ContinuityProblem : public ModelCheck_BaseProblem
{
public:

    //! Constructor.
    __CADEX_EXPORT ModelCheck_ContinuityProblem (ModelCheck_Continuity            theContinuity,
                                                 const Handle(Standard_Transient)& theSource    );

    //! Returns actual continuity.
    __CADEX_EXPORT ModelCheck_Continuity Continuity() const;

    //! Returns source of the problem.
    __CADEX_EXPORT const Handle(Standard_Transient)& Source() const;

    __CADEX_ACCEPT_VISITOR (ModelCheck_ProblemVisitor)
};

}

#endif

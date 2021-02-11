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


#ifndef _ModelCheck_VertexToleranceProblem_HeaderFile
#define _ModelCheck_VertexToleranceProblem_HeaderFile

#include <cadex/ModelCheck_ToleranceProblem.hxx>


namespace cadex {

class ModelCheck_VertexToleranceProblem : public ModelCheck_ToleranceProblem
{
public:

    //! Constructor.
    __CADEX_EXPORT ModelCheck_VertexToleranceProblem (double theReqTolerance, double theStoredTolerance);
    
    //! Returns the tolerance required for problem to disappear.
    __CADEX_EXPORT double ReqTolerance() const;

    __CADEX_ACCEPT_VISITOR (ModelCheck_ProblemVisitor)
};

}

#endif

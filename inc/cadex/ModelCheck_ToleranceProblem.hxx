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


#ifndef _ModelCheck_ToleranceProblem_HeaderFile
#define _ModelCheck_ToleranceProblem_HeaderFile

#include <cadex/ModelCheck_BaseProblem.hxx>


namespace cadex {

class ModelCheck_ToleranceProblem : public ModelCheck_BaseProblem
{
public:

    //! Returns the tolerance stored in shape.
    __CADEX_EXPORT double StoredTolerance() const;

    //! Returns the subtype of problem.
    __CADEX_EXPORT ModelCheck_ProblemType SubType() const;

protected:

    // Internal.
    ModelCheck_ToleranceProblem (const ImplType& theImpl);
};

}

#endif

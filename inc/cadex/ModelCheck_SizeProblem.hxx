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


#ifndef _ModelCheck_SizeProblem_HeaderFile
#define _ModelCheck_SizeProblem_HeaderFile

#include <cadex/ModelCheck_BaseProblem.hxx>


namespace cadex {

class ModelCheck_SizeProblem : public ModelCheck_BaseProblem
{
public:

    //! Constructor.
    __CADEX_EXPORT ModelCheck_SizeProblem (double theReqSize, double theActualSize);

    //! Returns the minimum bounding box diagonal length required for problem to disappear.
    __CADEX_EXPORT double ReqSize() const;

    //! Returns actual length of bounding box diagonal.
    __CADEX_EXPORT double ActualSize() const;

    __CADEX_ACCEPT_VISITOR (ModelCheck_ProblemVisitor)
};

}

#endif

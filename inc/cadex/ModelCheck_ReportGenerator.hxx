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


#ifndef _ModelCheck_ReportGenerator_HeaderFile
#define _ModelCheck_ReportGenerator_HeaderFile

namespace cadex {
class ModelCheck_ModelChecker;
class ModelCheck_BRepChecker;

class ModelCheck_ReportGenerator
{
public:

    virtual ~ModelCheck_ReportGenerator() {}
    virtual bool Generate (const ModelCheck_ModelChecker& theChecker) = 0;
    virtual bool Generate (const ModelCheck_BRepChecker&  theChecker) = 0;
    virtual bool Dump() = 0;
};

}

#endif

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


#ifndef _ModelCheck_XmlReportGenerator_HeaderFile
#define _ModelCheck_XmlReportGenerator_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_SharedPtr.hxx>
#include <cadex/ModelCheck_ReportGenerator.hxx>

class TCollection_ExtendedString;

namespace cadex {

namespace internal {
class ModelCheck_XmlReportGeneratorImpl;
}

class ModelCheck_XmlReportGenerator : public ModelCheck_ReportGenerator
{
public:

    struct BRepCheckerMode {
    enum
    {
        Contents = 1 << 0,
        Tools    = 1 << 1,
        ByLevel  = 1 << 2,
        ByShape  = 1 << 3,

        All = Contents | Tools | ByLevel | ByShape
    };
    typedef int    FlagType;
    };

    __CADEX_EXPORT ModelCheck_XmlReportGenerator (const char* theFileName);

#if _WIN32
    __CADEX_EXPORT ModelCheck_XmlReportGenerator (const wchar_t* theFileName);
#endif

    __CADEX_EXPORT ModelCheck_XmlReportGenerator (const TCollection_ExtendedString& theFileName);

    __CADEX_EXPORT virtual bool Generate (const ModelCheck_ModelChecker& theChecker);
    __CADEX_EXPORT virtual bool Generate (const ModelCheck_BRepChecker&  theChecker);
    __CADEX_EXPORT virtual bool Dump();

    //! Sets a mode for ModelCheck_BRepChecker report.
    __CADEX_EXPORT void SetBRepCheckerMode (BRepCheckerMode::FlagType theMode);

    //! Returns an internal implementation object.
    /*! \internal */
    const std::shared_ptr<internal::ModelCheck_XmlReportGeneratorImpl>& Impl() const
    { return myImpl; }

private:
    std::shared_ptr<internal::ModelCheck_XmlReportGeneratorImpl>   myImpl;
};

}

#endif

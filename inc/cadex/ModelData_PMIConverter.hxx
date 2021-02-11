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


#ifndef _ModelData_PMIConverter_HeaderFile
#define _ModelData_PMIConverter_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

namespace cadex {
class ModelData_PMIOutline;
class ModelData_PolyLineSet;
class ModelData_Plane;

namespace internal {
class ModelData_PMIConverterImpl;
}

class ModelData_PMIConverter
{
public:
    __CADEX_EXPORT ModelData_PMIConverter();

    __CADEX_EXPORT ModelData_PolyLineSet Convert (const ModelData_PMIOutline& theOutline);

    __CADEX_EXPORT ModelData_PolyLineSet Convert (const ModelData_PMIOutline& theOutline,
                                                  const ModelData_Plane& thePlane);

private:
    std::shared_ptr <internal::ModelData_PMIConverterImpl>   myImpl;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

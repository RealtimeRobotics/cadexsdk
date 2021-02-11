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


#ifndef _ModelData_LineProperties_HeaderFile
#define _ModelData_LineProperties_HeaderFile

#include <cadex/Base_Allocator.hxx>

namespace cadex {

class ModelData_LineProperties
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    enum LineType
    {
        Solid                    = 1,
        Dashed                   = 2,
        Dotted                   = 3,
        DashedDotted             = 4,
        DashDotDot               = 5,
        Single                   = 6,
        SingleDot                = 7,
        DoubleArrow              = 8,
        StitchLine               = 9,
        ChainLine                = 10,
        CenterLine               = 11,
        HiddenLine               = 12,
        PhantomLine              = 13,
        BreakLine1               = 14,
        BreakLine2               = 15,
        UserSpecifiedDashPattern = 16
    };

    //! Constructor.
    __CADEX_EXPORT ModelData_LineProperties();

    __CADEX_DEFINE_PRIMITIVE_PROPERTY(LineType,Type)
    __CADEX_DEFINE_PRIMITIVE_PROPERTY(float,WidthScaleFactor)
};


__CADEX_EXPORT bool operator== (const ModelData_LineProperties& theV1, const ModelData_LineProperties& theV2);

class ModelData_LinePropertiesHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_LineProperties& theLP) const;
};


}
#endif

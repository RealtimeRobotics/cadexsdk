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


#ifndef _ModelPrs_TouchEvent_HeaderFile
#define _ModelPrs_TouchEvent_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelData_Point2d.hxx>

#include <list>

namespace cadex {
namespace internal {

class ModelPrs_TouchEvent
{
public:
    enum StateFlag {
        Pressed    = 0x01,
        Moved      = 0x02,
        Stationary = 0x04,
        Released   = 0x08
    };

    class Touch
    {
    public:
        typedef int    StatesType;

        __CADEX_EXPORT Touch (const ModelData_Point2d& thePosition, StatesType theState);

        __CADEX_DEFINE_PROPERTY (StatesType,        State)
        __CADEX_DEFINE_PROPERTY (ModelData_Point2d, Position)
    };

    typedef std::list<Touch>    TouchesType;

    __CADEX_EXPORT ModelPrs_TouchEvent();

    __CADEX_EXPORT ModelPrs_TouchEvent (const TouchesType& theTouches);

    __CADEX_EXPORT bool IsEmpty() const;

    __CADEX_DEFINE_PROPERTY (TouchesType, Touches)
};

}}

#endif // #ifndef _ModelPrs_TouchEvent_HeaderFile

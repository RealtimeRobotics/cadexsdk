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


#ifndef _ModelPrs_WheelEvent_HeaderFile
#define _ModelPrs_WheelEvent_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelPrs_MouseEvent.hxx>

namespace cadex {
namespace internal {

class ModelPrs_WheelEvent : public ModelPrs_MouseEvent
{
public:
    __CADEX_EXPORT ModelPrs_WheelEvent (const ModelData_Point2d&  thePosition,
                                        int                       theDelta,
                                        ModelPrs_KeyboardModifier theModifiers = ModelPrs_KM_NoModifier,
                                        ModelPrs_MouseButton      theButtons   = ModelPrs_MB_NoButton);

    int Degrees() const { return myDelta / 8; }

    __CADEX_DEFINE_PRIMITIVE_PROPERTY (int, Delta)
};

}}

#endif // _ModelPrs_WheelEvent_HeaderFile

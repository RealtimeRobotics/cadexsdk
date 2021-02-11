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


#ifndef _ModelPrs_MouseEvent_HeaderFile
#define _ModelPrs_MouseEvent_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelPrs_HoverEvent.hxx>
#include <cadex/ModelPrs_MouseButton.hxx>

namespace cadex {
namespace internal {

class ModelPrs_MouseEvent : public ModelPrs_HoverEvent
{
public:
    __CADEX_EXPORT ModelPrs_MouseEvent (const ModelData_Point2d&  thePosition,
                                        ModelPrs_MouseButton      theButtons   = ModelPrs_MB_NoButton,
                                        ModelPrs_KeyboardModifier theModifiers = ModelPrs_KM_NoModifier);

    __CADEX_EXPORT ModelPrs_MouseButton Buttons() const;

private:
    ModelPrs_MouseButton myButtons;
};

}}

#endif // _ModelPrs_MouseEvent_HeaderFile

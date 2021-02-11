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


#ifndef _ModelPrs_ManipulatorObserver_HeaderFile
#define _ModelPrs_ManipulatorObserver_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/ModelPrs_ManipulatorMode.hxx>

namespace cadex {
class ModelData_Direction;
class ModelData_Transformation;

class ModelPrs_ManipulatorObserver
{
public:
    __CADEX_EXPORT ModelPrs_ManipulatorObserver();

    __CADEX_EXPORT virtual ~ModelPrs_ManipulatorObserver();

    virtual void ModeChanged (ModelPrs_ManipulatorMode theMode, const ModelData_Direction& theDirection) = 0;

    virtual void StartTransformation() = 0;

    virtual void Transformed (const ModelData_Transformation& theLocalTrsf,
                              const ModelData_Transformation& theGlobalTrsf,
                              double theValue) = 0;

    virtual void StopTransformation() = 0;
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_ManipulatorObserver_HeaderFile

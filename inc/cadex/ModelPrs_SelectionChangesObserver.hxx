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


#ifndef _ModelPrs_SelectionChangesObserver_HeaderFile
#define _ModelPrs_SelectionChangesObserver_HeaderFile

#include <cadex/Base_Macro.hxx>
#if __CADEX_PREVIEW_VISUALIZATION

namespace cadex {
class ModelPrs_Selection;

class ModelPrs_SelectionChangesObserver
{
public:
    __CADEX_EXPORT ModelPrs_SelectionChangesObserver();

    __CADEX_EXPORT virtual ~ModelPrs_SelectionChangesObserver();

    virtual void SelectionChangedByScene (const ModelPrs_Selection& theCurrent,
                                          const ModelPrs_Selection& theSelected,
                                          const ModelPrs_Selection& theDeselected) = 0;

    virtual void SelectionChangedByManager (const ModelPrs_Selection& theCurrent,
                                            const ModelPrs_Selection& theSelected,
                                            const ModelPrs_Selection& theDeselected) = 0;
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_SelectionChangesObserver_HeaderFile

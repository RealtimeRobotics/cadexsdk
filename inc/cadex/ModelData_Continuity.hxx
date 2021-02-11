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


#ifndef _ModelData_Continuity_HeaderFile
#define _ModelData_Continuity_HeaderFile

namespace cadex {

/*! Provides information about the continuity of a curve/surface:
    \li C0: only geometric continuity.
    \li C1: continuity of the first derivative.
    \li C2: continuity of the second derivative.
    \li CN: continuity of the N-th derivative, whatever is the value given for N (infinite order of continuity).
*/
enum ModelData_Continuity
{
    ModelData_C0,
    ModelData_C1,
    ModelData_C2,
    ModelData_CN
};

}

#endif

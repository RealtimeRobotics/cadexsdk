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


#ifndef _Base_Version_HeaderFile
#define _Base_Version_HeaderFile

#define __CADEX_PRODUCT_MAJOR_VERSION       3
#define __CADEX_PRODUCT_MINOR_VERSION       9
#define __CADEX_PRODUCT_MAINTENANCE_VERSION 1

/*! \def __CADEX_PRODUCT_VERSION_HEX
    \brief Defines a hexadecimal code for the version

    Can be used to check current CAD Exchanger version:
    \code
    #if __CADEX_PRODUCT_VERSION >= __CADEX_PRODUCT_VERSION_HEX(2,1,0)
    \endcode
*/
#define __CADEX_PRODUCT_VERSION_HEX(MAJ,MIN,MNT) (((MAJ) << 16) | ((MIN) << 8) | (MNT))

/*! \def __CADEX_PRODUCT_VERSION
    \brief The __CADEX_PRODUCT_VERSION macro defines a version number of the release.

    The version represents a hexadecimal integer in the form 0xMMNNTT where
    \li MM is a major version number;
    \li NN is a minor version number;
    \li TT is a maintenance (or update) version number.

    For example, 0x010203 would describe version 1.2.3.

    Versions can be compared as follows. Version v2 is considered to be senior
    than v1 if __CADEX_PRODUCT_VERSION used to built v2 is greater than
    one used to built v1, or if they are equal and __CADEX_PRODUCT_VERSION_PHASE
    of v2 is greater one of v1.

    \sa __CADEX_PRODUCT_VERSION_PHASE, __CADEX_PRODUCT_VERSION_STR.
*/
#define __CADEX_PRODUCT_VERSION             __CADEX_PRODUCT_VERSION_HEX(\
    __CADEX_PRODUCT_MAJOR_VERSION,\
    __CADEX_PRODUCT_MINOR_VERSION,\
    __CADEX_PRODUCT_MAINTENANCE_VERSION)

#define __CADEX_PHASE_ALPHA                 0x01
#define __CADEX_PHASE_BETA                  0x02
#define __CADEX_PHASE_TECH_PREVIEW          0x10
#define __CADEX_PHASE_RC                    0x20
#define __CADEX_PHASE_PRODUCTION            0xFF
#define __CADEX_PRODUCT_VERSION_PHASE_HEX(PHASE,UPDATE) (((PHASE) << 8) | (UPDATE))

#define __CADEX_PHASE           __CADEX_PHASE_PRODUCTION
#define __CADEX_PHASE_UPDATE    0


/*! \def __CADEX_PRODUCT_VERSION_PHASE
    \brief The __CADEX_PRODUCT_VERSION_PHASE macro defines a phase of the release.

    The phase represents a hexadecimal integer in the form 0xPPUU where
    \li PP is a phase identifier;
    \li UU is an update number within the phase.

    Phases PP are encoded as follows:
    \li 0x00 - none/undefined;
    \li 0x01 - for Alpha;
    \li 0x02 - for Beta.
    \li 0x10 - Technology Preview.
    \li 0x20 - for Release Candidate.
    \li 0xFF - for Production.

    For example, 0x0202 would describe Beta2, 0x2003 - RC3.

    For description of comparing two versions refer to __CADEX_PRODUCT_VERSION.

    \sa __CADEX_PRODUCT_VERSION, __CADEX_PRODUCT_VERSION_STR.
*/
#define __CADEX_PRODUCT_VERSION_PHASE   __CADEX_PRODUCT_VERSION_PHASE_HEX(__CADEX_PHASE,__CADEX_PHASE_UPDATE)

/*! \def __CADEX_PRODUCT_VERSION_STR
    \brief The __CADEX_PRODUCT_VERSION_STR macro defines a version label.

    Examples include "Beta", "2.0.1", "3.0 Beta 2".

    \sa __CADEX_PRODUCT_VERSION, __CADEX_PRODUCT_VERSION_PHASE.
*/
#define __CADEX_PRODUCT_VERSION_STR     "3.9.1"

#define __CADEX_EXCHANGER_MSI_GUID      "2A7559BE-B732-5409-9665-71F9270FF93C"

#endif

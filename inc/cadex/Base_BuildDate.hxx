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

#ifndef _Base_BuildDate_HeaderFile
#define _Base_BuildDate_HeaderFile

/*! \def __CADEX_BUILD_YEAR
 *  \brief Defines build year.
 */
#define __CADEX_BUILD_YEAR ( \
    (__DATE__[ 7] - '0') * 1000 + \
    (__DATE__[ 8] - '0') *  100 + \
    (__DATE__[ 9] - '0') *   10 + \
    (__DATE__[10] - '0'))

/*! \def __CADEX_BUILD_MONTH
 *  \brief Defines build month.
 */
#define __CADEX_BUILD_MONTH (\
      __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) \
    : __DATE__ [2] == 'b' ? 2 \
    : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
    : __DATE__ [2] == 'y' ? 5 \
    : __DATE__ [2] == 'l' ? 7 \
    : __DATE__ [2] == 'g' ? 8 \
    : __DATE__ [2] == 'p' ? 9 \
    : __DATE__ [2] == 't' ? 10 \
    : __DATE__ [2] == 'v' ? 11 \
    : 12)

/*! \def __CADEX_BUILD_DAY
 *  \brief Defines build day.
 */
#define __CADEX_BUILD_DAY ( \
    ((__DATE__[4] >= '0') ? (__DATE__[4] - '0') * 10 : 0) + (__DATE__[5] - '0'))

/*! \def __CADEX_BUILD_DATE
 *  \brief Defines build date as number (e.g. 20191231).
 */
#define __CADEX_BUILD_DATE __CADEX_BUILD_YEAR * 10000 + __CADEX_BUILD_MONTH * 100 + __CADEX_BUILD_DAY

#endif

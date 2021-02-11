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


#include <cadex/Base_Macro.hxx>

#if _MSC_VER
#  if defined(CadExViewQtQuick_MAKEDLL) /* create a CadExViewQtQuick DLL library */
#    if defined(CadExViewQtQuick_DLL)
#      undef CadExViewQtQuick_DLL
#    endif
#    define CadExViewQtQuick_EXPORT __declspec(dllexport)
#  elif defined(CadExViewQtQuick_DLL)   /* use a CadExViewQtQuick DLL library */
#    define CadExViewQtQuick_EXPORT __declspec(dllimport)
#  else
#    define CadExViewQtQuick_EXPORT
#  endif
#else
#  define CadExViewQtQuick_EXPORT
#  define CadExViewQtQuick_EXPORT
#endif

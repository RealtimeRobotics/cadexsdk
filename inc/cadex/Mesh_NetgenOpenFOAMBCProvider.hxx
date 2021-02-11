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


#ifndef _Mesh_NetgenOpenFOAMBCProvider_HeaderFile
#define _Mesh_NetgenOpenFOAMBCProvider_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>

#include <list>
#include <utility>


namespace cadex {

class Mesh_NetgenOpenFOAMBCProvider
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT
    
    //! A two-field line used in boundary conditions description (e.g. "type patch").
    typedef std::pair<std::string, std::string> LineType;

    //! A list of lines representing a boundary condition description.
    typedef std::list<LineType>                 DescriptionListType;

    //! Destructor.
    __CADEX_EXPORT virtual ~Mesh_NetgenOpenFOAMBCProvider();

    //! Provides a description for a boundary condition.
    /*! Returns true if there is a description for a given BC index or false otherwise. */
    virtual bool BCDescription (int theBCIndex, DescriptionListType& theDescriptionList) = 0;
};

}

#endif

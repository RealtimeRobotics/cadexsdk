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


#ifndef _Mesh_NetgenOpenFOAMWriter_HeaderFile
#define _Mesh_NetgenOpenFOAMWriter_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Mesh_NetgenBaseWriter.hxx>
#include <cadex/Base_SharedPtr.hxx>


namespace cadex {

class Mesh_NetgenOpenFOAMBCProvider;

class Mesh_NetgenOpenFOAMWriter : public Mesh_NetgenBaseWriter
{
public:

    //! Constructor.
    __CADEX_EXPORT Mesh_NetgenOpenFOAMWriter();

    //! Sets a custom OpenFOAM boundary conditions describer.
    __CADEX_EXPORT void SetBCProvider (
        const std::shared_ptr<Mesh_NetgenOpenFOAMBCProvider>& theBCProvider);

    //! Switches the use of zlib compression.
    __CADEX_EXPORT void SetCompression (bool theFlag);
};

}

#endif

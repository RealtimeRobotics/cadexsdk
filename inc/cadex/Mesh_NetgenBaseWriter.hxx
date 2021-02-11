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


#ifndef _Mesh_NetgenBaseWriter_HeaderFile
#define _Mesh_NetgenBaseWriter_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cadex/Base_SharedPtr.hxx>


namespace cadex {

class Base_String;
class Mesh_NetgenMeshDS;

namespace internal {
class Mesh_NetgenBaseWriterImpl;
}

class Mesh_NetgenBaseWriter
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Writes internal Netgen mesh stored in \a theNetgenMeshDS to a target file.
    __CADEX_EXPORT bool WriteFile (const Mesh_NetgenMeshDS& theNetgenMeshDS,
                                   const Base_String&       theFileName    ) const;

protected:

    //! Constructor.
    __CADEX_EXPORT Mesh_NetgenBaseWriter (
        const std::shared_ptr<internal::Mesh_NetgenBaseWriterImpl>& theImpl);

    //! Implementation object.
    /*! \internal*/
    std::shared_ptr<internal::Mesh_NetgenBaseWriterImpl> myImpl;
};

}

#endif

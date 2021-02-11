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


#ifndef _Mesh_SMDS_HeaderFile
#define _Mesh_SMDS_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_SharedPtr.hxx>


namespace cadex {

class Mesh_NetgenMeshDS;

namespace internal {
class Mesh_SMDSImpl;
}

class Mesh_SMDS
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    __CADEX_EXPORT Mesh_SMDS();

    //! Constructor.
    __CADEX_EXPORT Mesh_SMDS (const std::shared_ptr<internal::Mesh_SMDSImpl>& theImpl);


    //! Check if there is a valid Netgen mesh data.
    __CADEX_EXPORT bool HasNetgenMeshDS() const;

    //! Returns the Netgen mesh data.
    __CADEX_EXPORT const Mesh_NetgenMeshDS& NetgenMeshDS() const;

    //! Returns the Netgen mesh data.
    __CADEX_EXPORT Mesh_NetgenMeshDS& NetgenMeshDS();

    //! Returns an implementation object.
    const std::shared_ptr<internal::Mesh_SMDSImpl>& Impl() const { return myImpl; }

    //! Returns true if the object is null.
    bool IsNull() const { return !myImpl; }

    //! Returns true if the object is not null.
    /*! \sa IsNull().*/
    operator bool() const { return !IsNull(); }

protected:

    //! Internal implementation object.
    std::shared_ptr<internal::Mesh_SMDSImpl>    myImpl;
};

}

#endif

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


#ifndef _Mesh_NetgenMeshDS_HeaderFile
#define _Mesh_NetgenMeshDS_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cadex/Base_SharedPtr.hxx>


class TopoDS_Face;

namespace cadex {

class Base_String;
class ModelData_Face;

namespace internal {
class Mesh_NetgenMeshDSImpl;
}

class Mesh_NetgenMeshDS
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    __CADEX_EXPORT Mesh_NetgenMeshDS();

    //! Sets a boundary condition index for a face.
    __CADEX_EXPORT bool SetFaceBCIndex (const ModelData_Face& theFace, int theBCIndex);

    //! Sets a boundary condition index for a face.
    __CADEX_EXPORT bool SetFaceBCIndex (const TopoDS_Face& theFace, int theBCIndex);

    //! Sets an amount of boundary conditions.
    __CADEX_EXPORT void SetNumberOfBCs (size_t theNum);

    //! Sets a name for a boundary condition.
    __CADEX_EXPORT void SetBCName (int theBCIndex, const Base_String& theName);

    //! Returns the amount of points.
    __CADEX_EXPORT size_t NumberOfPoints() const;

    //! Returns the amount of boundary faces.
    __CADEX_EXPORT size_t NumberOfBoundaryFaces() const;

    //! Returns the amount of surface elements.
    __CADEX_EXPORT size_t NumberOfSurfaceElements() const;

    //! Returns the amount of volume elements.
    __CADEX_EXPORT size_t NumberOfVolumeElements() const;

    __CADEX_EXPORT void RefineUniform();

    __CADEX_EXPORT void MakeSecondOrder();

    //! \internal
    /*! Returns the pointer to the implementation object.

        \warning This function is not part of CAD Exchanger API and should not be used.
    */
    const std::shared_ptr<internal::Mesh_NetgenMeshDSImpl>& Impl() const { return myImpl; }

private:

    std::shared_ptr<internal::Mesh_NetgenMeshDSImpl> myImpl;
};

}

#endif

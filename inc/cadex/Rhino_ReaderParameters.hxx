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


#ifndef _Rhino_ReaderParameters_HeaderFile
#define _Rhino_ReaderParameters_HeaderFile

#include <cadex/Base_ReaderParameters.hxx>
#include <cadex/ModelData_Material.hxx>


namespace cadex {

class Rhino_ReaderParameters : public Base_ReaderParameters
{
public:

    enum MeshType
    {
        Default,
        Render,
        Analysis,
        Preview
    };

    __CADEX_EXPORT Rhino_ReaderParameters();

    __CADEX_EXPORT const ModelData_Material&  DefaultMaterial() const;
    __CADEX_EXPORT       ModelData_Material&  DefaultMaterial();

    __CADEX_EXPORT MeshType  ImportMeshType() const;
    __CADEX_EXPORT MeshType& ImportMeshType();

    __CADEX_EXPORT bool  ImportHiddenObjects() const;
    __CADEX_EXPORT bool& ImportHiddenObjects();

    __CADEX_EXPORT bool  ReadPCurves() const;
    __CADEX_EXPORT bool& ReadPCurves();
};

}

#endif

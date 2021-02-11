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


#ifndef _ModelData_ShapeConverter_HeaderFile
#define _ModelData_ShapeConverter_HeaderFile

#include <cadex/Base_Macro.hxx>

class TopoDS_Shape;

namespace cadex {

class ModelData_Assembly;
class ModelData_Model;
class ModelData_SceneGraphElement;
class ModelData_Shape;

class ModelData_ShapeConverter
{
public:

    __CADEX_EXPORT static ModelData_SceneGraphElement Add (const TopoDS_Shape& theSource,
        ModelData_Model& theTarget,
        bool theBreakSharing = true);

    __CADEX_EXPORT static ModelData_SceneGraphElement Add (const TopoDS_Shape& theSource,
        ModelData_Assembly& theTarget,
        bool theBreakSharing = true);

    __CADEX_EXPORT static ModelData_Shape Convert (const TopoDS_Shape& theSource);

    __CADEX_EXPORT static TopoDS_Shape Convert (const ModelData_Model& theSource);

    __CADEX_EXPORT static TopoDS_Shape Convert (const ModelData_SceneGraphElement& theSource);
};

}

#endif

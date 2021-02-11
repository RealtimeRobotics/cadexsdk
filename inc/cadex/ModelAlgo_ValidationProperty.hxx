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


#ifndef _ModelAlgo_ValidationProperty_HeaderFile
#define _ModelAlgo_ValidationProperty_HeaderFile

#include <cadex/Base_Macro.hxx>

namespace cadex {

class ModelAlgo_ValidationPropertyData;
class ModelData_Model;
class ModelData_IndexedTriangleSet;
class ModelData_Point;
class ModelData_Representation;
class ModelData_SceneGraphElement;
class ModelData_Shape;

class ModelAlgo_ValidationProperty
{
public:

    //! Returns a surface area of a scene graph.
    __CADEX_EXPORT static double ComputeSurfaceArea (
        const ModelData_Model& theModel,
        bool theUseProperty = false,
        bool theStoreProperty = false);

    //! Returns a surface area of a scene graph element.
    __CADEX_EXPORT static double ComputeSurfaceArea (
        const ModelData_SceneGraphElement& theElement,
        bool theUseProperty = false,
        bool theStoreProperty = false);

    //! Returns a surface area of a representation.
    __CADEX_EXPORT static double ComputeSurfaceArea (const ModelData_Representation& theRep);

    //! Returns a surface area of a shape.
    __CADEX_EXPORT static double ComputeSurfaceArea (const ModelData_Shape& theRep);

    //! Returns a surface area of a triangle set.
    __CADEX_EXPORT static double ComputeSurfaceArea (const ModelData_IndexedTriangleSet& theTriangleSet);

    //! Returns a volume of a scene graph.
    __CADEX_EXPORT static double ComputeVolume (
        const ModelData_Model& theModel,
        bool theUseProperty = false,
        bool theStoreProperty = false);

    //! Returns a volume of a scene graph element.
    __CADEX_EXPORT static double ComputeVolume (
        const ModelData_SceneGraphElement& theElement,
        bool theUseProperty = false,
        bool theStoreProperty = false);

    //! Returns a volume of a representation.
    __CADEX_EXPORT static double ComputeVolume (const ModelData_Representation& theRep);

    //! Returns a volume of a shape.
    __CADEX_EXPORT static double ComputeVolume (const ModelData_Shape& theRep);

    //! Returns a volume of a triangle set.
    __CADEX_EXPORT static double ComputeVolume (const ModelData_IndexedTriangleSet& theTriangleSet);

    //! Returns a center of mass of a scene graph.
    __CADEX_EXPORT static void ComputeCentroid (
        const ModelData_Model& theModel,
        ModelData_Point& theValue);

    //! Returns a center of mass of a scene graph element.
    __CADEX_EXPORT static void ComputeCentroid (
        const ModelData_SceneGraphElement& theElement,
        ModelData_Point& theValue);

    //! Returns a center of mass of a representation.
    __CADEX_EXPORT static void ComputeCentroid (const ModelData_Representation& theRep,
        ModelData_Point& theValue);

    //! Returns a center of mass of a shape.
    __CADEX_EXPORT static void ComputeCentroid (const ModelData_Shape& theShape,
        ModelData_Point& theValue);

    __CADEX_EXPORT static bool ComputeValidationProperties (const ModelData_Model& theModel,
        ModelAlgo_ValidationPropertyData& theData);

    __CADEX_EXPORT static bool ComputeValidationProperties (const ModelData_SceneGraphElement& theElement,
        ModelAlgo_ValidationPropertyData& theData);

    __CADEX_EXPORT static bool ComputeValidationProperties (const ModelData_Representation& theRep,
        ModelAlgo_ValidationPropertyData& theData);

    __CADEX_EXPORT static bool ComputeValidationProperties (const ModelData_Shape& theShape,
        ModelAlgo_ValidationPropertyData& theData);

    __CADEX_EXPORT static bool ComputeValidationProperties (const ModelData_IndexedTriangleSet& theITS,
        ModelAlgo_ValidationPropertyData& theData);
};

}

#endif

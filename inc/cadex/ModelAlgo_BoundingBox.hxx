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


#ifndef _ModelAlgo_BoundingBox_HeaderFile
#define _ModelAlgo_BoundingBox_HeaderFile

#include <cadex/Base_Macro.hxx>

namespace cadex {

class ModelData_Box;
class ModelData_Box2d;
class ModelData_Face;
class ModelData_Model;
class ModelData_Part;
class ModelData_Representation;
class ModelData_SceneGraphElement;
class ModelData_Shape;
class ModelData_Transformation;

class ModelAlgo_BoundingBox
{
public:

    //! Returns a bounding box of a scene graph.
    __CADEX_EXPORT static void Compute (const ModelData_Model& theSG,
        ModelData_Box& theBox,
        bool theForcedFlush = true);

    //! Returns a bounding box of a scene graph element.
    __CADEX_EXPORT static void Compute (const ModelData_SceneGraphElement& theElement,
        ModelData_Box& theBox,
        bool theForcedFlush = true);

    //! Returns a bounding box of a representation.
    __CADEX_EXPORT static void Compute (const ModelData_Representation& theRep,
        ModelData_Box& theBox);

    //! Returns a bounding box of a representation.
    __CADEX_EXPORT static void Compute (const ModelData_Representation& theRep,
        const ModelData_Transformation& theTransformation,
        ModelData_Box& theBox);

    //! Returns a bounding box of a shape.
    __CADEX_EXPORT static void Compute (const ModelData_Shape& theShape,
        const ModelData_Transformation& theTransformation,
        ModelData_Box& theBox);

    __CADEX_EXPORT static void Compute (const ModelData_Face& theFace, ModelData_Box2d& theBox);

#if __CADEX_PREVIEW_MIN_BOUNDING_BOX
    //! Returns a minimum bounding box of a representation.
    __CADEX_EXPORT static void ComputeMin (const ModelData_Part& thePart,
        ModelData_Box& theBox,
        ModelData_Transformation& theOutTransformation,
        bool theForcedFlush = true);

    //! Returns a minimum bounding box of a representation.
    __CADEX_EXPORT static void ComputeMin (const ModelData_Representation& theRep,
        ModelData_Box& theBox,
        ModelData_Transformation& theOutTransformation);

    //! Returns a minimum bounding box of a shape.
    __CADEX_EXPORT static void ComputeMin (const ModelData_Shape& theShape,
        ModelData_Box& theBox,
        ModelData_Transformation& theOutTransformation);

    //! Returns a minimum bounding box of a shape.
    __CADEX_EXPORT static void ComputeMin (const ModelData_Shape& theShape,
        const ModelData_Transformation& theTransformation,
        ModelData_Box& theBox,
        ModelData_Transformation& theOutTransformation);
#endif
};

}

#endif

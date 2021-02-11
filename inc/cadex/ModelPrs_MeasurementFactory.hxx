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


#ifndef _ModelPrs_MeasurementFactory_HeaderFile
#define _ModelPrs_MeasurementFactory_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION

#include <cadex/Base_PublicObject.hxx>

namespace cadex {
class ModelData_Face;
class ModelData_Shape;
class ModelData_Vertex;
class ModelPrs_Measurement;

namespace internal {
class ModelPrs_MeasurementFactoryImpl;
}

class ModelPrs_MeasurementFactory : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_MeasurementFactoryImpl    ImplType;

    __CADEX_EXPORT ModelPrs_MeasurementFactory();

    __CADEX_EXPORT ModelPrs_Measurement CreateDistance (const ModelData_Shape& theFirstShape,
                                                        const ModelData_Shape& theSecondShape);

    __CADEX_EXPORT ModelPrs_Measurement CreateMinorRadius (const ModelData_Shape& theShape);

    __CADEX_EXPORT ModelPrs_Measurement CreateMajorRadius (const ModelData_Shape& theShape);

    __CADEX_EXPORT ModelPrs_Measurement CreateMinorDiameter(const ModelData_Shape& theShape);

    __CADEX_EXPORT ModelPrs_Measurement CreateMajorDiameter (const ModelData_Shape& theShape);

    __CADEX_EXPORT ModelPrs_Measurement CreateAngle (const ModelData_Face& theFirstFace,
                                                     const ModelData_Face& theSecondFace);

    __CADEX_EXPORT ModelPrs_Measurement CreateAngle (const ModelData_Vertex& theFirstVertex,
                                                     const ModelData_Vertex& theSecondVertex,
                                                     const ModelData_Vertex& theThirdVertex);
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_MeasurementFactory_HeaderFile

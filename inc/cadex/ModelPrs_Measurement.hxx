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


#ifndef _ModelPrs_Measurement_HeaderFile
#define _ModelPrs_Measurement_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION

#include <cadex/Base_AngleUnit.hxx>
#include <cadex/Base_LengthUnit.hxx>
#include <cadex/Base_PublicObject.hxx>
#include <cadex/ModelPrs_MeasurementType.hxx>

namespace cadex {

namespace internal {
class ModelPrs_MeasurementImpl;
}

class ModelPrs_Measurement : public Base_PublicObject
{
public:
    typedef cadex::internal::ModelPrs_MeasurementImpl    ImplType;

    __CADEX_EXPORT ModelPrs_Measurement();

    __CADEX_EXPORT ModelPrs_MeasurementType Type() const;

    __CADEX_EXPORT double Value() const;

    __CADEX_EXPORT Base_LengthUnit LengthUnit() const;
    __CADEX_EXPORT void SetLengthUnit (Base_LengthUnit theLengthUnit);

    __CADEX_EXPORT Base_AngleUnit AngleUnit() const;
    __CADEX_EXPORT void SetAngleUnit (Base_AngleUnit theAngleUnit);

    __CADEX_EXPORT double Size() const;
    __CADEX_EXPORT void SetSize (double theSize);

    __CADEX_EXPORT double SizeOfFlyOut() const;
    __CADEX_EXPORT void SetSizeOfFlyOut (double theSizeOfFlyOut);

private:
    __CADEX_EXPORT ModelPrs_Measurement (ImplType* theImpl);

    friend class ModelPrs_MeasurementFactory;
};

__CADEX_EXPORT bool operator== (const ModelPrs_Measurement& theFirstMeasure,
                                const ModelPrs_Measurement& theSecondMeasure);

}

#endif // __CADEX_PREVIEW_VISUALIZATION

#endif // _ModelPrs_Measurement_HeaderFile

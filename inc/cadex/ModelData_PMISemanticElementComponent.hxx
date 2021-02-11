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


#ifndef _ModelData_PMISemanticElementComponent_HeaderFile
#define _ModelData_PMISemanticElementComponent_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/ModelData_BaseObject.hxx>


namespace cadex {
class ModelData_PMISemanticAttribute;
class ModelData_PMISemanticAttributeVisitor;
class ModelData_PMISemanticElementComponentVisitor;

namespace internal {
class ModelData_PMIDatumComponentImpl;
class ModelData_PMIDimensionComponentImpl;
class ModelData_PMIGeometricToleranceComponentImpl;
class ModelData_PMISemanticElementComponentImpl;
}

class ModelData_PMISemanticElementComponent : public ModelData_BaseObject
{
public:

    __CADEX_EXPORT void AddAttribute (const ModelData_PMISemanticAttribute& theAttribute);
    __CADEX_EXPORT bool HasAttributes() const;
    __CADEX_EXPORT size_t NumberOfAttributes() const;

    __CADEX_EXPORT void Accept (ModelData_PMISemanticAttributeVisitor& theVisitor) const;

    __CADEX_EXPORT void Accept (ModelData_PMISemanticElementComponentVisitor& theVisitor) const;

    class AttributeIterator
    {
    public:
        __CADEX_EXPORT AttributeIterator (const ModelData_PMISemanticElementComponent& theElement);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_PMISemanticAttribute& Next() const;
        __CADEX_EXPORT ModelData_PMISemanticAttribute& Next();
    protected:
        internal::Base_Handle myImpl;
    };
        
protected:

    //! Constructor.
    /*! Creates a null object (see IsNull()).*/
    ModelData_PMISemanticElementComponent() {}

    explicit ModelData_PMISemanticElementComponent (internal::ModelData_PMISemanticElementComponentImpl* theImpl);
};

class ModelData_PMIDimensionComponent : public ModelData_PMISemanticElementComponent
{
public:

    typedef cadex::internal::ModelData_PMIDimensionComponentImpl ImplType;

    enum DimensionType
    {
        Undefined,
        CurveLength,
        Diameter,
        SphericalDiameter,
        Radius,
        SphericalRadius,
        ToroidalMinorDiameter,
        ToroidalMajorDiameter,
        ToroidalMinorRadius,
        ToroidalMajorRadius,
        ToroidalHighMajorDiameter,
        ToroidalLowMajorDiameter,
        ToroidalHighMajorRadius,
        ToroidalLowMajorRadius,
        Thickness
    };

    __CADEX_EXPORT ModelData_PMIDimensionComponent();
    __CADEX_EXPORT explicit ModelData_PMIDimensionComponent (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIDimensionComponent (double theNominalValue);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetNominalValue (double theNominalValue);
    __CADEX_EXPORT double NominalValue() const;

    __CADEX_EXPORT void SetTypeOfDimension (DimensionType theType);
    __CADEX_EXPORT DimensionType TypeOfDimension() const;
};

class ModelData_PMIGeometricToleranceComponent : public ModelData_PMISemanticElementComponent
{
public:

    enum ToleranceZoneFormType
    {
        Undefined,
        CylindricalOrCircular,
        Spherical,
        WithinACircle,
        BetweenTwoConcentricCircles,
        BetweenTwoEquidistantCurves,
        WithinACylinder,
        BetweenTwoCoaxialCylinders,
        BetweenTwoEquidistantSurfaces,
        NonUniform
    };

    typedef cadex::internal::ModelData_PMIGeometricToleranceComponentImpl ImplType;

    __CADEX_EXPORT ModelData_PMIGeometricToleranceComponent();
    __CADEX_EXPORT explicit ModelData_PMIGeometricToleranceComponent (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIGeometricToleranceComponent (double theMagnitude);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetMagnitude (double theMagnitude);
    __CADEX_EXPORT double Magnitude() const;

    __CADEX_EXPORT void SetToleranceZoneForm (ToleranceZoneFormType theType);
    __CADEX_EXPORT ToleranceZoneFormType ToleranceZoneForm() const;
};

class ModelData_PMIDatumComponent : public ModelData_PMISemanticElementComponent
{
public:

    typedef cadex::internal::ModelData_PMIDatumComponentImpl ImplType;

    __CADEX_EXPORT ModelData_PMIDatumComponent();
    __CADEX_EXPORT explicit ModelData_PMIDatumComponent (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIDatumComponent (const Base_UTF16String& theLabel);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetLabel (const Base_UTF16String& theLabel);
    __CADEX_EXPORT const Base_UTF16String& Label() const;
};
}

#endif // __CADEX_PREVIEW_PMI
#endif


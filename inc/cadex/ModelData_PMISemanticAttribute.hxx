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


#ifndef _ModelData_PMISemanticAttribute_HeaderFile
#define _ModelData_PMISemanticAttribute_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_PMI

#include <cadex/Base_AngleUnit.hxx>
#include <cadex/Base_LengthUnit.hxx>
#include <cadex/ModelData_BaseObject.hxx>


namespace cadex {
class ModelData_PMISemanticAttributeVisitor;

namespace internal {
class ModelData_PMIAngleUnitAttributeImpl;
class ModelData_PMIDatumAttributeImpl;
class ModelData_PMIDatumRefAttributeImpl;
class ModelData_PMIDatumRefCompartmentAttributeImpl;
class ModelData_PMIDatumTargetAttributeImpl;
class ModelData_PMIDefinedAreaUnitAttributeImpl;
class ModelData_PMIDefinedUnitAttributeImpl;
class ModelData_PMIDimensionAttributeImpl;
class ModelData_PMIDisplacementAttributeImpl;
class ModelData_PMIGeometricAttributeImpl;
class ModelData_PMILengthUnitAttributeImpl;
class ModelData_PMILimitsAndFitsAttributeImpl;
class ModelData_PMIMaximumValueAttributeImpl;
class ModelData_PMIModifierAttributeImpl;
class ModelData_PMIModifierWithValueAttributeImpl;
class ModelData_PMIPlusMinusBoundsAttributeImpl;
class ModelData_PMIQualifierAttributeImpl;
class ModelData_PMIRangeAttributeImpl;
class ModelData_PMISemanticAttributeImpl;
}

class ModelData_PMISemanticAttribute : public ModelData_BaseObject
{
public:

    __CADEX_EXPORT void Accept (ModelData_PMISemanticAttributeVisitor& theVisitor) const;

protected:

    //! Constructor.
    /*! Creates a null object (see IsNull()).*/
    ModelData_PMISemanticAttribute() {}

    ModelData_PMISemanticAttribute (internal::ModelData_PMISemanticAttributeImpl* theImpl);
};

class ModelData_PMIModifierAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIModifierAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIModifierAttribute();
    __CADEX_EXPORT explicit ModelData_PMIModifierAttribute (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIModifierAttribute (const Base_UTF16String& theModifier);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetModifier (const Base_UTF16String& theModifier);
    __CADEX_EXPORT const Base_UTF16String& Modifier() const;
};

class ModelData_PMIModifierWithValueAttribute : public ModelData_PMIModifierAttribute
{
public:

    typedef cadex::internal::ModelData_PMIModifierWithValueAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIModifierWithValueAttribute();
    __CADEX_EXPORT explicit ModelData_PMIModifierWithValueAttribute (ImplType* theImpl);
    __CADEX_EXPORT ModelData_PMIModifierWithValueAttribute (const Base_UTF16String& theModifier, double theValue);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetValue (double theValue);
    __CADEX_EXPORT double Value() const;
};

class ModelData_PMIQualifierAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIQualifierAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIQualifierAttribute();
    __CADEX_EXPORT explicit ModelData_PMIQualifierAttribute (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIQualifierAttribute (const Base_UTF16String& theQualifier);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetQualifier (const Base_UTF16String& theQualifier);
    __CADEX_EXPORT const Base_UTF16String& Qualifier() const;
};

class ModelData_PMIPlusMinusBoundsAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIPlusMinusBoundsAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIPlusMinusBoundsAttribute();
    __CADEX_EXPORT explicit ModelData_PMIPlusMinusBoundsAttribute (ImplType* theImpl);
    __CADEX_EXPORT ModelData_PMIPlusMinusBoundsAttribute (double theLowerBound, double theUpperBound);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetUpperBound (double theValue);
    __CADEX_EXPORT double UpperBound() const;

    __CADEX_EXPORT void SetLowerBound (double theValue);
    __CADEX_EXPORT double LowerBound() const;
};

class ModelData_PMIRangeAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIRangeAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIRangeAttribute();
    __CADEX_EXPORT explicit ModelData_PMIRangeAttribute (ImplType* theImpl);
    __CADEX_EXPORT ModelData_PMIRangeAttribute (double theLowerLimit, double theUpperLimit);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetUpperLimit (double theValue);
    __CADEX_EXPORT double UpperLimit() const;

    __CADEX_EXPORT void SetLowerLimit (double theValue);
    __CADEX_EXPORT double LowerLimit() const;
};

class ModelData_PMILimitsAndFitsAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMILimitsAndFitsAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMILimitsAndFitsAttribute();
    __CADEX_EXPORT explicit ModelData_PMILimitsAndFitsAttribute (ImplType* theImpl);
    __CADEX_EXPORT ModelData_PMILimitsAndFitsAttribute (const Base_UTF16String& theType,
        const Base_UTF16String& theValue);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetType (const Base_UTF16String& theType);
    __CADEX_EXPORT const Base_UTF16String& Type() const;

    __CADEX_EXPORT void SetValue (const Base_UTF16String& theValue);
    __CADEX_EXPORT const Base_UTF16String& Value() const;
};

class ModelData_PMIDatumTargetAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIDatumTargetAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIDatumTargetAttribute();
    __CADEX_EXPORT explicit ModelData_PMIDatumTargetAttribute (ImplType* theImpl);
    __CADEX_EXPORT ModelData_PMIDatumTargetAttribute (size_t theIndex, const Base_UTF16String& theDescription);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetIndex (size_t theIndex);
    __CADEX_EXPORT size_t Index() const;

    __CADEX_EXPORT void SetDescription (const Base_UTF16String& theValue);
    __CADEX_EXPORT const Base_UTF16String& Description() const;
};

class ModelData_PMIDatumRefAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIDatumRefAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIDatumRefAttribute();
    __CADEX_EXPORT explicit ModelData_PMIDatumRefAttribute (ImplType* theImpl);
    __CADEX_EXPORT ModelData_PMIDatumRefAttribute (size_t thePrecedence, const Base_UTF16String& theTargetLabel);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetPrecedence (size_t thePrecedence);
    __CADEX_EXPORT size_t Precedence() const;

    __CADEX_EXPORT void SetTargetLabel (const Base_UTF16String& theTargetLabel);
    __CADEX_EXPORT const Base_UTF16String& TargetLabel() const;
};

class ModelData_PMIDatumRefCompartmentAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIDatumRefCompartmentAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIDatumRefCompartmentAttribute();
    __CADEX_EXPORT explicit ModelData_PMIDatumRefCompartmentAttribute (ImplType* theImpl);
    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void AddReference (const ModelData_PMIDatumRefAttribute& theReference);
    __CADEX_EXPORT void AddReference (const ModelData_PMIDatumRefCompartmentAttribute& theReference);
    __CADEX_EXPORT size_t NumberOfReferences() const;
    __CADEX_EXPORT const ModelData_PMISemanticAttribute& Reference (size_t theIndex) const;

    __CADEX_EXPORT void AddModifierAttribute (const ModelData_PMIModifierAttribute& theAttribute);
    __CADEX_EXPORT size_t NumberOfModifierAttributes() const;
    __CADEX_EXPORT const ModelData_PMIModifierAttribute& ModifierAttribute (size_t theIndex) const;
};

class ModelData_PMIMaximumValueAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIMaximumValueAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIMaximumValueAttribute();
    __CADEX_EXPORT explicit ModelData_PMIMaximumValueAttribute (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIMaximumValueAttribute (double theMaxValue);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetMaxValue (double theValue);
    __CADEX_EXPORT double MaxValue() const;
};

class ModelData_PMIDisplacementAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIDisplacementAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIDisplacementAttribute();
    __CADEX_EXPORT explicit ModelData_PMIDisplacementAttribute (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIDisplacementAttribute (double theDisplacement);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetDisplacement (double theDisplacement);
    __CADEX_EXPORT double Displacement() const;
};

class ModelData_PMILengthUnitAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMILengthUnitAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMILengthUnitAttribute();
    __CADEX_EXPORT explicit ModelData_PMILengthUnitAttribute (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMILengthUnitAttribute (Base_LengthUnit theUnit);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetUnit (Base_LengthUnit theUnit);
    __CADEX_EXPORT Base_LengthUnit Unit() const;
};

class ModelData_PMIAngleUnitAttribute : public ModelData_PMISemanticAttribute
{
public:

    typedef cadex::internal::ModelData_PMIAngleUnitAttributeImpl ImplType;

    __CADEX_EXPORT ModelData_PMIAngleUnitAttribute();
    __CADEX_EXPORT explicit ModelData_PMIAngleUnitAttribute (ImplType* theImpl);
    __CADEX_EXPORT explicit ModelData_PMIAngleUnitAttribute (Base_AngleUnit theUnit);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT void SetUnit (Base_AngleUnit theUnit);
    __CADEX_EXPORT Base_AngleUnit Unit() const;
};

}

#endif // __CADEX_PREVIEW_PMI
#endif

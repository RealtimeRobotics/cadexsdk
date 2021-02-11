// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// You may use this file under the terms of the BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// ****************************************************************************

#define __CADEX_PREVIEW_PMI 1

#include <cadex/Base_String.hxx>
#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelData_Assembly.hxx>
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_IndexedTriangleSet.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_SceneGraphElement.hxx>
#include <cadex/ModelData_PMIData.hxx>
#include <cadex/ModelData_PMISemanticAttribute.hxx>
#include <cadex/ModelData_PMISemanticAttributeVisitor.hxx>
#include <cadex/ModelData_PMISemanticElement.hxx>
#include <cadex/ModelData_PMISemanticElementComponent.hxx>
#include <cadex/ModelData_PMISemanticElementComponentVisitor.hxx>
#include <cadex/ModelData_PMIGraphicalElement.hxx>
#include <cadex/ModelData_PMIGraphicalElementComponent.hxx>
#include <cadex/ModelData_PMIGraphicalElementComponentVisitor.hxx>
#include <cadex/ModelData_PMIOutline.hxx>
#include <cadex/ModelData_PMIOutlineVisitor.hxx>
#include <cadex/ModelData_PMITable.hxx>
#include <cadex/ModelData_PolyLineSet.hxx>
#include <cadex/ModelData_PolyLine2dSet.hxx>
#include <cadex/STEP_Reader.hxx>
#include <cadex/STEP_ReaderParameters.hxx>
#include <iostream>

#include "../../cadex_license.cxx"

using namespace std;
using namespace cadex;

class TabulatedOutput
{
public:

    template<typename T>
    std::ostream& operator << (const T& theObject)
    {
        PrintTabulation();
        cout << theObject;
        return cout;
    }

    void IncreaseIndent() { ++myNestingLevel; }
    void DecreaseIndent() { --myNestingLevel; }

protected:
    void PrintTabulation()
    {
        if (myNestingLevel <= 0) {
            return;
        }
        // Emulate tabulation like tree.
        for (int i = 0; i < myNestingLevel - 1; i++) {
            if (i < 2 || i == 3) {
                cout << "|  ";
            } else {
                cout << "   ";
            }
        }
        cout << "|__";
        if (myNestingLevel > 3) {
            cout << " ";
        }
    }

    int myNestingLevel = 0;
};

static TabulatedOutput theOutput;


class PMISemanticAttributeVisitor: public ModelData_PMISemanticAttributeVisitor
{
public:
    void operator() (const ModelData_PMIModifierAttribute& theAttribute) override
    {
        theOutput << "Modifier: " << theAttribute.Modifier() << endl;
    }
    void operator() (const ModelData_PMIModifierWithValueAttribute& theAttribute) override
    {
        theOutput << "ModifierWithValue: modifier=" << theAttribute.Modifier() << ", value=" << theAttribute.Value() << endl;
    }
    void operator() (const ModelData_PMIQualifierAttribute& theAttribute) override
    {
        theOutput << "Qualifier: " << theAttribute.Qualifier() << endl;
    }
    void operator() (const ModelData_PMIPlusMinusBoundsAttribute& theAttribute) override
    {
        theOutput << "PlusMinusBounds: (" << theAttribute.LowerBound() << ", " << theAttribute.UpperBound() << ")" << endl;
    }
    void operator() (const ModelData_PMIRangeAttribute& theAttribute) override
    {
        theOutput << "Range: (" << theAttribute.LowerLimit() << ", " << theAttribute.UpperLimit() << ")" << endl;
    }
    void operator() (const ModelData_PMILimitsAndFitsAttribute& theAttribute) override
    {
        theOutput << "LimitsAndFits: value=" << theAttribute.Value() << ", type=" << theAttribute.Type() << endl;
    }
    void operator() (const ModelData_PMIDatumTargetAttribute& theAttribute) override
    {
        theOutput << "DatumTarget: index=" << theAttribute.Index() << ", description=" << theAttribute.Description() << endl;
    }
    void operator() (const ModelData_PMIDatumRefAttribute& theAttribute) override
    {
        theOutput << "DatumRef: precedence=" << theAttribute.Precedence() << ", targetLabel=" << theAttribute.TargetLabel() << endl;
    }
    void operator() (const ModelData_PMIDatumRefCompartmentAttribute& theAttribute) override
    {
        theOutput << "DatumRefCompartment:" << endl;

        theOutput.IncreaseIndent();

        const size_t aNumberOfReferences = theAttribute.NumberOfReferences();
        if (aNumberOfReferences > 0) {
            theOutput << "References:" << endl;
            theOutput.IncreaseIndent();
            for (size_t i = 0; i < aNumberOfReferences; i++) {
                theAttribute.Reference (i).Accept (*this);
            }
            theOutput.DecreaseIndent();
        }

        const size_t aNumberOfModifierAttributes = theAttribute.NumberOfModifierAttributes();
        if (aNumberOfModifierAttributes > 0) {
            theOutput << "Modifiers:" << endl;
            theOutput.IncreaseIndent();
            for (size_t i = 0; i < aNumberOfModifierAttributes; i++) {
                theAttribute.ModifierAttribute (i).Accept (*this);
            }
            theOutput.DecreaseIndent();
        }

        theOutput.DecreaseIndent();
    }
    void operator() (const ModelData_PMIMaximumValueAttribute& theAttribute) override
    {
        theOutput << "MaximumValue: " << theAttribute.MaxValue() << endl;
    }
    void operator() (const ModelData_PMIDisplacementAttribute& theAttribute) override
    {
        theOutput << "Displacement: " << theAttribute.Displacement() << endl;
    }
    void operator() (const ModelData_PMILengthUnitAttribute& theAttribute) override
    {
        theOutput << "LengthUnit: " << static_cast<int>(theAttribute.Unit()) << endl;
    }
    void operator() (const ModelData_PMIAngleUnitAttribute& theAttribute) override
    {
        theOutput << "AngleUnit: " << static_cast<int>(theAttribute.Unit()) << endl;
    }
};

class PMISemanticVisitor : public ModelData_PMISemanticElementComponentVisitor
{
public:
    void operator() (const ModelData_PMIDatumComponent &theComponent) override
    {
        theOutput << "Datum" << endl;
        theOutput.IncreaseIndent();
        theOutput << "Label: " << theComponent.Label() << endl;
        printAttributes (theComponent);
        theOutput.DecreaseIndent();
    }
    void operator() (const ModelData_PMIDimensionComponent &theComponent) override
    {
        theOutput << "Dimension" << endl;
        theOutput.IncreaseIndent();
        theOutput << "Nominal Value: " << theComponent.NominalValue() << endl;
        theOutput << "Type of dimension: " << static_cast <int> (theComponent.TypeOfDimension()) << endl;
        printAttributes (theComponent);
        theOutput.DecreaseIndent();
    }
    void operator() (const ModelData_PMIGeometricToleranceComponent &theComponent) override
    {
        theOutput << "Geometric tolerance" << endl;
        theOutput.IncreaseIndent();
        theOutput << "Magnitude: " << theComponent.Magnitude() << endl;
        theOutput << "Tolerance zone form: " << static_cast <int> (theComponent.ToleranceZoneForm()) << endl;
        printAttributes(theComponent);
        theOutput.DecreaseIndent();
    }
    void printAttributes (const ModelData_PMISemanticElementComponent& theComponent)
    {
        if (theComponent.HasAttributes()) {
            PMISemanticAttributeVisitor aVisitor;
            theComponent.Accept (aVisitor);
        }
    }
};

class PMIOutlineVisitor : public ModelData_PMIOutlineVisitor
{
public:
    void operator() (const ModelData_PMIPolyOutline& theOutline) override
    {
        theOutput << "PolyLine set [" << theOutline.LineSet().NumberOfPolyLines() << " polylines]" << endl;
    }
    void operator() (const ModelData_PMIPoly2dOutline& theOutline) override
    {
        theOutput << "PolyLine2d set [" << theOutline.LineSet().NumberOfPolyLines() << " polylines]" << endl;
    }
    void operator() (const ModelData_PMICurveOutline& theOutline) override
    {
        theOutput << "Curve set [" << theOutline.NumberOfCurves() << " curves]" << endl;
    }
    void operator() (const ModelData_PMICurve2dOutline& theOutline) override
    {
        theOutput << "Curve2d set [" << theOutline.NumberOfCurves() << " curves]" << endl;
    }
    bool VisitEnter (const ModelData_PMICompositeOutline& theOutline) override
    {
        theOutput << "Outline set:" << endl;
        theOutput.IncreaseIndent();
        return true;
    }
    void VisitLeave (const ModelData_PMICompositeOutline& theOutline) override
    {
        theOutput.DecreaseIndent();
    }
};

class PMIGraphicalVisitor : public ModelData_PMIGraphicalElementComponentVisitor
{
public:
    void operator() (const ModelData_PMIOutlinedComponent& theComponent) override
    {
        theOutput << "Outline" << endl;
        theOutput.IncreaseIndent();
        PMIOutlineVisitor aVisitor;
        theComponent.Outline().Accept (aVisitor);
        theOutput.DecreaseIndent();
    }
    void operator() (const ModelData_PMITextComponent& theComponent) override
    {
        theOutput << "Text [" << theComponent.Text() << "]" << endl;
    }
    void operator() (const ModelData_PMITriangulatedComponent& theComponent) override
    {
        theOutput << "Triangulation [" << theComponent.TriangleSet().NumberOfFaces() << " triangles]" << endl;
    }
};

class SceneGraphVisitor : public ModelData_Model::ElementVisitor
{
public:
    void operator() (const ModelData_Part& thePart) override
    {
        PrintName ("Part", thePart.Name());
        ExplorePMI (thePart);
    }
    bool VisitEnter (const ModelData_Instance& theInstance) override
    {
        theOutput.IncreaseIndent();
        PrintName ("Instance", theInstance.Name());
        ExplorePMI (theInstance);
        return true;
    }
    bool VisitEnter (const ModelData_Assembly& theAssembly) override
    {
        theOutput.IncreaseIndent();
        PrintName ("Assembly", theAssembly.Name());
        ExplorePMI (theAssembly);
        return true;
    }
    void VisitLeave (const ModelData_Instance& theInstance) override
    {
        theOutput.DecreaseIndent();
    }
    void VisitLeave (const ModelData_Assembly& theAssembly) override
    {
        theOutput.DecreaseIndent();
    }

private:
    void ExplorePMI (ModelData_SceneGraphElement theSGE)
    {
        ModelData_PMITable aPMITable = theSGE.PMI();
        if (aPMITable) {
            theOutput << "PMI Table:" << endl;
            theOutput.IncreaseIndent();

            ModelData_PMITable::PMIDataIterator aDataIt (aPMITable);
            while (aDataIt.HasNext()) {
                ModelData_PMIData aData = aDataIt.Next();
                theOutput << "PMI Data: " << aData.Name() << endl;

                theOutput.IncreaseIndent();

                ModelData_PMISemanticElement aSemanticElement = aData.SemanticElement();
                if (aSemanticElement) {
                    theOutput << "Semantic element:" << endl;
                    theOutput.IncreaseIndent();
                    PMISemanticVisitor aVisitor;
                    aSemanticElement.Accept (aVisitor);
                    theOutput.DecreaseIndent();
                }

                ModelData_PMIGraphicalElement aGraphicalElement = aData.GraphicalElement();
                if (aGraphicalElement) {
                    theOutput << "Graphical element:" << endl;
                    theOutput.IncreaseIndent();
                    PMIGraphicalVisitor aVisitor;
                    aGraphicalElement.Accept (aVisitor);
                    theOutput.DecreaseIndent();
                }

                theOutput.DecreaseIndent();
            }
            theOutput.DecreaseIndent();
        }
    }

    void PrintName (string theSGElement, Base_UTF16String theName)
    {
        if (!theName.IsEmpty()) {
            theOutput << theSGElement << ": " << theName << endl;
        } else {
            theOutput << theSGElement << ": <noname>" << endl;
        }
    }
};


int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cs)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>, where:" << endl;
        cerr << "    <input_file>  is a name of the STEP file to Read() model from" << endl;
        return 1;
    }

    const char* aSource = argv[1];

    ModelData_Model aModel;
    STEP_Reader aReader;
    STEP_ReaderParameters aParams;
    aParams.ReadPMI() = true;
    aReader.Parameters() = aParams;

    if (!aReader.ReadFile (aSource)) {
        cout << "Failed to read the file " << aSource << endl;
        return 1;
    }

    // Converting into inner format
    if (!aReader.Transfer (aModel)) {
        cout << "Failed to transfer the file into inner format." << endl;
        return 1;
    }

    // Create a PMI visitor
    SceneGraphVisitor aVisitor;
    aModel.Accept (aVisitor);

    return 0;
}

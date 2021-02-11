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

import cadex.*;

public class pmi {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExSTEP");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(1);
        }
    }

    public static void main(String[] args) {
        String aKey = LicenseKey.Value();

        // Activate the license (aKey must be defined in LicenseKey.java)
        if (!LicenseManager.Activate(aKey)) {
            System.out.println("Failed to activate CAD Exchanger license.");
            System.exit(1);
        }

        if (args.length != 1) {
            System.out.println("Usage: " + " <input_file>, where:");
            System.out.println("    <input_file>  is a name of the STEP file to be read");
            System.exit(1);
        }

        String aSource = args[0];

        ModelData_Model aModel = new ModelData_Model();
        STEP_Reader aReader = new STEP_Reader();
        STEP_ReaderParameters aParams = new STEP_ReaderParameters();
        aParams.SetReadPMI(true);
        aReader.SetParameters(aParams);

        if (!aReader.ReadFile(new Base_UTF16String(aSource))) {
            System.out.println("Failed to read the file");
            System.exit(1);
        }

        if (!aReader.Transfer(aModel)) {
            System.out.println("Failed to transfer the model");
            System.exit(1);
        }

        SceneGraphVisitor aVisitor = new SceneGraphVisitor();
        aModel.Accept(aVisitor);
    }
}

class TabulatedOutput {
    public static void Println(Object theObject) {
        PrintTabulation();
        System.out.println(theObject);
    }

    public static void IncreaseIndent() {
        ++myNestingLevel;
    }

    public static void DecreaseIndent() {
        --myNestingLevel;
    }

    private static void PrintTabulation() {
        if (myNestingLevel <= 0) {
            return;
        }
        // Emulate tabulation like tree.
        for (int i = 0; i < myNestingLevel - 1; i++) {
            if (i < 2 || i == 3) {
                System.out.print("|  ");
            } else {
                System.out.print("   ");
            }
        }
        System.out.print("|__");
        if (myNestingLevel > 3) {
            System.out.print(" ");
        }
    }

    private static int myNestingLevel = 0;
}

class SceneGraphVisitor extends ModelData_Model.ElementVisitor {
    @Override
    public void Apply(ModelData_Part thePart) {
        PrintName("Part", thePart.Name());
        ExplorePMI(thePart);
    }

    @Override
    public boolean VisitEnter(ModelData_Instance theInstance) {
        TabulatedOutput.IncreaseIndent();
        PrintName("Instance", theInstance.Name());
        ExplorePMI(theInstance);
        return true;
    }

    @Override
    public boolean VisitEnter(ModelData_Assembly theAssembly) {
        TabulatedOutput.IncreaseIndent();
        PrintName("Assembly", theAssembly.Name());
        ExplorePMI(theAssembly);
        return true;
    }

    @Override
    public void VisitLeave(ModelData_Instance theInstance) {
        TabulatedOutput.DecreaseIndent();
    }

    @Override
    public void VisitLeave(ModelData_Assembly theAssembly) {
        TabulatedOutput.DecreaseIndent();
    }

    private void ExplorePMI(ModelData_SceneGraphElement theSGE) {
        ModelData_PMITable aPMITable = theSGE.PMI();
        if (aPMITable != null) {
            TabulatedOutput.Println("PMI Table:");

            TabulatedOutput.IncreaseIndent();

            ModelData_PMITable.PMIDataIterator aDataIt = new ModelData_PMITable.PMIDataIterator(aPMITable);
            while (aDataIt.HasNext()) {
                ModelData_PMIData aData = aDataIt.Next();
                TabulatedOutput.Println("PMI Data: " + aData.Name());

                TabulatedOutput.IncreaseIndent();

                ModelData_PMISemanticElement aSemanticElement = aData.SemanticElement();
                if (aSemanticElement != null) {
                    TabulatedOutput.Println("Semantic element:");
                    TabulatedOutput.IncreaseIndent();
                    PMISemanticVisitor aVisitor = new PMISemanticVisitor();
                    aSemanticElement.Accept(aVisitor);
                    TabulatedOutput.DecreaseIndent();
                }

                ModelData_PMIGraphicalElement aGraphicalElement = aData.GraphicalElement();
                if (aGraphicalElement != null) {
                    TabulatedOutput.Println("Graphical element:");
                    TabulatedOutput.IncreaseIndent();
                    PMIGraphicalVisitor aVisitor = new PMIGraphicalVisitor();
                    aGraphicalElement.Accept(aVisitor);
                    TabulatedOutput.DecreaseIndent();
                }

                TabulatedOutput.DecreaseIndent();
            }
            TabulatedOutput.DecreaseIndent();
        }
    }

    private void PrintName(String theSGElement, Base_UTF16String theName) {
        if (!theName.IsEmpty()) {
            TabulatedOutput.Println(theSGElement + ": " + theName);
        } else {
            TabulatedOutput.Println(theSGElement + ": <noname>");
        }
    }
}

class PMISemanticVisitor extends ModelData_PMISemanticElementComponentVisitor {
    @Override
    public void Apply(ModelData_PMIDatumComponent theComponent) {
        TabulatedOutput.Println("Datum");
        TabulatedOutput.IncreaseIndent();
        TabulatedOutput.Println("Label: " + theComponent.Label());
        printAttributes(theComponent);
        TabulatedOutput.DecreaseIndent();
    }

    @Override
    public void Apply(ModelData_PMIDimensionComponent theComponent) {
        TabulatedOutput.Println("Dimension");
        TabulatedOutput.IncreaseIndent();
        TabulatedOutput.Println("Nominal Value: " + theComponent.NominalValue());
        TabulatedOutput.Println("Type of dimension: " + theComponent.TypeOfDimension());
        printAttributes(theComponent);
        TabulatedOutput.DecreaseIndent();
    }

    @Override
    public void Apply(ModelData_PMIGeometricToleranceComponent theComponent) {
        TabulatedOutput.Println("Geometric tolerance");
        TabulatedOutput.IncreaseIndent();
        TabulatedOutput.Println("Magnitude: " + theComponent.Magnitude());
        TabulatedOutput.Println("Tolerance zone form: " + theComponent.ToleranceZoneForm());
        printAttributes(theComponent);
        TabulatedOutput.DecreaseIndent();
    }

    void printAttributes(ModelData_PMISemanticElementComponent theComponent) {
        if (theComponent.HasAttributes()) {
            PMISemanticAttributeVisitor aVisitor = new PMISemanticAttributeVisitor();
            theComponent.Accept(aVisitor);
        }
    }
}

class PMIOutlineVisitor extends ModelData_PMIOutlineVisitor {
    @Override
    public void Apply(ModelData_PMIPolyOutline theOutline) {
        TabulatedOutput.Println("PolyLine set [" + theOutline.LineSet().NumberOfPolyLines() + " polylines]");
    }

    @Override
    public void Apply(ModelData_PMIPoly2dOutline theOutline) {
        TabulatedOutput.Println("PolyLine2d set [" + theOutline.LineSet().NumberOfPolyLines() + " polylines]");
    }

    @Override
    public void Apply(ModelData_PMICurveOutline theOutline) {
        TabulatedOutput.Println("Curve set [" + theOutline.NumberOfCurves() + " curves]");
    }

    @Override
    public void Apply(ModelData_PMICurve2dOutline theOutline) {
        TabulatedOutput.Println("Curve2d set [" + theOutline.NumberOfCurves() + " curves]");
    }

    @Override
    public boolean VisitEnter(ModelData_PMICompositeOutline theOutline) {
        TabulatedOutput.Println("Outline set:");
        TabulatedOutput.IncreaseIndent();
        return true;
    }

    @Override
    public void VisitLeave(ModelData_PMICompositeOutline theOutline) {
        TabulatedOutput.DecreaseIndent();
    }
}
;

class PMIGraphicalVisitor extends ModelData_PMIGraphicalElementComponentVisitor {
    @Override
    public void Apply(ModelData_PMIOutlinedComponent theComponent) {
        TabulatedOutput.Println("Outline");
        TabulatedOutput.IncreaseIndent();
        PMIOutlineVisitor aVisitor = new PMIOutlineVisitor();
        theComponent.Outline().Accept(aVisitor);
        TabulatedOutput.DecreaseIndent();
    }

    @Override
    public void Apply(ModelData_PMITextComponent theComponent) {
        TabulatedOutput.Println("Text [" + theComponent.Text() + "]");
    }

    @Override
    public void Apply(ModelData_PMITriangulatedComponent theComponent) {
        TabulatedOutput.Println("Triangulation [" + theComponent.TriangleSet().NumberOfFaces() + " triangles]");
    }
}
;

class PMISemanticAttributeVisitor extends ModelData_PMISemanticAttributeVisitor {
    @Override
    public void Apply(ModelData_PMIModifierAttribute theAttribute) {
        TabulatedOutput.Println("Modifier: " + theAttribute.Modifier());
    }

    @Override
    public void Apply(ModelData_PMIModifierWithValueAttribute theAttribute) {
        TabulatedOutput.Println("ModifierWithValue: modifier=" + theAttribute.Modifier() + ", value=" + theAttribute.Value());
    }

    @Override
    public void Apply(ModelData_PMIQualifierAttribute theAttribute) {
        TabulatedOutput.Println("Qualifier: " + theAttribute.Qualifier());
    }

    @Override
    public void Apply(ModelData_PMIPlusMinusBoundsAttribute theAttribute) {
        TabulatedOutput.Println("PlusMinusBounds: (" + theAttribute.LowerBound() + ", " + theAttribute.UpperBound() + ")");
    }

    @Override
    public void Apply(ModelData_PMIRangeAttribute theAttribute) {
        TabulatedOutput.Println("Range: [" + theAttribute.LowerLimit() + ", " + theAttribute.UpperLimit() + "]");
    }

    @Override
    public void Apply(ModelData_PMILimitsAndFitsAttribute theAttribute) {
        TabulatedOutput.Println("LimitsAndFits: value=" + theAttribute.Value() + ", type=" + theAttribute.Type());
    }

    @Override
    public void Apply(ModelData_PMIDatumTargetAttribute theAttribute) {
        TabulatedOutput.Println("DatumTarget: index=" + theAttribute.Index() + ", description=" + theAttribute.Description());
    }

    @Override
    public void Apply(ModelData_PMIDatumRefAttribute theAttribute) {
        TabulatedOutput.Println("DatumRef: precedence=" + theAttribute.Precedence() + ", targetLabel=" + theAttribute.TargetLabel());
    }

    @Override
    public void Apply(ModelData_PMIDatumRefCompartmentAttribute theAttribute) {
        TabulatedOutput.Println("DatumRefCompartment:");

        TabulatedOutput.IncreaseIndent();

        long aNumberOfReferences = theAttribute.NumberOfReferences();
        if (aNumberOfReferences > 0) {
            TabulatedOutput.Println("References:");
            TabulatedOutput.IncreaseIndent();
            for (long i = 0; i < aNumberOfReferences; i++) {
                theAttribute.Reference(i).Accept(this);
            }
            TabulatedOutput.DecreaseIndent();
        }

        long aNumberOfModifierAttributes = theAttribute.NumberOfModifierAttributes();
        if (aNumberOfModifierAttributes > 0) {
            TabulatedOutput.Println("Modifiers:");
            TabulatedOutput.IncreaseIndent();
            for (long i = 0; i < aNumberOfModifierAttributes; i++) {
                theAttribute.ModifierAttribute(i).Accept(this);
            }
            TabulatedOutput.DecreaseIndent();
        }

        TabulatedOutput.DecreaseIndent();
    }

    @Override
    public void Apply(ModelData_PMIMaximumValueAttribute theAttribute) {
        TabulatedOutput.Println("MaximumValue: " + theAttribute.MaxValue());
    }

    @Override
    public void Apply(ModelData_PMIDisplacementAttribute theAttribute) {
        TabulatedOutput.Println("Displacement: " + theAttribute.Displacement());
    }

    @Override
    public void Apply(ModelData_PMILengthUnitAttribute theAttribute) {
        TabulatedOutput.Println("LengthUnit: " + theAttribute.Unit());
    }

    @Override
    public void Apply(ModelData_PMIAngleUnitAttribute theAttribute) {
        TabulatedOutput.Println("AngleUnit: " + theAttribute.Unit());
    }
}
;

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


using cadex;
using System;
using System.Runtime.InteropServices;

namespace pmi
{
    class Program
    {
        // For more information see https://stackoverflow.com/questions/8836093/how-can-i-specify-a-dllimport-path-at-runtime
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool SetDllDirectory(string lpPathName);

        static int Main(string[] args)
        {
            // Add runtime path to CAD Exchanger libraries (e.g. compiled with Visual Studio 2015)
            SetDllDirectory("../../../../../../win64/vc14.1/bin");

            string aKey = LicenseKey.Value();

            // Activate the license (aKey must be defined in cadex_license.cs)
            if (!LicenseManager.Activate(aKey))
            {
                Console.WriteLine("Failed to activate CAD Exchanger license.");
                return 1;
            }

            if (args.Length != 1)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the STEP file to be read");
                return 1;
            }

            string aSource = args[0];

            ModelData_Model aModel = new ModelData_Model();
            STEP_Reader aReader = new STEP_Reader();
            STEP_ReaderParameters aParams = new STEP_ReaderParameters();
            aParams.SetReadPMI(true);
            aReader.SetParameters(aParams);

            // Reading the file
            if (!aReader.ReadFile(new Base_UTF16String(aSource)))
            {
                Console.WriteLine("Failed to read the file ", aSource);
                return 1;
            }

            // Converting into inner format
            if (!aReader.Transfer(aModel))
            {
                Console.WriteLine("Failed to transfer the file into inner format.");
                return 1;
            }

            // Create a PMI visitor
            SceneGraphVisitor aVisitor = new SceneGraphVisitor();
            aModel.Accept(aVisitor);

            return 0;
        }
    }

    class TabulatedOutput
    {
        public static void WriteLine(Object theObject)
        {
            PrintTabulation();
            Console.WriteLine(theObject);
        }

        public static void IncreaseIndent() { ++myNestingLevel; }
        public static void DecreaseIndent() { --myNestingLevel; }

        private static void PrintTabulation()
        {
            if (myNestingLevel <= 0)
            {
                return;
            }
            // Emulate tabulation like tree.
            for (int i = 0; i < myNestingLevel - 1; i++)
            {
                if (i < 2 || i == 3)
                {
                    Console.Write("|  ");
                }
                else
                {
                    Console.Write("   ");
                }
            }
            Console.Write("|__");
            if (myNestingLevel > 3)
            {
                Console.Write(" ");
            }
        }
        private static int myNestingLevel = 0;
    }

    class SceneGraphVisitor : ModelData_Model.ElementVisitor
    {
        public override void Apply(ModelData_Part thePart)
        {
            PrintName("Part", thePart.Name());
            ExplorePMI(thePart);
        }

        public override bool VisitEnter(ModelData_Instance theInstance)
        {
            TabulatedOutput.IncreaseIndent();
            PrintName("Instance", theInstance.Name());
            ExplorePMI(theInstance);
            return true;
        }

        public override bool VisitEnter(ModelData_Assembly theAssembly)
        {
            TabulatedOutput.IncreaseIndent();
            PrintName("Assembly", theAssembly.Name());
            ExplorePMI(theAssembly);
            return true;
        }

        public override void VisitLeave(ModelData_Instance theInstance)
        {
            TabulatedOutput.DecreaseIndent();
        }

        public override void VisitLeave(ModelData_Assembly theAssembly)
        {
            TabulatedOutput.DecreaseIndent();
        }

        private void ExplorePMI(ModelData_SceneGraphElement theSGE)
        {
            ModelData_PMITable aPMITable = theSGE.PMI();
            if (aPMITable != null)
            {
                TabulatedOutput.WriteLine("PMI Table:");
                TabulatedOutput.IncreaseIndent();

                ModelData_PMITable.PMIDataIterator aDataIt = new ModelData_PMITable.PMIDataIterator(aPMITable);
                while (aDataIt.HasNext())
                {
                    ModelData_PMIData aData = aDataIt.Next();
                    TabulatedOutput.WriteLine("PMI Data: " + aData.Name());

                    TabulatedOutput.IncreaseIndent();

                    ModelData_PMISemanticElement aSemanticElement = aData.SemanticElement();
                    if (aSemanticElement != null)
                    {
                        TabulatedOutput.WriteLine("Semantic element:");
                        TabulatedOutput.IncreaseIndent();
                        PMISemanticVisitor aVisitor = new PMISemanticVisitor();
                        aSemanticElement.Accept(aVisitor);
                        TabulatedOutput.DecreaseIndent();
                    }

                    ModelData_PMIGraphicalElement aGraphicalElement = aData.GraphicalElement();
                    if (aGraphicalElement != null)
                    {
                        TabulatedOutput.WriteLine("Graphical element:");
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

        private void PrintName(string theSGElement, Base_UTF16String theName)
        {
            if (!theName.IsEmpty())
            {
                TabulatedOutput.WriteLine(theSGElement + ": " + theName);
            }
            else
            {
                TabulatedOutput.WriteLine(theSGElement + ": <noname>");
            }
        }
    }

    class PMISemanticVisitor : ModelData_PMISemanticElementComponentVisitor
    {
        public override void Apply(ModelData_PMIDatumComponent theComponent)
        {
            TabulatedOutput.WriteLine("Datum");
            TabulatedOutput.IncreaseIndent();
            TabulatedOutput.WriteLine("Label: " + theComponent.Label());
            printAttributes(theComponent);
            TabulatedOutput.DecreaseIndent();
        }

        public override void Apply(ModelData_PMIDimensionComponent theComponent)
        {
            TabulatedOutput.WriteLine("Dimension");
            TabulatedOutput.IncreaseIndent();
            TabulatedOutput.WriteLine("Nominal Value: " + theComponent.NominalValue());
            TabulatedOutput.WriteLine("Type of dimension: " + (int)theComponent.TypeOfDimension());
            printAttributes(theComponent);
            TabulatedOutput.DecreaseIndent();
        }

        public override void Apply(ModelData_PMIGeometricToleranceComponent theComponent)
        {
            TabulatedOutput.WriteLine("Geometric tolerance");
            TabulatedOutput.IncreaseIndent();
            TabulatedOutput.WriteLine("Magnitude: " + theComponent.Magnitude());
            TabulatedOutput.WriteLine("Tolerance zone form: " +  (int)theComponent.ToleranceZoneForm());
            printAttributes(theComponent);
            TabulatedOutput.DecreaseIndent();
        }

        void printAttributes(ModelData_PMISemanticElementComponent theComponent)
        {
            if (theComponent.HasAttributes())
            {
                PMISemanticAttributeVisitor aVisitor = new PMISemanticAttributeVisitor();
                theComponent.Accept(aVisitor);
            }
        }
    }

    class PMIOutlineVisitor : ModelData_PMIOutlineVisitor
    {
        public override void Apply(ModelData_PMIPolyOutline theOutline)
        {
            TabulatedOutput.WriteLine("PolyLine set [" + theOutline.LineSet().NumberOfPolyLines() + " polylines]");
        }
        public override void Apply(ModelData_PMIPoly2dOutline theOutline)
        {
            TabulatedOutput.WriteLine("PolyLine2d set [" + theOutline.LineSet().NumberOfPolyLines() + " polylines]");
        }
        public override void Apply(ModelData_PMICurveOutline theOutline)
        {
            TabulatedOutput.WriteLine("Curve set [" + theOutline.NumberOfCurves() + " curves]");
        }
        public override void Apply(ModelData_PMICurve2dOutline theOutline)
        {
            TabulatedOutput.WriteLine("Curve2d set [" + theOutline.NumberOfCurves() + " curves]");
        }
        public override bool VisitEnter(ModelData_PMICompositeOutline theOutline)
        {
            TabulatedOutput.WriteLine("Outline set:");
            TabulatedOutput.IncreaseIndent();
            return true;
        }
        public override void VisitLeave(ModelData_PMICompositeOutline theOutline)
        {
            TabulatedOutput.DecreaseIndent();
        }
    };

    class PMIGraphicalVisitor : ModelData_PMIGraphicalElementComponentVisitor
    {
        public override void Apply(ModelData_PMIOutlinedComponent theComponent)
        {
            TabulatedOutput.WriteLine("Outline");
            TabulatedOutput.IncreaseIndent();
            PMIOutlineVisitor aVisitor = new PMIOutlineVisitor();
            theComponent.Outline().Accept(aVisitor);
            TabulatedOutput.DecreaseIndent();
        }
        public override void Apply(ModelData_PMITextComponent theComponent)
        {
            TabulatedOutput.WriteLine("Text [" + theComponent.Text() + "]");
        }
        public override void Apply(ModelData_PMITriangulatedComponent theComponent)
        {
            TabulatedOutput.WriteLine("Triangulation [" + theComponent.TriangleSet().NumberOfFaces() + " triangles]");
        }
    };

    class PMISemanticAttributeVisitor : ModelData_PMISemanticAttributeVisitor
    {
        public override void Apply(ModelData_PMIModifierAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("Modifier: " + theAttribute.Modifier());
        }
        public override void Apply(ModelData_PMIModifierWithValueAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("ModifierWithValue: modifier=" + theAttribute.Modifier() + ", value=" + theAttribute.Value());
        }
        public override void Apply(ModelData_PMIQualifierAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("Qualifier: " + theAttribute.Qualifier());
        }
        public override void Apply(ModelData_PMIPlusMinusBoundsAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("PlusMinusBounds: (" + theAttribute.LowerBound() + ", " + theAttribute.UpperBound() + ")");
        }
        public override void Apply(ModelData_PMIRangeAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("Range: [" + theAttribute.LowerLimit() + ", " + theAttribute.UpperLimit() + "]");
        }
        public override void Apply(ModelData_PMILimitsAndFitsAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("LimitsAndFits: value=" + theAttribute.Value() + ", type=" + theAttribute.Type());
        }
        public override void Apply(ModelData_PMIDatumTargetAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("DatumTarget: index=" + theAttribute.Index() + ", description=" + theAttribute.Description());
        }
        public override void Apply(ModelData_PMIDatumRefAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("DatumRef: precedence=" + theAttribute.Precedence() + ", targetLabel=" + theAttribute.TargetLabel());
        }
        public override void Apply(ModelData_PMIDatumRefCompartmentAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("DatumRefCompartment:");

            TabulatedOutput.IncreaseIndent();

            uint aNumberOfReferences = theAttribute.NumberOfReferences();
            if (aNumberOfReferences > 0)
            {
                TabulatedOutput.WriteLine("References:");
                TabulatedOutput.IncreaseIndent();
                for (uint i = 0; i < aNumberOfReferences; i++)
                {
                    theAttribute.Reference(i).Accept(this);
                }
                TabulatedOutput.DecreaseIndent();
            }

            uint aNumberOfModifierAttributes = theAttribute.NumberOfModifierAttributes();
            if (aNumberOfModifierAttributes > 0)
            {
                TabulatedOutput.WriteLine("Modifiers:");
                TabulatedOutput.IncreaseIndent();
                for (uint i = 0; i < aNumberOfModifierAttributes; i++)
                {
                    theAttribute.ModifierAttribute(i).Accept(this);
                }
                TabulatedOutput.DecreaseIndent();
            }

            TabulatedOutput.DecreaseIndent();
        }
        public override void Apply(ModelData_PMIMaximumValueAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("MaximumValue: " + theAttribute.MaxValue());
        }
        public override void Apply(ModelData_PMIDisplacementAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("Displacement: " + theAttribute.Displacement());
        }
        public override void Apply(ModelData_PMILengthUnitAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("LengthUnit: " + theAttribute.Unit());
        }
        public override void Apply(ModelData_PMIAngleUnitAttribute theAttribute)
        {
            TabulatedOutput.WriteLine("AngleUnit: " + theAttribute.Unit());
        }
    };

}

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
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace brepresentation
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
                Console.WriteLine("    <input_file>  is a name of the XML file to be read");
                return 1;
            }

            string aSource = args[0];

            ModelData_Model aModel = new ModelData_Model();

            if (!aModel.Open(new Base_UTF16String(aSource)))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            // Explore B-Rep representation of model parts
            PartBRepVisitor aVisitor = new PartBRepVisitor();
            aModel.Accept(aVisitor);

            aVisitor.PrintUniqueShapesCount();

            return 0;
        }
    }

    // Visits directly each part and calls B-Rep representation exploring if a part has one
    class PartBRepVisitor : ModelData_Model.VoidElementVisitor
    {
        public PartBRepVisitor()
        {
            myNestingLevel = 0;
        }

        public void PrintUniqueShapesCount()
        {
            Console.WriteLine();
            Console.WriteLine("Total unique shapes count: " + myShapeSet.Count);
        }

        public override void Apply(ModelData_Part thePart)
        {
            ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
            if (aBRep != null)
            {
                ExploreBRep(aBRep);
            }
        }

        private void ExploreBRep(ModelData_BRepRepresentation theBRep)
        {
            // Get() method retrieves bodies listed in B-Rep representation by calling data providers flushing
            // Flushing isn't an elementary process so it can take a significant time (seconds, minutes depending on a model structure)
            ModelData_BodyList aBodyList = theBRep.Get();

            for (uint i = 0; i < aBodyList.Size(); ++i)
            {
                ModelData_Body aBody = aBodyList.Access(i);
                Console.WriteLine("Body " + i + ": -type " + PrintBodyType(aBody));
                ExploreShape(aBody);
            }
        }


        // Recursive iterating over the Shape until reaching vertices
        private void ExploreShape(ModelData_Shape theShape)
        {
            myShapeSet.Add(theShape);
            ++myNestingLevel;
            ModelData_Shape.Iterator aShapeIt = new ModelData_Shape.Iterator(theShape);
            while (aShapeIt.HasNext())
            {
                ModelData_Shape aShape = aShapeIt.Next();
                PrintShapeInfo(aShape);
                ExploreShape(aShape);
            }
            --myNestingLevel;
        }

        // Returns body type name
        private string PrintBodyType(ModelData_Body theBody)
        {
            switch (theBody.BodyType())
            {
                case ModelData_BodyType.ModelData_BT_Solid: return "Solid";
                case ModelData_BodyType.ModelData_BT_Sheet: return "Sheet";
                case ModelData_BodyType.ModelData_BT_Wireframe: return "Wireframe";
                case ModelData_BodyType.ModelData_BT_Acorn: return "Acorn";
            }
            return "Undefined";
        }

        // Prints shape type name and prints shape info in some cases
        private void PrintShapeInfo(ModelData_Shape theShape)
        {
            PrintTabulation();

            switch (theShape.Type())
            {
                case ModelData_ShapeType.ModelData_ST_Body: Console.Write("Body"); break;
                case ModelData_ShapeType.ModelData_ST_Solid: Console.Write("Solid"); break;
                case ModelData_ShapeType.ModelData_ST_Shell: Console.Write("Shell"); break;
                case ModelData_ShapeType.ModelData_ST_Wire:
                    Console.Write("Wire");
                    PrintWireInfo(ModelData_Wire.Cast(theShape));
                    break;
                case ModelData_ShapeType.ModelData_ST_Face:
                    Console.Write("Face");
                    PrintFaceInfo(ModelData_Face.Cast(theShape));
                    break;
                case ModelData_ShapeType.ModelData_ST_Edge:
                    Console.Write("Edge");
                    PrintEdgeInfo(ModelData_Edge.Cast(theShape));
                    break;
                case ModelData_ShapeType.ModelData_ST_Vertex:
                    Console.Write("Vertex");
                    PrintVertexInfo(ModelData_Vertex.Cast(theShape));
                    break;
                default: Console.Write("Undefined"); break;
            }
            Console.WriteLine();
        }

        private void PrintOrientationInfo(ModelData_Shape theShape)
        {
            Console.Write(". Orientation: ");
            switch (theShape.Orientation())
            {
                case ModelData_ShapeOrientation.ModelData_SO_Forward: Console.Write("Forward"); break;
                case ModelData_ShapeOrientation.ModelData_SO_Reversed: Console.Write("Reversed"); break;
                default:
                    break;
            }
        }

        private void PrintWireInfo(ModelData_Wire theWire)
        {
            ++myNestingLevel;
            PrintOrientationInfo(theWire);
            --myNestingLevel;
        }

        public void PrintFaceInfo(ModelData_Face theFace)
        {
            ++myNestingLevel;
            PrintOrientationInfo(theFace);
            Console.WriteLine();
            ModelData_Surface aSurface = theFace.Surface();
            PrintTabulation();

            Console.Write("Surface: " + PrintSurfaceType(aSurface));

            --myNestingLevel;
        }

        private string PrintSurfaceType(ModelData_Surface theSurface)
        {
            switch (theSurface.Type())
            {
                case ModelData_SurfaceType.ModelData_ST_Plane: return "Plane";
                case ModelData_SurfaceType.ModelData_ST_Cylinder: return "Cylinder";
                case ModelData_SurfaceType.ModelData_ST_Cone: return "Cone";
                case ModelData_SurfaceType.ModelData_ST_Sphere: return "Sphere";
                case ModelData_SurfaceType.ModelData_ST_Torus: return "Torus";
                case ModelData_SurfaceType.ModelData_ST_LinearExtrusion: return "LinearExtrusion";
                case ModelData_SurfaceType.ModelData_ST_Revolution: return "Revolution";
                case ModelData_SurfaceType.ModelData_ST_Bezier: return "Bezier";
                case ModelData_SurfaceType.ModelData_ST_BSpline: return "BSpline";
                case ModelData_SurfaceType.ModelData_ST_Offset: return "Offset";
                case ModelData_SurfaceType.ModelData_ST_Trimmed: return "Trimmed";
                default:
                    break;
            }
            return "Undefined";
        }

        private void PrintEdgeInfo(ModelData_Edge theEdge)
        {
            ++myNestingLevel;
            if (theEdge.IsDegenerated())
            {
                Console.Write("(Degenerated)");
            }
            PrintOrientationInfo(theEdge);
            Console.Write(". Tolerance " + theEdge.Tolerance());

            if (!theEdge.IsDegenerated())
            {
                Console.WriteLine();
                double aParamFirst = 0.0, aParamLast = 0.0;
                ModelData_Curve aCurve = theEdge.Curve(ref aParamFirst, ref aParamLast);
                PrintTabulation();
                Console.Write("Curve: " + PrintCurveType(aCurve));
            }
            --myNestingLevel;
        }

        private string PrintCurveType(ModelData_Curve theCurve)
        {
            switch (theCurve.Type())
            {
                case ModelData_CurveType.ModelData_CT_Line: return "Line";
                case ModelData_CurveType.ModelData_CT_Circle: return "Circle";
                case ModelData_CurveType.ModelData_CT_Ellipse: return "Ellipse";
                case ModelData_CurveType.ModelData_CT_Hyperbola: return "Hyperbola";
                case ModelData_CurveType.ModelData_CT_Parabola: return "Parabola";
                case ModelData_CurveType.ModelData_CT_Bezier: return "Bezier";
                case ModelData_CurveType.ModelData_CT_BSpline: return "BSpline";
                case ModelData_CurveType.ModelData_CT_Offset: return "Offset";
                case ModelData_CurveType.ModelData_CT_Trimmed: return "Trimmed";
                default:
                    break;
            }
            return "Undefined";
        }

        private void PrintVertexInfo(ModelData_Vertex theVertex)
        {
            PrintOrientationInfo(theVertex);
            Console.Write(". Tolerance " + theVertex.Tolerance());
        }

        private void PrintTabulation()
        {
            for (int i = 0; i < myNestingLevel; ++i)
            {
                Console.Write("- ");
            }
        }

        // Set to collect unique shapes from model
        private HashSet<ModelData_Shape> myShapeSet = new HashSet<ModelData_Shape>(new ModelData_UnorientedShapeHash());
        private int myNestingLevel;
    }
}

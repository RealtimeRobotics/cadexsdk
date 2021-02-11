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

import java.util.HashSet;

public class breprepresentation {
    static {
        try {
            System.loadLibrary("CadExCore");
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
            System.out.println("    <input_file>  is a name of the XML file to be read");
            System.exit(1);
        }

        String aSource = args[0];

        ModelData_Model aModel = new ModelData_Model();

        if (!aModel.Open(new Base_UTF16String(aSource))) {
            System.out.println("Failed to read the file");
            System.exit(1);
        }

        // Explore B-Rep representation of model parts
        PartBRepVisitor aVisitor = new PartBRepVisitor();
        aModel.Accept(aVisitor);

        aVisitor.PrintUniqueShapesCount();
    }
}

class PartBRepVisitor extends ModelData_Model.VoidElementVisitor {
    public void PrintUniqueShapesCount() {
        System.out.println("Total unique shapes count: " + myShapeSet.size());
    }

    @Override
    public void Apply(ModelData_Part thePart) {
        ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
        if (aBRep != null) {
            ExploreBRep(aBRep);
        }
    }

    private void ExploreBRep(ModelData_BRepRepresentation theBRep) {
        // Get() method retrieves bodies listed in B-Rep representation by calling data providers flushing
        // Flushing isn't an elementary process so it can take a significant time (seconds, minutes depending on a model structure)
        ModelData_BodyList aBodyList = theBRep.Get();

        // Iterate over bodies
        for (int i = 0; i < aBodyList.Size(); ++i) {
            ModelData_Body aBody = aBodyList.Element(i);
            System.out.println("Body " + i + " : -type " + PrintBodyType(aBody));

            ExploreShape(aBody);
        }
    }

    // Recursive iterating over the Shape until reaching vertices
    private void ExploreShape(ModelData_Shape theShape) {
        myShapeSet.add(theShape);
        ++myNestingLevel;
        ModelData_Shape.Iterator aShapeIt = new ModelData_Shape.Iterator(theShape);
        while (aShapeIt.HasNext()) {
            ModelData_Shape aShape = aShapeIt.Next();
            PrintShapeInfo(aShape);
            ExploreShape(aShape);
        }
        --myNestingLevel;
    }

    // Returns body type name
    String PrintBodyType(ModelData_Body theBody) {
        switch (theBody.BodyType()) {
            case ModelData_BT_Solid:
                return "Solid";
            case ModelData_BT_Sheet:
                return "Sheet";
            case ModelData_BT_Wireframe:
                return "Wireframe";
            case ModelData_BT_Acorn:
                return "Acorn";
            default:
                break;
        }

        return "Undefined";
    }

    // Returns shape type name and prints shape info in some cases
    void PrintShapeInfo(ModelData_Shape theShape) {
        PrintTabulation();

        switch (theShape.Type()) {
            case ModelData_ST_Body:
                System.out.println("Body");
                break;
            case ModelData_ST_Solid:
                System.out.println("Solid");
                break;
            case ModelData_ST_Shell:
                System.out.println("Shell");
                break;
            case ModelData_ST_Wire:
                System.out.print("Wire");
                PrintWireInfo(ModelData_Wire.Cast(theShape));
                break;
            case ModelData_ST_Face:
                System.out.print("Face");
                PrintFaceInfo(ModelData_Face.Cast(theShape));
                break;
            case ModelData_ST_Edge:
                System.out.print("Edge");
                PrintEdgeInfo(ModelData_Edge.Cast(theShape));
                break;
            case ModelData_ST_Vertex:
                System.out.print("Vertex");
                PrintVertexInfo(ModelData_Vertex.Cast(theShape));
                break;
            default:
                System.out.print("Undefined");
                break;
        }
    }

    private void PrintWireInfo(ModelData_Wire theWire) {
        System.out.print(". Orientation: " + PrintOrientation(theWire.Orientation()) + "\n");
    }

    private void PrintFaceInfo(ModelData_Face theFace) {
        ++myNestingLevel;
        System.out.print(". Orientation: " + PrintOrientation(theFace.Orientation()) + "\n");

        ModelData_Surface aSurface = theFace.Surface();
        PrintTabulation();
        System.out.print("Surface: " + PrintSurfaceType(aSurface) + "\n");

        --myNestingLevel;
    }

    private String PrintSurfaceType(ModelData_Surface theSurface) {
        switch (theSurface.Type()) {
            case ModelData_ST_Plane:
                return "Plane";
            case ModelData_ST_Cylinder:
                return "Cylinder";
            case ModelData_ST_Cone:
                return "Cone";
            case ModelData_ST_Sphere:
                return "Sphere";
            case ModelData_ST_Torus:
                return "Torus";
            case ModelData_ST_LinearExtrusion:
                return "LinearExtrusion";
            case ModelData_ST_Revolution:
                return "Revolution";
            case ModelData_ST_Bezier:
                return "Bezier";
            case ModelData_ST_BSpline:
                return "BSpline";
            case ModelData_ST_Offset:
                return "Offset";
            case ModelData_ST_Trimmed:
                return "Trimmed";
            default:
                break;
        }

        return "Undefined";
    }

    private void PrintEdgeInfo(ModelData_Edge theEdge) {
        ++myNestingLevel;
        if (theEdge.IsDegenerated()) {
            System.out.print("(Degenerated)");
        }
        System.out.print(". Orientation: " + PrintOrientation(theEdge.Orientation()));
        System.out.print(". Tolerance: " + theEdge.Tolerance() + "\n");

        if (!theEdge.IsDegenerated()) {
            double[][] aParams = {{0}, {1}};
            ModelData_Curve aCurve = theEdge.Curve(aParams[0], aParams[1]);
            PrintTabulation();
            System.out.print("Curve: " + PrintCurveType(aCurve) + "\n");
        }

        --myNestingLevel;
    }

    private String PrintCurveType(ModelData_Curve theCurve) {
        switch (theCurve.Type()) {
            case ModelData_CT_Line:
                return "Line";
            case ModelData_CT_Circle:
                return "Circle";
            case ModelData_CT_Ellipse:
                return "Ellipse";
            case ModelData_CT_Hyperbola:
                return "Hyperbola";
            case ModelData_CT_Parabola:
                return "Parabola";
            case ModelData_CT_Bezier:
                return "Bezier";
            case ModelData_CT_BSpline:
                return "BSpline";
            case ModelData_CT_Offset:
                return "Offset";
            case ModelData_CT_Trimmed:
                return "Trimmed";
            default:
                break;
        }

        return "Undefined";
    }

    private void PrintVertexInfo(ModelData_Vertex theVertex) {
        System.out.print(". Orientation: " + PrintOrientation(theVertex.Orientation()));
        System.out.print(". Tolerance " + theVertex.Tolerance() + "\n");
    }

    private String PrintOrientation(ModelData_ShapeOrientation theOrientation) {
        if (theOrientation == ModelData_ShapeOrientation.ModelData_SO_Forward) {
            return "Forward";
        } else if (theOrientation == ModelData_ShapeOrientation.ModelData_SO_Reversed) {
            return "Reversed";
        } else {
            return "Undefined";
        }
    }

    private void PrintTabulation() {
        for (int i = 0; i < myNestingLevel; ++i) {
            System.out.print("- ");
        }
    }

    private int myNestingLevel = 0;
    private HashSet<ModelData_Shape> myShapeSet = new HashSet<>();
}

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

public class polyrepresentation {
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

        // If there is no Poly representation in the model, mesher will compute it
        ModelAlgo_BRepMesherParameters aParams = new ModelAlgo_BRepMesherParameters();
        aParams.SetGranularity(ModelAlgo_BRepMesherParameters.Granularity.Fine);
        ModelAlgo_BRepMesher aMesher = new ModelAlgo_BRepMesher(aParams);
        aMesher.Compute(aModel);

        // Explore Poly representation of model parts
        PartPolyVisitor aVisitor = new PartPolyVisitor();
        aModel.Accept(aVisitor);
    }
}

// Visits directly every part and calls Poly representation exploring if a part has one
class PartPolyVisitor extends ModelData_Model.VoidElementVisitor {
    @Override
    public void Apply(ModelData_Part thePart) {
        ModelData_PolyRepresentation aPolyRep = thePart.PolyRepresentation(ModelData_RepresentationMask.ModelData_RM_Poly);
        if (aPolyRep != null) {
            ExplorePoly(aPolyRep);
        }
    }

    // Explores PolyVertexSets of Poly representation
    private void ExplorePoly(ModelData_PolyRepresentation thePoly) {
        // Get() method retrieves PolyVertexSets listed in Poly representation by calling data providers flushing
        // Because of internal mechanics providers flushing is faster than for B-Rep representations
        ModelData_PolyShapeList aList = thePoly.Get();

        // Iterate over PolyShape list
        for (int i = 0; i < aList.Size(); ++i) {
            ModelData_PolyVertexSet aPVS = aList.Access(i);
            System.out.println("PolyShape " + i + ":");
            PrintPVSInfo(aPVS);
        }
    }

    // Function to print a PolyVertexSet info
    private void PrintPVSInfo(ModelData_PolyVertexSet thePVS) {
        if (thePVS.TypeId() == ModelData_IndexedTriangleSet.GetTypeId()) {
            System.out.println("IndexedTriangleSet type.");
            ModelData_IndexedTriangleSet anITS = ModelData_IndexedTriangleSet.Cast(thePVS);
            DumpTriangleSet(anITS);
        } else if (thePVS.TypeId() == ModelData_PolyLineSet.GetTypeId()) {
            System.out.println("PolyLineSet type");
            ModelData_PolyLineSet aPLS = ModelData_PolyLineSet.Cast(thePVS);
            DumpPolyLineSet(aPLS);
        } else if (thePVS.TypeId() == ModelData_PolyPointSet.GetTypeId()) {
            System.out.println("PolyPointSet type");
            ModelData_PolyPointSet aPPS = ModelData_PolyPointSet.Cast(thePVS);
            DumpPolyPointSet(aPPS);
        } else {
            System.out.println("Undefined type");
        }
    }

    private void DumpPolyPointSet(ModelData_PolyPointSet thePS) {
        int n = thePS.NumberOfVertices();

        System.out.println("PolyPoint set contains " + n + " vertices");
        for (int i = 0; i < n; ++i) {
            System.out.println("Point " + i + ":");
            System.out.println("    Node coordinates:");
            ModelData_Point aP = thePS.Coordinate(i);
            System.out.println("    (" + aP.X() + ", " + aP.Y() + ", " + aP.Z() + ")");
        }
    }

    // Prints number of PolyLines and local coordinates for every vertex of each PolyLine
    private void DumpPolyLineSet(ModelData_PolyLineSet thePLS) {
        int n = thePLS.NumberOfPolyLines();

        System.out.println("PolyLine set contains " + n + " PolyLines");
        for (int i = 0; i < n; ++i) {
            System.out.println("PolyLine " + i + ":");
            System.out.println("    Node coordinates:");
            for (int j = 0; j < thePLS.NumberOfVertices(i); ++j) {
                ModelData_Point aV = thePLS.Coordinate(i, j);
                System.out.println("    (" + aV.X() + ", " + aV.Y() + ", " + aV.Z() + ")");
            }
        }
    }

    // Prints number of triangles and local data for each node
    // Prints Coords and UV-Coords for each vertex and prints Normals and Colors for each triangle
    private void DumpTriangleSet(ModelData_IndexedTriangleSet theTS) {
        int n = theTS.NumberOfFaces();

        System.out.println("Triangle set contains " + n + " Triangles");
        for (int i = 0; i < n; ++i) {
            System.out.println("Triangle " + i + ":");

            for (int j = 0; j < 3; ++j) {
                System.out.println("Node: " + j);

                // Coordinates
                System.out.println("    Node coordinates:");
                ModelData_Point aV = theTS.Coordinate(i, j);
                System.out.println("    (" + aV.X() + ", " + aV.Y() + ", " + aV.Z() + ")");

                // UV-coordinates
                if (theTS.HasUVCoordinates()) {
                    System.out.println("    UV coordinates:");
                    ModelData_Point2d aUV = theTS.UVCoordinate(i, j);
                    System.out.println("    (" + aUV.X() + ", " + aUV.Y() + ")");
                }

                // Normals
                if (theTS.HasNormals()) {
                    ModelData_Vectorf aN = theTS.VertexNormal(i, j);
                    System.out.println("    Normal: (" + aN.X() + ", " + aN.Y() + ", " + aN.Z() + ")");
                }

                // Colors
                if (theTS.HasColors()) {
                    ModelData_Color aColor = theTS.VertexColor(i, j);
                    System.out.println(
                            "    Color (RGB):     (" + aColor.R() + ", " + aColor.G() + ", " + aColor.B() + ", " + aColor.A() + ")");
                }
            }
        }
    }
}

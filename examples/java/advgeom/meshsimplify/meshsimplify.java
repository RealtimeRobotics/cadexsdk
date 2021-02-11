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

public class meshsimplify {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExAdvGeom");
            System.loadLibrary("CadExVRML");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(1);
        }
    }

    public static void main (String[] args) {
        String aKey = LicenseKey.Value();

        // Activate the license (aKey must be defined in LicenseKey.java)
        if (!LicenseManager.Activate(aKey)) {
            System.out.println("Failed to activate CAD Exchanger license.");
            System.exit(1);
        }

        if (args.length != 2) {
            System.err.println("Usage: " + " <input_file> <output_file>, where:");
            System.err.println("    <input_file>  is a name of the VRML file to be read        ");
            System.err.println("    <output_file> is a name of the XML file to Save() the model");
            System.exit(1);
        }

        String aSource = args[0];
        String aDest = args[1];

        ModelData_Model aModel = new ModelData_Model();

        VRML_Reader aReader = new VRML_Reader();

        // Read the file
        if (!aReader.ReadFile(new Base_UTF16String(aSource))) {
            System.err.println("Failed to read the file " + aSource);
            System.exit(1);
        }

        // Make model data
        if (!aReader.Transfer(aModel)) {
            System.err.println("Failed to transfer the file " + aSource);
            System.exit(1);
        }

        // Basic info about model
        TriangleCounter aBeforeCounter = new TriangleCounter();
        aModel.Accept(aBeforeCounter);
        System.out.println("Model name: " + aModel.Name());
        System.out.println("# of triangles before: " + String.valueOf(aBeforeCounter.NumberOfTriangles()));

        // Running the simplifier
        ModelSimplifier_MeshSimplifierParameters aParams = new ModelSimplifier_MeshSimplifierParameters();
        aParams.SetDegreeOfSimplification(ModelSimplifier_MeshSimplifierParameters.DegreeOfSimplificationType.High);

        ModelSimplifier_MeshSimplifier aSimplifier = new ModelSimplifier_MeshSimplifier();
        aSimplifier.SetParameters(aParams);
        ModelData_Model aNewModel = aSimplifier.Perform(aModel);

        // How many triangles does simplified model contain?
        TriangleCounter anAfterCounter = new TriangleCounter();
        aNewModel.Accept(anAfterCounter);
        System.out.println("# of triangles after: " + String.valueOf(anAfterCounter.NumberOfTriangles()));

        // Saving the simplified model
        if (!aNewModel.Save(new Base_UTF16String(aDest))) {
            System.err.println("Failed to write the file " + aDest);
            System.exit(1);
        }
    }
}

class TriangleCounter extends ModelData_Model.VoidElementVisitor {

    class PolyRepExplorer extends ModelData_Part.VoidRepresentationVisitor {
        public int myNumberOfTriangles = 0;

        @Override
        public void Apply(ModelData_PolyRepresentation theRep) {
            ModelData_PolyShapeList aShapeList = theRep.Get();
            for (int i = 0; i < aShapeList.Size(); i++) {
                ModelData_PolyShape aShape = aShapeList.Element(i);
                if (aShape.TypeId() == ModelData_IndexedTriangleSet.GetTypeId()) {
                    ModelData_IndexedTriangleSet anITS = ModelData_IndexedTriangleSet.Cast(aShape);
                    myNumberOfTriangles += anITS.NumberOfFaces();
                }
            }
        }
    }

    private int myNumberOfTriangles = 0;

    @Override
    public void Apply(ModelData_Part thePart) {
        PolyRepExplorer aRepExplorer = new PolyRepExplorer();
        thePart.Accept(aRepExplorer);
        myNumberOfTriangles += aRepExplorer.myNumberOfTriangles;
    }

    public final int NumberOfTriangles() { return myNumberOfTriangles; }

};

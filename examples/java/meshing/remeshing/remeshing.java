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

import java.util.HashMap;
import java.util.Stack;
import java.util.ArrayList;

public class remeshing {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExSLD");
            System.loadLibrary("CadExVRML");
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

        if (args.length != 2) {
            System.out.println("Usage: " + " <input_file> <output_file>, where:");
            System.out.println("    <input_file>  is a name of the SLD file to be read  ");
            System.out.println("    <output_file> is a name of the VRML file to be written");
            System.exit(1);
        }

        String aSource = args[0];
        String aDest = args[1];

        SLD_Reader aReader = new SLD_Reader();

        System.out.println("Conversion started...");

        // Read the file
        if (!aReader.ReadFile(new Base_UTF16String(aSource))) {
            System.out.println("Failed to read the file " + aSource);
            System.exit(1);
        }

        ModelData_Model aModel = new ModelData_Model();

        // Make model data
        if (!aReader.Transfer(aModel)) {
            System.out.println("Failed to transfer model data to specified format " + aSource);
            System.exit(1);
        }

        MeshReplacementVisitor aVisitor = new MeshReplacementVisitor();
        aModel.Accept(aVisitor);
        ArrayList <ModelData_SceneGraphElement> aNewRoots = new ArrayList<ModelData_SceneGraphElement>();
        for (ModelData_Model.ElementIterator anIt = new ModelData_Model.ElementIterator(aModel); anIt.HasNext();) {
            ModelData_SceneGraphElement aRoot = anIt.Next();
            if (aRoot.TypeId() == ModelData_Part.GetTypeId()) {
                ModelData_Part aRootPart = ModelData_Part.Cast(aRoot);
                assert(aVisitor.RootReplacements().containsKey(aRootPart));
                aNewRoots.add(aVisitor.RootReplacements().get(aRootPart));
            } else {
                aNewRoots.add(aRoot);
            }
        }
        aModel.Clear();
        for (ModelData_SceneGraphElement aNewRoot : aNewRoots) {
            aModel.AddRoot(aNewRoot);
        }


        VRML_Writer aWriter = new VRML_Writer();

        // Transfer model data to JT format
        if (!aWriter.Transfer(aModel)) {
            System.out.println("Failed to transfer model data to specified format " + aSource);
            System.exit(1);
        }

        // Write the file
        if (!aWriter.WriteFile(new Base_UTF16String(aDest))) {
            System.out.println("Failed to write the file " + aSource);
            System.exit(1);
        }
    }
}

class MeshReplacementVisitor extends ModelData_Model.VoidElementVisitor {
    @Override
    public boolean VisitEnter(ModelData_Instance theInstance) {
        myInstances.push(theInstance);
        return true;
    }

    @Override
    public void VisitLeave(ModelData_Instance theInstance) {
        myInstances.pop();
    }

    @Override
    public void Apply(ModelData_Part thePart) {

        if (thePart.BRepRepresentation().IsNull()) {
            return;
        }

        if (myReplacedParts.containsKey (thePart) && myInstances.size() > 0) {
            myInstances.peek().SetReference (myReplacedParts.get (thePart));
            return;
        }

        ModelData_Part aNewPart = new ModelData_Part(thePart.BRepRepresentation(), thePart.Name());
        aNewPart.SetAppearance(thePart.Appearance());
        aNewPart.AddProperties(thePart.Properties());
        aNewPart.AddPMI(thePart.PMI());
        for (ModelData_SceneGraphElement.LayerIterator anIt = new ModelData_SceneGraphElement.LayerIterator(thePart); anIt.HasNext();) {
            aNewPart.AddToLayer(anIt.Next());
        }

        ModelAlgo_BRepMesherParameters aMesherParams = new ModelAlgo_BRepMesherParameters(ModelAlgo_BRepMesherParameters.Granularity.Fine);
        ModelAlgo_BRepMesher aMesher = new ModelAlgo_BRepMesher(aMesherParams);
        aMesher.Compute(aNewPart);

        if (myInstances.size() == 0) {
            myRootReplacements.put(thePart, aNewPart);
        } else {
            myReplacedParts.put(thePart, aNewPart);
            myInstances.peek().SetReference (aNewPart);
        }
    }

    HashMap<ModelData_Part, ModelData_Part> RootReplacements() {
        return myRootReplacements;
    }

    private HashMap<ModelData_Part, ModelData_Part> myRootReplacements  = new HashMap<ModelData_Part, ModelData_Part>();
    private Stack<ModelData_Instance> myInstances = new Stack<ModelData_Instance>();
    private HashMap<ModelData_Part, ModelData_Part> myReplacedParts = new HashMap<ModelData_Part, ModelData_Part>();
}

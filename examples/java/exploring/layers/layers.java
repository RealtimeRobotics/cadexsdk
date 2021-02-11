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

public class layers {
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

        // Check the model if it has any layer
        ModelData_Model.LayerIterator aLayerIt = new ModelData_Model.LayerIterator(aModel);
        if (!aLayerIt.HasNext()) {
            // Create a visitor to fill it's layer object
            LayersFiller aVisitor = new LayersFiller();
            aModel.Accept(aVisitor);

            // Add created layer to the model
            aModel.AddLayer(aVisitor.GetLayer());
        }

        LayersVisitor aLayerVisitor = new LayersVisitor();
        aModel.Accept(aLayerVisitor);
    }
}

// Visitor used to add model's parts to layer
class LayersFiller extends ModelData_Model.CombinedElementVisitor {
    @Override
    public void Apply(ModelData_Part thePart) {
        mySGELayer.Add(thePart);
        ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
        if (aBRep != null) {
            ModelData_BodyList aBodyList = aBRep.Get();
            for (int i = 0; i < aBodyList.Size(); ++i) {
                ModelData_Body aBody = aBodyList.Element(i);
                aBRep.AddToLayer(aBody, mySubshapesLayer);
            }
        }
    }

    @Override
    public boolean VisitEnter(ModelData_SceneGraphElement theElement) {
        mySGELayer.Add(theElement);
        return true;
    }

    public ModelData_Layer GetLayer() {
        return mySubshapesLayer;
    }

    private ModelData_Layer mySubshapesLayer = new ModelData_Layer(new Base_UTF16String("SubshapesLayer"));
    private ModelData_Layer mySGELayer = new ModelData_Layer(new Base_UTF16String("SGELayer"));
}

// Visitor to explore model layers
class LayersVisitor extends ModelData_Model.LayerVisitor {
    @Override
    public void Apply(ModelData_Layer theLayer) {
        LayerItemVisitor aLayerItemVisitor = new LayerItemVisitor();
        theLayer.Accept(aLayerItemVisitor);
        System.out.println("Layer " + theLayer.Name() + " contains:");
        aLayerItemVisitor.PrintElementsCount();
    }
}

// Visitor checks elements of specific layer
class LayerItemVisitor extends ModelData_Layer.ItemVisitor {
    @Override
    public void Apply(ModelData_SceneGraphElement theSGE) {
        if (theSGE.TypeId() == ModelData_Part.GetTypeId()) {
            ++myPartsNb;
        } else if (theSGE.TypeId() == ModelData_Assembly.GetTypeId()) {
            ++myAssembliesNb;
        } else if (theSGE.TypeId() == ModelData_Instance.GetTypeId()) {
            ++myInstancesNb;
        }
    }

    @Override
    public void Apply(ModelData_Shape theShape, ModelData_BRepRepresentation theBRep) {
        ++myShapesNb;
    }

    public void PrintElementsCount() {
        System.out.println("Number of parts:      " + myPartsNb);
        System.out.println("Number of assemblies: " + myAssembliesNb);
        System.out.println("Number of instances:  " + myInstancesNb);
        System.out.println("Number of shapes:     " + myShapesNb);
    }

    private int myPartsNb = 0;
    private int myAssembliesNb = 0;
    private int myInstancesNb = 0;
    private int myShapesNb = 0;
}

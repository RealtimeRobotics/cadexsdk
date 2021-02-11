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

public class appearance {
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

        // Explore model's appearances
        AppearancesCollector aCollector = new AppearancesCollector(aModel);

        // Print the number of unique appearances in our model
        aCollector.PrintAppearancesCount();
    }
}

class AppearancesCollector {
    public AppearancesCollector(ModelData_Model theModel) {
        ModelData_Model aModel = theModel;

        SGEAppearancesCollector aCollector = new SGEAppearancesCollector(myAppSet);
        theModel.Accept(aCollector);
    }

    public void PrintAppearancesCount() {
        System.out.println("Total Model Unique Appearances Count: " + myAppSet.size());
    }

    private HashSet<ModelData_Appearance> myAppSet = new HashSet<>();
}

class SGEAppearancesCollector extends ModelData_Model.CombinedElementVisitor {
    public SGEAppearancesCollector(HashSet<ModelData_Appearance> theAppSet) {
        myAppSet = theAppSet;
    }

    @Override
    public void Apply(ModelData_Part thePart) {
        ExploreSGEAppearance(thePart);

        RepVisitor aVisitor = new RepVisitor(myAppSet);
        thePart.Accept(aVisitor);
    }

    @Override
    public boolean VisitEnter(ModelData_SceneGraphElement theSGE) {
        ExploreSGEAppearance(theSGE);
        return true;
    }

    private void ExploreSGEAppearance(ModelData_SceneGraphElement theSGE) {
        ModelData_Appearance anApp = theSGE.Appearance();
        if (anApp != null) {
            myAppSet.add(anApp);
        }
    }

    private HashSet<ModelData_Appearance> myAppSet;
}

class RepVisitor extends ModelData_Part.RepresentationVisitor {
    public RepVisitor(HashSet<ModelData_Appearance> theAppSet) {
        myAppSet = theAppSet;
    }

    @Override
    public void Apply(ModelData_BRepRepresentation theBRep) {
        SubshapeAppearancesCollector aCollector = new SubshapeAppearancesCollector(theBRep, myAppSet);
        theBRep.Accept(aCollector);
    }

    @Override
    public void Apply(ModelData_PolyRepresentation thePolyRep) {
        ExplorePVSAppearances(thePolyRep);
    }

    // Iterates through PolyShapes to collect it's appearances
    private void ExplorePVSAppearances(ModelData_PolyRepresentation thePolyRep) {
        ModelData_PolyShapeList aList = thePolyRep.Get();
        for (int i = 0; i < aList.Size(); ++i) {
            ModelData_PolyVertexSet aPVS = aList.Element(i);
            ModelData_Appearance anApp = aPVS.Appearance();
            if (anApp != null) {
                myAppSet.add(anApp);
            }
        }
    }

    private HashSet<ModelData_Appearance> myAppSet;
}

class SubshapeAppearancesCollector extends ModelData_BRepRepresentation.SubshapeVisitor {
    public SubshapeAppearancesCollector(ModelData_BRepRepresentation theBRep, HashSet<ModelData_Appearance> theAppSet) {
        myBRep = theBRep;
        myAppSet = theAppSet;
    }

    @Override
    public void Apply(ModelData_Shape theShape) {
        ExploreShapeAppearances(theShape);
    }

    // Iterates through Shapes to collect it's appearances
    private void ExploreShapeAppearances(ModelData_Shape theShape) {
        ModelData_Appearance anApp = myBRep.Appearance(theShape);
        if (anApp != null) {
            myAppSet.add(anApp);
        }
    }

    private HashSet<ModelData_Appearance> myAppSet;
    private ModelData_BRepRepresentation myBRep;
}

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

import java.util.ArrayList;

public class propertytable {
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

        PropertiesVisitor aVisitor = new PropertiesVisitor();
        aModel.Accept(aVisitor);
    }
}

class PropertiesVisitor extends ModelData_Model.CombinedElementVisitor {
    @Override
    public void Apply(ModelData_Part thePart) {
        ModelData_PropertyTable aPT = thePart.Properties();
        ExplorePropertyTable(aPT);

        ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
        if (aBRep != null) {
            SubshapePropertiesVisitor aVisitor = new SubshapePropertiesVisitor(aBRep);
            aBRep.Accept(aVisitor);

            // Extract all PropertyTables from SubShapes in B-Rep and explore it
            ArrayList<ModelData_PropertyTable> aPTList = aVisitor.GetPropertyTables();
            for (int i = 0; i < aPTList.size(); ++i) {
                ExplorePropertyTable(aPTList.get(i));
            }
        }
    }

    @Override
    public boolean VisitEnter(ModelData_SceneGraphElement theElement) {
        ModelData_PropertyTable aPT = theElement.Properties();
        ExplorePropertyTable(aPT);

        return true;
    }

    private void ExplorePropertyTable(ModelData_PropertyTable thePT) {
        // Traverse property table if it is not empty
        if (thePT != null && !thePT.IsEmpty()) {
            PropertyVisitor aPropVisitor = new PropertyVisitor();
            thePT.Accept(aPropVisitor);
        } else {
            System.out.println("\nProperty Table is empty");
        }
    }
}

class SubshapePropertiesVisitor extends ModelData_BRepRepresentation.SubshapeVisitor {
    public SubshapePropertiesVisitor(ModelData_BRepRepresentation theBRep) {
        myBRep = theBRep;
    }

    @Override
    public void Apply(ModelData_Shape theShape) {
        ModelData_PropertyTable aPT = myBRep.PropertyTable(theShape);
        myPTList.add(aPT);
    }

    public ArrayList<ModelData_PropertyTable> GetPropertyTables() {
        return myPTList;
    }

    private ModelData_BRepRepresentation myBRep;
    private ArrayList<ModelData_PropertyTable> myPTList = new ArrayList<>();
}

class PropertyVisitor extends ModelData_PropertyTable.VoidVisitor {
    public PropertyVisitor() {
        System.out.println("\nProperty table: ");
    }

    @Override
    public void Apply(Base_UTF16String theName, int theValue) {
        OutputData(theName, theValue);
    }

    @Override
    public void Apply(Base_UTF16String theName, double theValue) {
        OutputData(theName, theValue);
    }

    @Override
    public void Apply(Base_UTF16String theName, Base_UTF16String theValue) {
        OutputData(theName, theValue);
    }

    private void OutputData(Base_UTF16String theName, Object theValue) {
        System.out.println(theName + ": " + theValue);
    }
}

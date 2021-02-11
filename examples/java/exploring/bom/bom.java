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

public class bom {
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

        // Create a Counter
        SceneGraphVisitor aCounter = new SceneGraphVisitor();
        aModel.Accept(aCounter);
        aCounter.PrintCounts();
    }
}

class SceneGraphVisitor extends ModelData_Model.ElementVisitor {
    @Override
    public void Apply(ModelData_Part thePart) {
        PrintName("Part", thePart.Name());
        UpdateTable(thePart);
    }

    @Override
    public boolean VisitEnter(ModelData_Assembly theAssembly) {
        PrintName("Assembly", theAssembly.Name());
        UpdateTable(theAssembly);
        ++myNestingLevel;
        return true;
    }

    @Override
    public void VisitLeave(ModelData_Assembly theAssembly) {
        --myNestingLevel;
    }

    @Override
    public boolean VisitEnter(ModelData_Instance theInstance) {
        PrintName("Instance", theInstance.Name());
        ++myNestingLevel;
        return true;
    }

    @Override
    public void VisitLeave(ModelData_Instance theInstance) {
        --myNestingLevel;
    }

    public void PrintCounts() {
        System.out.println("Total:\nname | type | count");
        for (HashMap.Entry<ModelData_SceneGraphElement, Integer> entry : mySGEMap.entrySet()) {
            System.out.println(entry.getKey().Name() + " | " + PrintSGEType(entry.getKey()) + " | " + entry.getValue());
        }
    }

    private void PrintName(String theSGElement, Base_UTF16String theName) {
        for (int i = 0; i < myNestingLevel; ++i) {
            System.out.print("--- ");
        }

        if (!theName.IsEmpty()) {
            System.out.println(theSGElement + ": " + theName);
        } else {
            System.out.println(theSGElement + ": <noname>");
        }
    }

    private void UpdateTable(ModelData_SceneGraphElement theSGEElement) {
        if (mySGEMap.containsKey(theSGEElement)) {
            mySGEMap.put(theSGEElement, (mySGEMap.get(theSGEElement) + 1));
        } else {
            mySGEMap.put(theSGEElement, 1);
        }
    }

    private String PrintSGEType(ModelData_SceneGraphElement theSGE) {
        if (theSGE.TypeId() == ModelData_Part.GetTypeId()) {
            return "Part";
        } else if (theSGE.TypeId() == ModelData_Assembly.GetTypeId()) {
            return "Assembly";
        } else if (theSGE.TypeId() == ModelData_Instance.GetTypeId()) {
            return "Instance";
        }
        return "Undefined";
    }

    private int myNestingLevel = 0;
    private HashMap<ModelData_SceneGraphElement, Integer> mySGEMap = new HashMap<>();
}

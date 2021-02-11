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

import java.util.*;

public class elementremoval {
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

        if (args.length != 3) {
            System.out.println("Usage: " + " <input_file> <output_file> <sge_to_remove>, where:");
            System.out.println("    <input_file>  is a name of the XML file to be read");
            System.out.println("    <output_file>   is a name of the XML file where the output should be stored");
            System.out.println("    <sge_to_remove> is a name of the scene graph elements to remove");
            System.exit(1);
        }

        String aSource = args[0];
        String anOutput = args[1];

        // Load the model
        ModelData_Model aModel = new ModelData_Model();

        if (!aModel.Open(new Base_UTF16String(aSource))) {
            System.out.println("Failed to read the file " + aSource);
            System.exit(1);
        }

        // Remove roots with specified name
        Base_UTF16String aNameToRemove = new Base_UTF16String(args[2]);
        List<ModelData_SceneGraphElement> aRootsToRemove = new ArrayList<>();
        ModelData_Model.ElementIterator anIt = new ModelData_Model.ElementIterator(aModel);
        while (anIt.HasNext()) {
            ModelData_SceneGraphElement anElement = anIt.Next();
            if (anElement.Name().equals(aNameToRemove)) {
                aRootsToRemove.add(anElement);
            }
        }

        for (ModelData_SceneGraphElement aRootToRemove : aRootsToRemove) {
            aModel.RemoveRoot(aRootToRemove);
        }

        // Find the rest of scene graph elements that need to be removed and their parents
        RemovedSGEFinder aFinder = new RemovedSGEFinder(aNameToRemove);
        aModel.Accept(aFinder);

        // Perform the recorded removals of non-root SGEs
        for (Map.Entry<ModelData_Assembly, List<ModelData_Instance>> aParentWithChildren : aFinder.SGEsToRemove().entrySet()) {
            ModelData_Assembly aParent = aParentWithChildren.getKey();
            List<ModelData_Instance> aChildrenToRemove = aParentWithChildren.getValue();

            for (ModelData_Instance aChildToRemove : aChildrenToRemove) {
                aParent.RemoveInstance(aChildToRemove);
            }
        }

        // Save the result
        aModel.Save(new Base_UTF16String(anOutput));
    }
}

class RemovedSGEFinder extends ModelData_Model.VoidElementVisitor {
    private Base_UTF16String myNameToRemove;
    private HashMap<ModelData_Assembly, List<ModelData_Instance>> mySGEsToRemove;

    public RemovedSGEFinder(Base_UTF16String theNameToRemove) {
        myNameToRemove = theNameToRemove;
        mySGEsToRemove = new HashMap<>();
    }

    /* Non-root SGEs that can be removed are under assemblies. Iterate
       through the assembly's child instances and find those that reference
       SGEs with given name
    */
    @Override
    public boolean VisitEnter(ModelData_Assembly theElement) {
        ModelData_Model.ElementIterator anIt = new ModelData_Model.ElementIterator(theElement);
        while (anIt.HasNext()) {
            ModelData_Instance aChild = ModelData_Instance.Cast(anIt.Next());

            if (aChild.Reference() != null && aChild.Reference().Name().equals(myNameToRemove)) {
                RemoveElement(aChild, theElement);
            }
        }

        return true;
    }

    public HashMap<ModelData_Assembly, List<ModelData_Instance>> SGEsToRemove() {
        return mySGEsToRemove;
    }

    private void RemoveElement(ModelData_Instance theElement, ModelData_Assembly theParent) {
        if (mySGEsToRemove.containsKey(theParent)) {
            mySGEsToRemove.get(theParent).add(theElement);
        } else {
            mySGEsToRemove.put(theParent, new ArrayList<>(Arrays.asList(theElement)));
        }
    }
}

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

import java.util.Stack;

public class transformations {
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

        // Visitor to check and print trasformations of instances
        InstancesTransformationsVisitor aVisitor = new InstancesTransformationsVisitor();
        aModel.Accept(aVisitor);
    }
}

class InstancesTransformationsVisitor extends ModelData_Model.VoidElementVisitor {
    public InstancesTransformationsVisitor() {
        // We are going to multiply each matrix to produce transformations relative to the SceneGraph root
        ModelData_Transformation anIdentity = new ModelData_Transformation();
        myTransformationMatrix.push(anIdentity);
    }

    @Override
    public boolean VisitEnter(ModelData_Instance theInstance) {
        if (theInstance.HasTransformation()) {
            ModelData_Transformation aTrsf = theInstance.Transformation();
            myTransformationMatrix.push(myTransformationMatrix.peek().Multiplied(aTrsf));
        } else {
            ModelData_Transformation anIdentity = new ModelData_Transformation();
            myTransformationMatrix.push(anIdentity);
        }

        PrintTransformation(theInstance.Name());

        return true;
    }

    @Override
    public void VisitLeave(ModelData_Instance theInstance) {
        myTransformationMatrix.pop();
    }

    private void PrintTransformation(Base_UTF16String theName) {
        // Print instance name
        if (theName.IsEmpty()) {
            theName = new Base_UTF16String("noName");
        }
        System.out.println("Instance " + theName + " has transformations:");

        ModelData_Transformation.RotationPart aR = myTransformationMatrix.peek().GetRotationPart();

        ModelData_Vector aTranslation = myTransformationMatrix.peek().TranslationPart();
        System.out.println("| " + aR.v00 + " " + aR.v01 + " " + aR.v02 + " " + aTranslation.X() + " |");
        System.out.println("| " + aR.v10 + " " + aR.v11 + " " + aR.v12 + " " + aTranslation.Y() + " |");
        System.out.println("| " + aR.v20 + " " + aR.v21 + " " + aR.v22 + " " + aTranslation.Z() + " |");
    }

    private Stack<ModelData_Transformation> myTransformationMatrix = new Stack<>();
}

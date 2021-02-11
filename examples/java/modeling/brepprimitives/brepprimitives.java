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

public class brepprimitives {
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

        // Create a model
        ModelData_Model aModel = new ModelData_Model();

        // Create box
        CreateBox(new ModelData_Point(10., 0., 0.), 8., 8., 8., aModel);

        // Create sphere
        CreateSphere(new ModelData_Point(0., 10., 0.), 4., aModel);

        // Create cylinder
        CreateCylinder(new ModelData_Point(-10., 0., 0.), 4., 8., aModel);

        // Create cone
        CreateCone(new ModelData_Point(0., -10., 0.), 3., 5., 7., aModel);

        // Create torus
        CreateTorus(new ModelData_Point(0., 0., 0.), 2., 3., aModel);

        // Save the result
        if (!aModel.Save(new Base_UTF16String("Primitives.xml"))) {
            System.out.println("Unable to save the model!");
            System.exit(1);
        }
    }

    static void AttachPrimitiveToModel(Base_UTF16String theName, ModelData_Solid thePrimitive, ModelData_Model theModel) {
        ModelData_Part aPart = new ModelData_Part(new ModelData_BRepRepresentation(thePrimitive), theName);
        theModel.AddRoot(aPart);
    }

    static void CreateBox(ModelData_Point thePosition, double Dx, double Dy, double Dz, ModelData_Model theModel) {
        ModelData_Solid aBox = ModelAlgo_TopoPrimitives.CreateBox(thePosition, Dx, Dy, Dz);
        AttachPrimitiveToModel(new Base_UTF16String("Box"), aBox, theModel);
    }

    static void CreateSphere(ModelData_Point thePosition, double theRadius, ModelData_Model theModel) {
        ModelData_Solid aSphere = ModelAlgo_TopoPrimitives.CreateSphere(thePosition, theRadius);
        AttachPrimitiveToModel(new Base_UTF16String("Sphere"), aSphere, theModel);
    }

    static void CreateCylinder(ModelData_Point thePosition, double theRadius, double theHeight, ModelData_Model theModel) {
        ModelData_Axis2Placement anAxis = new ModelData_Axis2Placement(thePosition, ModelData_Direction.ZDir(), ModelData_Direction.YDir());

        ModelData_Solid aCylinder = ModelAlgo_TopoPrimitives.CreateCylinder(anAxis, theRadius, theHeight);
        AttachPrimitiveToModel(new Base_UTF16String("Cylinder"), aCylinder, theModel);
    }

    static void CreateCone(ModelData_Point thePosition, double theRadius1, double theRadius2, double theHeight, ModelData_Model theModel) {
        ModelData_Axis2Placement anAxis = new ModelData_Axis2Placement(thePosition, ModelData_Direction.ZDir(), ModelData_Direction.YDir());

        ModelData_Solid aCone = ModelAlgo_TopoPrimitives.CreateCone(anAxis, theRadius1, theRadius2, theHeight);
        AttachPrimitiveToModel(new Base_UTF16String("Cone"), aCone, theModel);
    }

    static void CreateTorus(ModelData_Point thePosition, double theMinRadius, double theMaxRadius, ModelData_Model theModel) {
        ModelData_Axis2Placement anAxis = new ModelData_Axis2Placement(thePosition, ModelData_Direction.ZDir(), ModelData_Direction.YDir());

        ModelData_Solid aTorus = ModelAlgo_TopoPrimitives.CreateTorus(anAxis, theMaxRadius, theMinRadius);
        AttachPrimitiveToModel(new Base_UTF16String("Torus"), aTorus, theModel);
    }
}

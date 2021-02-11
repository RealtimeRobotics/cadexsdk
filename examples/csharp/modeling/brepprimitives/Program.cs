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


using cadex;
using System;
using System.Runtime.InteropServices;

namespace brepprimitives
{
    class Program
    {
        // For more information see https://stackoverflow.com/questions/8836093/how-can-i-specify-a-dllimport-path-at-runtime
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool SetDllDirectory(string lpPathName);

        static int Main(string[] args)
        {
            // Add runtime path to CAD Exchanger libraries (e.g. compiled with Visual Studio 2015)
            SetDllDirectory("../../../../../../win64/vc14.1/bin");

            string aKey = LicenseKey.Value();

            // Activate the license (aKey must be defined in cadex_license.cs)
            if (!LicenseManager.Activate(aKey))
            {
                Console.WriteLine("Failed to activate CAD Exchanger license.");
                return 1;
            }

            ModelData_Model aModel = new ModelData_Model();

            CreateBox(new ModelData_Point(10.0, 0.0, 0.0), 8.0, 8.0, 8.0, aModel);

            CreateSphere(new ModelData_Point(0.0, 10.0, 0.0), 4.0, aModel);

            CreateCylinder(new ModelData_Point(-10.0, 0.0, 0.0), 4.0, 8.0, aModel);

            CreateCone(new ModelData_Point(0.0, -10.0, 0.0), 3.0, 5.0, 7.0, aModel);

            CreateTorus(new ModelData_Point(0.0, 0.0, 0.0), 2.0, 3.0, aModel);

            // Save the result
            if (!aModel.Save(new Base_UTF16String("Primitives.xml")))
            {
                Console.WriteLine("Unable to save the model!");
                return 1;
            }

            return 0;
        }

        static void AttachPrimitiveToModel(string theName, ModelData_Solid thePrimitive, ModelData_Model theModel)
        {
            ModelData_Part aPart = new ModelData_Part(new ModelData_BRepRepresentation(thePrimitive), new Base_UTF16String(theName));
            theModel.AddRoot(aPart);

        }

        static void CreateBox(ModelData_Point thePosition,
                               double Dx,
                               double Dy,
                               double Dz,
                               ModelData_Model theModel)
        {
            ModelData_Solid aBox = ModelAlgo_TopoPrimitives.CreateBox(thePosition, Dx, Dy, Dz);
            AttachPrimitiveToModel("Box", aBox, theModel);
        }

        static void CreateSphere(ModelData_Point thePosition,
                                 double theRadius,
                                 ModelData_Model theModel)
        {
            ModelData_Solid aSphere = ModelAlgo_TopoPrimitives.CreateSphere(thePosition, theRadius);
            AttachPrimitiveToModel("Sphere", aSphere, theModel);
        }

        static void CreateCylinder(ModelData_Point thePosition, double theRadius, double theHeight, ModelData_Model theModel)
        {
            ModelData_Axis2Placement anAxis = new ModelData_Axis2Placement(thePosition, ModelData_Direction.ZDir(), ModelData_Direction.YDir());
            ModelData_Solid aCylinder = ModelAlgo_TopoPrimitives.CreateCylinder(anAxis, theRadius, theHeight);
            AttachPrimitiveToModel("Cylinder", aCylinder, theModel);
        }

        static void CreateCone(ModelData_Point thePosition, double theRadius1, double theRadius2, double theHeight, ModelData_Model theModel)
        {
            ModelData_Axis2Placement anAxis = new ModelData_Axis2Placement(thePosition, ModelData_Direction.ZDir(), ModelData_Direction.YDir());
            ModelData_Solid aCone = ModelAlgo_TopoPrimitives.CreateCone(anAxis, theRadius1, theRadius2, theHeight);
            AttachPrimitiveToModel("Cone", aCone, theModel);
        }

        static void CreateTorus(ModelData_Point thePosition, double theMinRadius, double theMaxRadius, ModelData_Model theModel)
        {
            ModelData_Axis2Placement anAxis = new ModelData_Axis2Placement(thePosition, ModelData_Direction.ZDir(), ModelData_Direction.YDir());
            ModelData_Solid aTorus = ModelAlgo_TopoPrimitives.CreateTorus(anAxis, theMaxRadius, theMinRadius);
            AttachPrimitiveToModel("Torus", aTorus, theModel);
        }
    }
}

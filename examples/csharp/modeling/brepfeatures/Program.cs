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

namespace brepfeatures
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

            // Extrusion
            // Edge to Face
            ModelData_Line anExtrusionLine = new ModelData_Line(new ModelData_Point(-2.0, 0.0, -4.0), ModelData_Direction.XDir());
            ModelData_Edge anExtrusionEdge = new ModelData_Edge(anExtrusionLine, 0.0, 4.0);
            var aPlane = ModelAlgo_BRepFeatures.CreateExtrusion(anExtrusionEdge, new ModelData_Vector(0.0, 4.0, 0.0));

            // Face to Solid
            var aBlock = ModelAlgo_BRepFeatures.CreateExtrusion(aPlane, new ModelData_Vector(0.0, 0.0, 8.0));

            // Revolution
            // Edge to Face
            ModelData_Line aRevolutionLine = new ModelData_Line(new ModelData_Point(10.0, 0.0, 0.0), ModelData_Direction.ZDir());
            ModelData_Edge aRevolutionEdge = new ModelData_Edge(aRevolutionLine, 1.0, 3.0);
            var aCircularPlane = ModelAlgo_BRepFeatures.CreateRevolution(aRevolutionEdge,
                                                                          new ModelData_Axis1Placement(new ModelData_Point(10.0, 0.0, 0.0),
                                                                          ModelData_Direction.YDir()), Math.PI * 2);
            // Face to Solid
            var aTunnel = ModelAlgo_BRepFeatures.CreateRevolution(aCircularPlane, ModelData_Axis1Placement.OZ(), Math.PI);

            // Create a model
            ModelData_Model aModel = new ModelData_Model();
            ModelData_BRepRepresentation aBRepB = new ModelData_BRepRepresentation(aBlock);
            ModelData_Part anExtrusionPart = new ModelData_Part(aBRepB, new Base_UTF16String("Block"));
            aModel.AddRoot(anExtrusionPart);

            ModelData_BRepRepresentation aBRepT = new ModelData_BRepRepresentation(aTunnel);
            ModelData_Part aRevolutionPart = new ModelData_Part(aBRepT, new Base_UTF16String("Tunnel"));
            aModel.AddRoot(aRevolutionPart);

            // Save the result
            if (!aModel.Save(new Base_UTF16String("Features.xml")))
            {
                Console.WriteLine("Unable to save the model!");
                return 1;
            }

            return 0;
        }
    }
}

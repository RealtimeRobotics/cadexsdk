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

namespace metadata
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

            // Create a simple box
            ModelData_Solid aBox = ModelAlgo_TopoPrimitives.CreateBox(5.0, 5.0, 5.0);
            ModelData_BRepRepresentation aBRep = new ModelData_BRepRepresentation(aBox);

            // Color the box
            ModelData_Shape.Iterator aFaceIt = new ModelData_Shape.Iterator(aBox, ModelData_ShapeType.ModelData_ST_Face);
            int r = 10, g = 10, b = 250, a = 255;
            while (aFaceIt.HasNext())
            {
                a -= 30;
                ModelData_Shape aFace = aFaceIt.Next();
                ModelData_Appearance anApp = new ModelData_Appearance(new ModelData_Color(r, g, b, a));
                aBRep.SetAppearance(aFace, anApp);

            }

            // Change properties
            ModelData_Part aPart = new ModelData_Part(aBRep, new Base_UTF16String("ColorBox"));
            ModelData_PropertyTable aTable = new ModelData_PropertyTable();
            aTable.Add(new Base_UTF16String("Color"), new Base_UTF16String("Different"));
            aPart.AddProperties(aTable);

            ModelData_Model aModel = new ModelData_Model();
            aModel.AddRoot(aPart);
            aModel.Save(new Base_UTF16String("ColorBox.xml"));

            return 0;
        }
    }
}

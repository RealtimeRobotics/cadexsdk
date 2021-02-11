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

namespace meshsimplify
{
    class TriangleCounter : ModelData_Model.VoidElementVisitor
    {
        class PolyRepExplorer : ModelData_Part.VoidRepresentationVisitor
        {
            public override void Apply(ModelData_PolyRepresentation theRep)
            {
                var aShapeList = theRep.Get();
                for (uint i = 0; i < aShapeList.Size(); i++)
                {
                    ModelData_PolyShape aShape = aShapeList.Element(i);
                    if (aShape.TypeId() == ModelData_IndexedTriangleSet.GetTypeId())
                    {
                        var anITS = ModelData_IndexedTriangleSet.Cast(aShape);
                        myNumberOfTriangles += anITS.NumberOfFaces();
                    }
                }
            }

            public int myNumberOfTriangles = 0;
        }

        public override void Apply(ModelData_Part thePart)
        {
            PolyRepExplorer aRepExplorer = new PolyRepExplorer();
            thePart.Accept(aRepExplorer);
            myNumberOfTriangles += aRepExplorer.myNumberOfTriangles;
        }

        public int NumberOfTriangles()
        {
            return myNumberOfTriangles;
        }

        private int myNumberOfTriangles = 0;
    }

    class Program
    {
        // For more information see https://stackoverflow.com/questions/8836093/how-can-i-specify-a-dllimport-path-at-runtime
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool SetDllDirectory(string lpPathName);

        static int Main(string[] args)
        {
            // Add runtime path to CAD Exchanger libraries (e.g. compiled with Visual Studio 2017)
            SetDllDirectory("../../../../../../win64/vc14.1/bin");

            string aKey = LicenseKey.Value();

            // Activate the license (aKey must be defined in cadex_license.cs)
            if (!LicenseManager.Activate(aKey))
            {
                Console.WriteLine("Failed to activate CAD Exchanger license.");
                return 1;
            }

            if (args.Length != 2)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file> <output_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the VRML file to be read");
                Console.WriteLine("    <output_file> is a name of the XML file to Save() the model");
                return 1;
            }

            string aSource = args[0];
            string aDest = args[1];

            VRML_Reader aReader = new VRML_Reader();

            ModelData_Model aModel = new ModelData_Model();

            // Reading the file
            if (!aReader.ReadFile(new Base_UTF16String(aSource)))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            // Making a model data
            if (!aReader.Transfer(aModel))
            {
                Console.WriteLine("Failed to transfer the model into inner format");
                return 1;
            }

            // Basic info about model
            TriangleCounter aBeforeCounter = new TriangleCounter();
            aModel.Accept(aBeforeCounter);
            Console.WriteLine("Model name: " + aModel.Name());
            Console.WriteLine("# of triangles before: " + aBeforeCounter.NumberOfTriangles());

            // Running the simplifier
            ModelSimplifier_MeshSimplifierParameters aParams = new ModelSimplifier_MeshSimplifierParameters();
            aParams.SetDegreeOfSimplification(ModelSimplifier_MeshSimplifierParameters.DegreeOfSimplificationType.High);

            ModelSimplifier_MeshSimplifier aSimplifier = new ModelSimplifier_MeshSimplifier();
            aSimplifier.SetParameters(aParams);
            ModelData_Model aNewModel = aSimplifier.Perform(aModel);

            // How many triangles does simplified model contain?
            TriangleCounter anAfterCounter = new TriangleCounter();
            aNewModel.Accept(anAfterCounter);
            Console.WriteLine("# of triangles after: " + anAfterCounter.NumberOfTriangles());

            // Saving the simplified model
            if (!aNewModel.Save(new Base_UTF16String(aDest)))
            {
                Console.WriteLine("Failed to save the .xml file");
                return 1;
            };

            return 0;
        }
    }
}
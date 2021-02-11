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
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace remeshing
{
    class MeshReplacementVisitor : ModelData_Model.VoidElementVisitor
    {
        public override bool VisitEnter(ModelData_Instance theInstance)
        {
            myInstances.Push(theInstance);
            return true;
        }

        public override void VisitLeave(ModelData_Instance theInstance)
        {
            myInstances.Pop();
        }

        public override void Apply(ModelData_Part thePart)
        {
            if (thePart.BRepRepresentation().IsNull())
            {
                return;
            }

            if (myReplacedParts.ContainsKey (thePart) && myInstances.Count > 0)
            {
                myInstances.Peek().SetReference (myReplacedParts[thePart]);
                return;
            }

            ModelData_Part aNewPart = new ModelData_Part(thePart.BRepRepresentation(), thePart.Name());
            aNewPart.SetAppearance (thePart.Appearance());
            aNewPart.AddProperties (thePart.Properties());
            aNewPart.AddPMI (thePart.PMI());
            for (var anIt = new ModelData_SceneGraphElement.LayerIterator(thePart); anIt.HasNext();)
            {
                aNewPart.AddToLayer (anIt.Next());
            }

            ModelAlgo_BRepMesherParameters aMesherParams = new ModelAlgo_BRepMesherParameters(ModelAlgo_BRepMesherParameters.Granularity.Fine);
            ModelAlgo_BRepMesher aMesher = new ModelAlgo_BRepMesher(aMesherParams);
            aMesher.Compute(aNewPart);

            if (myInstances.Count == 0)
            {
                RootReplacements.Add(thePart, aNewPart);
            }
            else
            {
                myReplacedParts.Add (thePart, aNewPart);
                myInstances.Peek().SetReference (aNewPart);
            }
        }

        public Dictionary<ModelData_Part, ModelData_Part> RootReplacements { get; } = new Dictionary<ModelData_Part, ModelData_Part>();

        private Stack<ModelData_Instance> myInstances = new Stack<ModelData_Instance>();
        private Dictionary<ModelData_Part, ModelData_Part> myReplacedParts = new Dictionary<ModelData_Part, ModelData_Part>();
    }

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

            if (args.Length != 2)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file> <output_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the SLD file to be read");
                Console.WriteLine("    <output_file> is a name of the VRML file to be written");
                return 1;
            }

            string aSource = args[0];
            string aDest = args[1];

            ModelData_Model aModel = new ModelData_Model();

            Console.WriteLine("Conversion started...");

            SLD_Reader aReader = new SLD_Reader();

            if (!aReader.ReadFile(new Base_UTF16String(aSource)))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            // Converting into inner format
            if (!aReader.Transfer(aModel))
            {
                Console.WriteLine("Failed to transfer the file into inner format.");
                return 1;
            }

            MeshReplacementVisitor aVisitor = new MeshReplacementVisitor();
            aModel.Accept(aVisitor);
            List <ModelData_SceneGraphElement> aNewRoots = new List<ModelData_SceneGraphElement>();
            for (var anIt = new ModelData_Model.ElementIterator(aModel); anIt.HasNext();)
            {
                var aRoot = anIt.Next();
                if (aRoot.TypeId() == ModelData_Part.GetTypeId())
                {
                    var aRootPart = ModelData_Part.Cast(aRoot);
                    Debug.Assert(aVisitor.RootReplacements.ContainsKey(aRootPart), "Part was not processed");
                    aNewRoots.Add(aVisitor.RootReplacements[aRootPart]);

                }
                else
                {
                    aNewRoots.Add(aRoot);
                }
            }
            aModel.Clear();
            foreach (ModelData_SceneGraphElement aNewRoot in aNewRoots)
            {
                aModel.AddRoot (aNewRoot);
            }

            VRML_Writer aWriter = new VRML_Writer();

            // Converting from inner format
            if (!aWriter.Transfer(aModel))
            {
                Console.WriteLine("Failed to transfer the file from inner format.");
                return 1;
            }

            if (!aWriter.WriteFile(new Base_UTF16String(aDest)))
            {
                Console.WriteLine("Failed to write the file...", aDest);
                return 1;
            }

            return 0;
        }
    }
}

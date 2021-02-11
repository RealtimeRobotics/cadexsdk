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
using System.Runtime.InteropServices;

namespace elementremoval
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

            if (args.Length != 3)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location +
                                  " <input_file> <output_file> <sge_to_remove>, where:");
                Console.WriteLine("    <input_file>  is a name of the XML file to be read");
                Console.WriteLine("    <output_file>   is a name of the XML file where the output should be stored");
                Console.WriteLine("    <sge_to_remove> is a name of the scene graph elements to remove");
                return 1;
            }

            string aSource = args[0];
            string anOutput = args[1];

            // Load the model
            ModelData_Model aModel = new ModelData_Model();

            if (!aModel.Open(new Base_UTF16String(aSource)))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            // Remove roots with specified name
            string aNameToRemove = args[2];
            List<ModelData_SceneGraphElement> aRootsToRemove = new List<ModelData_SceneGraphElement>();
            for (var anIt = new ModelData_Model.ElementIterator(aModel); anIt.HasNext();)
            {
                var anElement = anIt.Next();
                if (anElement.Name().Equals(new Base_UTF16String(aNameToRemove)))
                {
                    aRootsToRemove.Add(anElement);
                }
            }

            foreach (var aRootToRemove in aRootsToRemove)
            {
                aModel.RemoveRoot(aRootToRemove);
            }

            // Find the rest of scene graph elements that need to be removed and their parents
            RemovedSGEFinder aFinder = new RemovedSGEFinder(new Base_UTF16String(aNameToRemove));
            aModel.Accept(aFinder);

            // Perform the recorded removals of non-root SGEs
            foreach (var aParentWithChildren in aFinder.SGEsToRemove)
            {
                var aParent = aParentWithChildren.Key;
                var aChildrenToRemove = aParentWithChildren.Value;

                foreach (var aChildToRemove in aChildrenToRemove)
                {
                    aParent.RemoveInstance(aChildToRemove);
                }
            }

            // Save the result
            aModel.Save(new Base_UTF16String(anOutput));

            return 0;
        }
    }

    class RemovedSGEFinder : ModelData_Model.VoidElementVisitor
    {
        private Base_UTF16String myNameToRemove;

        public Dictionary<ModelData_Assembly, List<ModelData_Instance>> SGEsToRemove { get; set; }

        public RemovedSGEFinder(Base_UTF16String theNameToRemove)
        {
            myNameToRemove = theNameToRemove;
            SGEsToRemove = new Dictionary<ModelData_Assembly, List<ModelData_Instance>>();
        }

        // Non-root SGEs that can be removed are under assemblies. Iterate
        // through the assembly's child instances and find those that reference
        // SGEs with given name
        public override bool VisitEnter(ModelData_Assembly theElement)
        {
            for (var anIt = new ModelData_Model.ElementIterator(theElement); anIt.HasNext();)
            {
                var aChild = ModelData_Instance.Cast(anIt.Next());

                if (aChild.Reference() != null && aChild.Reference().Name().Equals(myNameToRemove))
                {
                    RemoveElement(aChild, theElement);
                }
            }

            return true;
        }

        private void RemoveElement(ModelData_Instance theElement, ModelData_Assembly theParent)
        {
            if (SGEsToRemove.ContainsKey(theParent))
            {
                SGEsToRemove[theParent].Add(theElement);
            }
            else
            {
                SGEsToRemove[theParent] = new List<ModelData_Instance>() { theElement } ;
            }
        }
    }
}

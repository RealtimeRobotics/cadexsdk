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

namespace bom
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

            if (args.Length != 1)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the XML file to be read");
                return 1;
            }

            string aSource = args[0];

            // Load the model
            ModelData_Model aModel = new ModelData_Model();

            if (!aModel.Open(new Base_UTF16String(aSource)))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            // Create a Counter
            SceneGraphVisitor aCounter = new SceneGraphVisitor();
            aModel.Accept(aCounter);
            aCounter.PrintCounts();

            return 0;
        }
    }

    class SceneGraphVisitor : ModelData_Model.ElementVisitor
    {
        public SceneGraphVisitor()
        {
            myNestingLevel = 0;
            margin = 0;
        }

        public void PrintCounts()
        {
            Console.WriteLine("Total:");
            Console.WriteLine("\t{0,8:c}", "name".PadRight(margin, ' ') + " | " + "type".PadRight(margin, ' ') + " | count");

            foreach (KeyValuePair<ModelData_BaseObject, int> i in mySGEMap)
            {
                Console.WriteLine("\t{0,8:c}", i.Key.Name().ToString().PadRight(margin, ' ') + " | " + PrintSGEType(i.Key).PadRight(margin, ' ') + " | " + i.Value);
            }
        }

        public override void Apply(ModelData_Part thePart)
        {
            PrintName("Part", thePart.Name());
            UpdateTable(thePart);
        }

        public override bool VisitEnter(ModelData_Assembly theAssembly)
        {
            PrintName("Assembly", theAssembly.Name());
            UpdateTable(theAssembly);
            ++myNestingLevel;
            return true;
        }

        public override bool VisitEnter(ModelData_Instance theInstance)
        {
            PrintName("Instance", theInstance.Name());
            ++myNestingLevel;
            return true;
        }

        public override void VisitLeave(ModelData_Assembly theAssembly)
        {
            --myNestingLevel;
        }

        public override void VisitLeave(ModelData_Instance theInstance)
        {
            --myNestingLevel;
        }

        private void PrintName(string theSGElement, Base_UTF16String theName)
        {
            for (int i = 0; i < myNestingLevel; ++i)
            {
                Console.Write("--- ");
            }

            if (!theName.IsEmpty())
            {
                Console.WriteLine(theSGElement + ": " + theName);
            }
            else
            {
                Console.WriteLine(theSGElement + ": <noname>");
            }

            // Calculating spacing for output table columns
            margin = Math.Max(margin, (int)theName.Length());
        }

        private void UpdateTable(ModelData_SceneGraphElement theSGE)
        {
            if (!mySGEMap.ContainsKey(theSGE))
            {
                mySGEMap.Add(theSGE, 1);
            }
            else
            {
                ++mySGEMap[theSGE];
            }
        }

        private string PrintSGEType(ModelData_BaseObject theSGE)
        {
            if (theSGE.TypeId() == ModelData_Part.GetTypeId())
            {
                return "Part";
            }
            else if (theSGE.TypeId() == ModelData_Assembly.GetTypeId())
            {
                return "Assembly";
            }
            else if (theSGE.TypeId() == ModelData_Instance.GetTypeId())
            {
                return "Instance";
            }
            return "Undefined";
        }

        private int margin; // This variable used only for formating output table
        private Dictionary<ModelData_BaseObject, int> mySGEMap = new Dictionary<ModelData_BaseObject, int>(new ModelData_BaseObjectHash());
        private int myNestingLevel;
    }
}

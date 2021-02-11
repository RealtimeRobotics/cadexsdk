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

namespace propertytable
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

            ModelData_Model aModel = new ModelData_Model();

            if (!aModel.Open(new Base_UTF16String(aSource)))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            PropertiesVisitor aVisitor = new PropertiesVisitor();
            aModel.Accept(aVisitor);

            return 0;
        }
    }

    class PropertiesVisitor : ModelData_Model.CombinedElementVisitor
    {
        public override void Apply(ModelData_Part thePart)
        {
            ModelData_PropertyTable aPT = thePart.Properties();
            ExplorePropertyTable(aPT);

            ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
            if (aBRep != null)
            {
                SubShapePropertiesVisitor aVisitor = new SubShapePropertiesVisitor(aBRep);
                aBRep.Accept(aVisitor);

                // Extract all PropertyTables from SubShapes in B-Rep and explore it
                List<ModelData_PropertyTable> aPTList = aVisitor.PropertyTables();
                for (int i = 0; i < aPTList.Count; ++i)
                {
                    ExplorePropertyTable(aPTList[i]);
                }
            }
        }

        public override bool VisitEnter(ModelData_SceneGraphElement theElement)
        {
            ModelData_PropertyTable aPT = theElement.Properties();
            ExplorePropertyTable(aPT);

            return true;
        }

        private List<ModelData_PropertyTable> ExtractPropertyTables(ModelData_BRepRepresentation theBRep)
        {
            List<ModelData_PropertyTable> aPTList = new List<ModelData_PropertyTable>();
            ModelData_BodyList aBodyList = theBRep.Get();
            for (uint i = 0; i < aBodyList.Size(); ++i)
            {
                ModelData_Body aBody = aBodyList.Element(i);
                aPTList.Add(theBRep.PropertyTable(aBody));
            }
            return aPTList;
        }

        private void ExplorePropertyTable(ModelData_PropertyTable thePT)
        {
            if (thePT != null && !thePT.IsEmpty())
            {
                PropertyVisitor aPropVisitor = new PropertyVisitor();
                thePT.Accept(aPropVisitor);
            }
            else
            {
                Console.WriteLine("\nProperty Table is empty");
            }
        }
    }

    class PropertyVisitor : ModelData_PropertyTable.VoidVisitor
    {
        public PropertyVisitor()
        {
            Console.WriteLine("\nProperty table: ");
        }

        public override void Apply(Base_UTF16String theName, int theValue)
        {
            OutputData(theName, theValue);
        }

        public override void Apply(Base_UTF16String theName, double theValue)
        {
            OutputData(theName, theValue);
        }

        public override void Apply(Base_UTF16String theName, Base_UTF16String theValue)
        {
            OutputData(theName, theValue);
        }


        private void OutputData<T>(Base_UTF16String theName, T theValue)
        {
            Console.WriteLine(theName + ": " + theValue);
        }

        private void ExplorePropertyTable(ModelData_PropertyTable thePT)
        {
            // Traverse property table
            PropertyVisitor aPropVisitor = new PropertyVisitor();
            thePT.Accept(aPropVisitor);
        }
    }

    class SubShapePropertiesVisitor : ModelData_BRepRepresentation.SubshapeVisitor
    {
        public SubShapePropertiesVisitor(ModelData_BRepRepresentation theBRep)
        {
            myBRep = theBRep;
        }

        public List<ModelData_PropertyTable> PropertyTables()
        {
            return myPTList;
        }

        public override void Apply(ModelData_Shape theShape)
        {
            ModelData_PropertyTable aPT = myBRep.PropertyTable(theShape);
            myPTList.Add(aPT);
        }

        private ModelData_BRepRepresentation myBRep;
        private List<ModelData_PropertyTable> myPTList = new List<ModelData_PropertyTable>();
    }
}

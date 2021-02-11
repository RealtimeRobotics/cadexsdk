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

namespace appearance
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

            // Explore model's appearances
            AppearancesCollector aCollector = new AppearancesCollector(aModel);

            // Print the number of unique appearances in our model
            aCollector.PrintAppearancesCount();

            return 0;
        }
    }

    class SubshapeAppearancesCollector : ModelData_BRepRepresentation.SubshapeVisitor
    {
        public SubshapeAppearancesCollector(ModelData_BRepRepresentation theBRep, HashSet<ModelData_Appearance> theAppSet)
        {
            myBRep = theBRep;
            myAppSet = theAppSet;
        }

        public override void Apply(ModelData_Shape theShape)
        {
            ExploreShapeAppearances(theShape);
        }

        private void ExploreShapeAppearances(ModelData_Shape theShape)
        {
            ModelData_Appearance anApp = myBRep.Appearance(theShape);
            if (anApp != null)
            {
                myAppSet.Add(anApp);
            }
        }

        private HashSet<ModelData_Appearance> myAppSet = new HashSet<ModelData_Appearance>(new ModelData_AppearanceHash());
        private ModelData_BRepRepresentation myBRep;
    }

    class RepVisitor : ModelData_Part.RepresentationVisitor
    {
        public RepVisitor(HashSet<ModelData_Appearance> theAppSet)
        {
            myAppSet = theAppSet;
        }

        public override void Apply(ModelData_BRepRepresentation theBRep)
        {
            SubshapeAppearancesCollector aCollector = new SubshapeAppearancesCollector(theBRep, myAppSet);
            theBRep.Accept(aCollector);
        }

        public override void Apply(ModelData_PolyRepresentation thePolyRep)
        {
            ExplorePVSAppearances(thePolyRep);
        }

        private void ExplorePVSAppearances(ModelData_PolyRepresentation thePolyRep)
        {
            ModelData_PolyShapeList aList = thePolyRep.Get();
            for (uint i = 0; i < aList.Size(); ++i)
            {
                ModelData_PolyVertexSet aPVS = aList.Element(i);
                ModelData_Appearance anApp = aPVS.Appearance();
                if (anApp != null)
                {
                    myAppSet.Add(anApp);
                }
            }
        }

        private HashSet<ModelData_Appearance> myAppSet = new HashSet<ModelData_Appearance>(new ModelData_AppearanceHash());
    }

    class SGEAppearancesCollector : ModelData_Model.CombinedElementVisitor
    {
        public SGEAppearancesCollector(HashSet<ModelData_Appearance> theAppSet)
        {
            myAppSet = theAppSet;
        }

        public override void Apply(ModelData_Part thePart)
        {
            ExploreSGEAppearance(thePart);

            RepVisitor aVisitor = new RepVisitor(myAppSet);
            thePart.Accept(aVisitor);
        }

        public override bool VisitEnter(ModelData_SceneGraphElement theElement)
        {
            ExploreSGEAppearance(theElement);
            return true;
        }

        // Collects SceneGraphElement appearance
        private void ExploreSGEAppearance(ModelData_SceneGraphElement theSGE)
        {
            ModelData_Appearance anApp = theSGE.Appearance();
            if (anApp != null)
            {
                myAppSet.Add(anApp);
            }
        }

        private HashSet<ModelData_Appearance> myAppSet = new HashSet<ModelData_Appearance>(new ModelData_AppearanceHash());
    }

    class AppearancesCollector
    {
        public AppearancesCollector(ModelData_Model theModel)
        {
            myModel = theModel;
            SGEAppearancesCollector aCollector = new SGEAppearancesCollector(myAppSet);
            myModel.Accept(aCollector);
        }

        public void PrintAppearancesCount()
        {
            Console.WriteLine("Total model unique Appearances count: " + myAppSet.Count);
        }

        private HashSet<ModelData_Appearance> myAppSet = new HashSet<ModelData_Appearance>(new ModelData_AppearanceHash());
        private ModelData_Model myModel;
    }
}

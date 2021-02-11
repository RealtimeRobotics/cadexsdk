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

namespace layers
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

            // Check the model if it has any layer
            ModelData_Model.LayerIterator aLayerIt = new ModelData_Model.LayerIterator(aModel);
            if (!aLayerIt.HasNext())
            {
                // Create a visitor to fill its layers
                LayersFiller aVisitor = new LayersFiller();
                aModel.Accept(aVisitor);

                // Add created layers to the model
                aModel.AddLayer(aVisitor.SGELayer());
                aModel.AddLayer(aVisitor.SubShapesLayer());
            }
            LayersVisitor aLayerVisitor = new LayersVisitor();
            aModel.Accept(aLayerVisitor);

            return 0;
        }
    }

    // Visitor checks elements of specific layer
    class LayerItemVisitor : ModelData_Layer.ItemVisitor
    {
        public LayerItemVisitor()
        {
            myPartsNb = 0;
            myAssembliesNb = 0;
            myInstancesNb = 0;
            myShapesNb = 0;
        }

        public void GetElementsCount()
        {
            Console.WriteLine("Number of parts:      " + myPartsNb);
            Console.WriteLine("Number of assemblies: " + myAssembliesNb);
            Console.WriteLine("Number of instances:  " + myInstancesNb);
            Console.WriteLine("Number of shapes:     " + myShapesNb);

        }

        public override void Apply(ModelData_SceneGraphElement theSGE)
        {
            if (theSGE.TypeId() == ModelData_Part.GetTypeId())
            {
                ++myPartsNb;
            }
            else if (theSGE.TypeId() == ModelData_Assembly.GetTypeId())
            {
                ++myAssembliesNb;
            }
            else if (theSGE.TypeId() == ModelData_Instance.GetTypeId())
            {
                ++myInstancesNb;
            }
        }

        public override void Apply(ModelData_Shape theShape, ModelData_BRepRepresentation theRep)
        {
            ++myShapesNb;
        }

        private int myPartsNb;
        private int myAssembliesNb;
        private int myInstancesNb;
        private int myShapesNb;
    }

    // Visitor to explore model layers
    class LayersVisitor : ModelData_Model.LayerVisitor
    {
        public override void Apply(ModelData_Layer theLayer)
        {
            LayerItemVisitor aLayerItemVisitor = new LayerItemVisitor();
            theLayer.Accept(aLayerItemVisitor);
            Console.WriteLine("Layer " + theLayer.Name() + " contains:");
            aLayerItemVisitor.GetElementsCount();

        }
    }

    // Visitor used to add model's parts to layer
    class LayersFiller : ModelData_Model.CombinedElementVisitor
    {
        public LayersFiller()
        {
            ModelData_Layer mySubshapesLayer = new ModelData_Layer(new Base_UTF16String("SubshapesLayer"));
            ModelData_Layer mySGELayer = new ModelData_Layer(new Base_UTF16String("SGELayer"));
        }

        public ModelData_Layer SGELayer()
        {
            return mySGELayer;
        }

        public ModelData_Layer SubShapesLayer()
        {
            return mySubshapesLayer;
        }

        public override void Apply(ModelData_Part thePart)
        {
            mySGELayer.Add(thePart);
            ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
            if (aBRep != null)
            {
                ModelData_BodyList aBodyList = aBRep.Get();
                for (uint i = 0; i < aBodyList.Size(); ++i)
                {
                    ModelData_Body aBody = aBodyList.Element(i);
                    aBRep.AddToLayer(aBody, mySubshapesLayer);
                }
            }
        }

        public override bool VisitEnter(ModelData_SceneGraphElement theElement)
        {
            mySGELayer.Add(theElement);
            return true;
        }

        private readonly ModelData_Layer mySubshapesLayer;
        private ModelData_Layer mySGELayer;
    }
}

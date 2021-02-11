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

namespace transformations
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

            // Visitor to check and print transformations of instances
            InstancesTransformationsVisitor aVisitor = new InstancesTransformationsVisitor();
            aModel.Accept(aVisitor);

            return 0;
        }
    }

    class InstancesTransformationsVisitor : ModelData_Model.VoidElementVisitor
    {
        public InstancesTransformationsVisitor()
        {
            // We are going to multiply each matrix to produce transformations relative to the SceneGraph root
            ModelData_Transformation anIdentity = new ModelData_Transformation();
            myTransformationMatrix.Push(anIdentity);
        }

        public override bool VisitEnter(ModelData_Instance theInstance)
        {
            ModelData_Transformation aTrsf = new ModelData_Transformation();
            if (theInstance.HasTransformation())
            {
                aTrsf = theInstance.Transformation();
            }

            ModelData_Transformation aCumulativeTrsf = myTransformationMatrix.Peek().Multiplied(aTrsf);
            myTransformationMatrix.Push(aCumulativeTrsf);
            PrintTransformation(theInstance.Name());
            return true;
        }

        private void PrintTransformation(Base_UTF16String theName)
        {
            if (theName.IsEmpty())
            {
                theName = new Base_UTF16String("noName");
            }
            Console.WriteLine("Instance " + theName + " has transformations:");

            // Current transformations are relative to the SceneGraph root
            double v00 = 0.0, v01 = 0.0, v02 = 0.0, v10 = 0.0, v11 = 0.0, v12 = 0.0, v20 = 0.0, v21 = 0.0, v22 = 0.0;
            myTransformationMatrix.Peek().RotationPart(ref v00, ref v01, ref v02, ref v10, ref v11, ref v12, ref v20, ref v21, ref v22);
            ModelData_Vector aTranslation = myTransformationMatrix.Peek().TranslationPart();
            Console.WriteLine("| " + v00 + " " + v01 + " " + v02 + " " + aTranslation.X() + " |");
            Console.WriteLine("| " + v10 + " " + v11 + " " + v12 + " " + aTranslation.Y() + " |");
            Console.WriteLine("| " + v20 + " " + v21 + " " + v22 + " " + aTranslation.Z() + " |");
        }

        public override void VisitLeave(ModelData_Instance theInstance)
        {
            myTransformationMatrix.Pop();
        }

        Stack<ModelData_Transformation> myTransformationMatrix = new Stack<ModelData_Transformation>();
    }
}

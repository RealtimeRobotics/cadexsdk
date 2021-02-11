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

namespace lods
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

            ModelData_BRepRepresentation aBRep = CreateSphereBRep(new ModelData_Point(0.0, 0.0, 0.0), 10);
            ModelData_Part aPart = new ModelData_Part(aBRep, new Base_UTF16String("Sphere"));

            AddPolyToPart(aPart, ModelAlgo_BRepMesherParameters.Granularity.Coarse);
            AddPolyToPart(aPart, ModelAlgo_BRepMesherParameters.Granularity.Medium);
            AddPolyToPart(aPart, ModelAlgo_BRepMesherParameters.Granularity.Fine);

            ModelData_Model aModel = new ModelData_Model();
            aModel.AddRoot(aPart);

            if (!aModel.Save(new Base_UTF16String("SphereWithLODs.xml")))
            {
                Console.WriteLine("Unable to save the model");
                return 1;
            }

            return 0;
        }

        private static int NumberOfTriangles(ModelData_PolyRepresentation thePoly)
        {
            int trianglesNB = 0;

            ModelData_PolyShapeList aList = thePoly.Get();
            for (uint i = 0; i < aList.Size(); ++i)
            {
                ModelData_PolyVertexSet aPVS = aList.Element(i);
                if (aPVS.TypeId() == ModelData_IndexedTriangleSet.GetTypeId())
                {
                    ModelData_IndexedTriangleSet anITS = ModelData_IndexedTriangleSet.Cast(aPVS);
                    trianglesNB += anITS.NumberOfFaces();
                }
            }
            return trianglesNB;
        }

        private static ModelData_BRepRepresentation CreateSphereBRep(ModelData_Point thePosition, double theRadius)
        {
            ModelData_Solid aSphere = ModelAlgo_TopoPrimitives.CreateSphere(thePosition, theRadius);
            ModelData_Body aBody = ModelData_Body.Create(aSphere);
            ModelData_BRepRepresentation aBRep = new ModelData_BRepRepresentation(aBody);
            return aBRep;
        }

        private static void AddPolyToPart(ModelData_Part thePart, ModelAlgo_BRepMesherParameters.Granularity theLOD)
        {
            ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
            ModelAlgo_BRepMesherParameters aParam = new ModelAlgo_BRepMesherParameters(theLOD);
            ModelAlgo_BRepMesher aMesher = new ModelAlgo_BRepMesher(aParam);

            ModelData_PolyRepresentation aPoly = aMesher.Compute(aBRep);

            thePart.AddRepresentation(aPoly);
            Console.WriteLine("A polygonal representation with " + NumberOfTriangles(aPoly) + " triangles has been added");
        }
    }
}

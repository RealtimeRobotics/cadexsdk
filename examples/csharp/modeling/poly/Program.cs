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

namespace poly
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

            // Create PolyPointSet and explore it
            ModelData_PolyPointSet aPPS = CreatePolyPointSet();

            // Create PolyLineSet and explore it
            ModelData_PolyLineSet aPLS = CreatePolyLineSet();

            // Create IndexedTriangleSet and explore it
            ModelData_IndexedTriangleSet anITS = CreateITS();

            ModelData_PolyRepresentation aPolyWithPPS = new ModelData_PolyRepresentation(aPPS);
            ModelData_PolyRepresentation aPolyWithPLS = new ModelData_PolyRepresentation(aPLS);
            ModelData_PolyRepresentation aPolyWithITS = new ModelData_PolyRepresentation(anITS);

            ModelData_Part aPart = new ModelData_Part();

            aPart.AddRepresentation(aPolyWithPPS);
            aPart.AddRepresentation(aPolyWithPLS);
            aPart.AddRepresentation(aPolyWithITS);

            ModelData_Model aModel = new ModelData_Model();
            aModel.AddRoot(aPart);
            aModel.Save(new Base_UTF16String("Poly.xml"));

            return 0;
        }

        static ModelData_PolyPointSet CreatePolyPointSet()
        {
            ModelData_PointList aPoints1 = new ModelData_PointList();
            ModelData_PointList aPoints2 = new ModelData_PointList();

            for (int i = 0; i < 10; ++i)
            {
                aPoints1.Add(new ModelData_Point(i, 0, 0));
                aPoints2.Add(new ModelData_Point(i, 0, i));
            }

            // It's possible to add as much containers of points to same PolyPointSet as you want
            ModelData_PolyPointSet aPPS = new ModelData_PolyPointSet();
            aPPS.Add(aPoints1); // aPPS.NumberOfVertices() == 10
            aPPS.Add(aPoints2); // aPPS.NumberOfVertices() == 20
            return aPPS;
        }

        // Create PLS from lists of points: each list builds a new PolyLine
        static ModelData_PolyLineSet CreatePolyLineSet()
        {
            ModelData_PointList aPoints1 = new ModelData_PointList();
            ModelData_PointList aPoints2 = new ModelData_PointList();

            for (int i = 0; i < 10; ++i)
            {
                aPoints1.Add(new ModelData_Point(i, 3, i / 2));
                aPoints2.Add(new ModelData_Point(i, 0, i % 2));
            }

            // For each new list of points there will be a new PolyLine
            ModelData_PolyLineSet aPLS = new ModelData_PolyLineSet();
            aPLS.AddPolyline(aPoints1); // aPLS.NumberOfPolyLines() == 1
            aPLS.AddPolyline(aPoints2); // aPLS.NumberOfPolyLines() == 2
            return aPLS;
        }

        // Creates ITS with full information provided
        static ModelData_IndexedTriangleSet CreateITS()
        {
            ModelData_PointList aCoords = new ModelData_PointList
            {
                new ModelData_Point ( 1.0,  1.0,  1.0),
                new ModelData_Point (-1.0,  1.0,  1.0),
                new ModelData_Point (-1.0, -1.0,  1.0),
                new ModelData_Point ( 1.0, -1.0,  1.0),
                new ModelData_Point ( 1.0,  1.0, -1.0),
                new ModelData_Point (-1.0,  1.0, -1.0),
                new ModelData_Point (-1.0, -1.0, -1.0),
                new ModelData_Point ( 1.0, -1.0, -1.0)

            };

            ModelData_IntList aVerticesIndices = new ModelData_IntList
            {
                0, 1, 2, 3, //1
                1, 0, 4, 5, //2
                2, 1, 5, 6, //3
                3, 2, 6, 7, //4
                0, 3, 7, 4, //5
                7, 6, 5, 4  //6
            };

            ModelData_IntList aCounts = new ModelData_IntList { 4, 4, 4, 4, 4, 4 };

            ModelData_VectorfList aNormals = new ModelData_VectorfList
            {
                new ModelData_Vectorf ( 0f,  0f,  1f),
                new ModelData_Vectorf ( 0f,  1f,  0f),
                new ModelData_Vectorf (-1f,  0f,  0f),
                new ModelData_Vectorf ( 0f, -1f,  0f),
                new ModelData_Vectorf ( 1f,  0f,  0f),
                new ModelData_Vectorf ( 0f,  0f, -1f),
            };

            ModelData_IntList aNormalsIndices = new ModelData_IntList
            {
                0, 0, 0, 0, //1
                1, 1, 1, 1, //2
                2, 2, 2, 2, //3
                3, 3, 3, 3, //4
                4, 4, 4, 4, //5
                5, 5, 5, 5  //6
            };

            ModelData_ColorList aColors = new ModelData_ColorList
            {
                new ModelData_Color (255,   0,   0),
                new ModelData_Color (  0, 255,   0),
                new ModelData_Color (  0,   0, 255),
                new ModelData_Color (255, 255,   0),
                new ModelData_Color (  0, 255, 255),
                new ModelData_Color (255, 255, 255)
            };

            ModelData_IntList aColorIndices = new ModelData_IntList
            {
                0, 0, 0, 0, //1
                1, 1, 1, 1, //2
                2, 2, 2, 2, //3
                3, 3, 3, 3, //4
                4, 4, 4, 4, //5
                5, 5, 5, 5  //6
            };

            ModelData_IndexedTriangleSet anITS = new ModelData_IndexedTriangleSet();
            anITS.AddCoordinates(aCoords, aVerticesIndices, aCounts);
            anITS.AddNormals(aNormals, aNormalsIndices, aCounts);
            anITS.AddColors(aColors, aColorIndices, aCounts);
            return anITS;
        }
    }
}

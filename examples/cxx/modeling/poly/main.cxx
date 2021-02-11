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


#include <cadex/Base_String.hxx>
#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelData_Color.hxx>
#include <cadex/ModelData_IndexedTriangleSet.hxx>
#include <cadex/ModelData_Point2d.hxx>
#include <cadex/ModelData_PolyLineSet.hxx>
#include <cadex/ModelData_PolyPointSet.hxx>
#include <cadex/ModelData_PolyRepresentation.hxx>
#include <cadex/ModelData_Vector.hxx>
#include <array>
#include <iostream>
#include <vector>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

// Simply creates PPS
ModelData_PolyPointSet CreatePolyPointSet()
{
    vector<ModelData_Point> aPoints1, aPoints2;
    for (int i = 0; i < 10; ++i) {
        aPoints1.push_back (ModelData_Point (i, 0, 0));
        aPoints2.push_back (ModelData_Point (i, 0, i));
    }

    // It's possible to add as much containers of points to same PolyPointSet as you want.
    ModelData_PolyPointSet aPPS;
    aPPS.Add (aPoints1.data(), aPoints1.size()); // aPPS.NumberOfVertices() == 10
    aPPS.Add (aPoints2.data(), aPoints2.size()); // aPPS.NumberOfVertices() == 20
    return aPPS;
}

// Creates PLS from vectors of points: each vector builds a new PolyLine
ModelData_PolyLineSet CreatePolyLineSet()
{
    vector<ModelData_Point> aPoints1, aPoints2;
    for (int i = 0; i < 10; ++i) {
        aPoints1.push_back (ModelData_Point (i, 3, i / 2));
        aPoints2.push_back (ModelData_Point (i, 0, i % 2));
    }

    // For each new vector of points there will be a new PolyLine
    ModelData_PolyLineSet aPLS;
    aPLS.AddPolyLine (aPoints1.data(), aPoints1.size()); // aPLS.NumberOfPolyLines() == 1
    aPLS.AddPolyLine (aPoints2.data(), aPoints2.size()); // aPLS.NumberOfPolyLines() == 2
    return aPLS;
}

// Creates ITS with full information provided
ModelData_IndexedTriangleSet CreateITS()
{
    // Here we create a simple cube
    array<ModelData_Point, 8> aCoords = {{
        ModelData_Point ( 1.,  1.,  1.), //top
        ModelData_Point (-1.,  1.,  1.),
        ModelData_Point (-1., -1.,  1.),
        ModelData_Point ( 1., -1.,  1.),
        ModelData_Point ( 1.,  1., -1.), //bot
        ModelData_Point (-1.,  1., -1.),
        ModelData_Point (-1., -1., -1.),
        ModelData_Point ( 1., -1., -1.)
    }};

    array<int, 24> aVerticesIndices = {{
        0, 1, 2, 3,    // 1
        1, 0, 4, 5,    // 2
        2, 1, 5, 6,    // 3
        3, 2, 6, 7,    // 4
        0, 3, 7, 4,    // 5
        7, 6, 5, 4,    // 6
    }};

    array<int, 6> aCounts = {{4, 4, 4, 4, 4, 4}};

    array<ModelData_Vectorf, 6> aNormals = {{
        ModelData_Vectorf ( 0.f,  0.f,  1.f), // 1
        ModelData_Vectorf ( 0.f,  1.f,  0.f), // 2
        ModelData_Vectorf (-1.f,  0.f,  0.f), // 3
        ModelData_Vectorf ( 0.f, -1.f,  0.f), // 4
        ModelData_Vectorf ( 1.f,  0.f,  0.f), // 5
        ModelData_Vectorf ( 0.f,  0.f, -1.f), // 6
    }};

    array<int, 24> aNormalsIndices = {{
        0, 0, 0, 0, // 1
        1, 1, 1, 1, // 2
        2, 2, 2, 2, // 3
        3, 3, 3, 3, // 4
        4, 4, 4, 4, // 5
        5, 5, 5, 5, // 6
    }};

    array<ModelData_Color, 6> aColors = {{
        ModelData_Color (255, 0,   0  ),
        ModelData_Color (0,   255, 0  ),
        ModelData_Color (0,   0,   255),
        ModelData_Color (255, 255, 0  ),
        ModelData_Color (0,   255, 255),
        ModelData_Color (255, 255, 255),
    }};

    array<int, 24> aColorsIndices = {{
        0, 0, 0, 0, // 1
        1, 1, 1, 1, // 2
        2, 2, 2, 2, // 3
        3, 3, 3, 3, // 4
        4, 4, 4, 4, // 5
        5, 5, 5, 5, // 6
    }};

    ModelData_IndexedTriangleSet anITS;
    anITS.AddCoordinates   (aCoords.data(),   aCoords.size(),   aVerticesIndices.data(), aCounts.data(), aCounts.size());
    anITS.AddNormals       (aNormals.data(),  aNormals.size(),  aNormalsIndices.data(),  aCounts.data(), aCounts.size());
    anITS.AddColors        (aColors.data(),   aColors.size(),   aColorsIndices.data(),   aCounts.data(), aCounts.size());
    return anITS;
}

int main()
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    // Create PolyPointSet and explore it
    ModelData_PolyPointSet aPPS = CreatePolyPointSet();

    // Create PolyLineSet and explore it
    ModelData_PolyLineSet aPLS = CreatePolyLineSet();

    // Create IndexedTriangleSet and explore it
    ModelData_IndexedTriangleSet anITS = CreateITS();

    ModelData_PolyRepresentation aPolyWithPPS (aPPS);
    ModelData_PolyRepresentation aPolyWithPLS (aPLS);
    ModelData_PolyRepresentation aPolyWithITS (anITS);

    ModelData_Part aPart;
    aPart.AddRepresentation (aPolyWithPPS);
    aPart.AddRepresentation (aPolyWithPLS);
    aPart.AddRepresentation (aPolyWithITS);

    ModelData_Model aModel;
    aModel.AddRoot (aPart);
    aModel.Save ("Poly.xml");

    return 0;
}

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


#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelAlgo_BRepMesher.hxx>
#include <cadex/ModelData_IndexedTriangleSet.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_Point2d.hxx>
#include <cadex/ModelData_PolyLineSet.hxx>
#include <cadex/ModelData_PolyPointSet.hxx>
#include <cadex/ModelData_PolyRepresentation.hxx>
#include <cadex/ModelData_PolyShapeList.hxx>
#include <iostream>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

static void DumpPolyPointSet (const ModelData_PolyPointSet& thePS)
{
    ModelData_PolyPointSet::IndexType n = thePS.NumberOfVertices();

    cout << "PolyPoint set contains " << n << " vertices" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Point " << i << ":" << endl;
        cout << "    Node coordinates:" << endl;
        const ModelData_PolyPointSet::CoordType& aP = thePS.Coordinate (i);
        cout << "    (" << aP.X() << ", " << aP.Y() << ", " << aP.Z() << ")" << endl;
    }
}

// Prints number of PolyLines and local coordinates for every vertex of each PolyLine
static void DumpPolyLineSet (const ModelData_PolyLineSet& thePLS)
{
    ModelData_PolyLineSet::IndexType n = thePLS.NumberOfPolyLines();

    cout << "PolyLine set contains " << n << " PolyLines" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "PolyLine " << i << ":" << endl;
        cout << "    Node coordinates:" << endl;
        for (int j = 0; j < thePLS.NumberOfVertices (i); ++j) {
            const ModelData_PolyLineSet::CoordType& aV = thePLS.Coordinate (i, j);
            cout << "    (" << aV.X() << ", " << aV.Y() << ", " << aV.Z() << ")" << endl;
        }
    }
}

// Prints number of triangles and local data for each node
// Prints Coords and UV-Coords for each vertex and prints Normals and Colors for each triangle
static void DumpTriangleSet (const ModelData_IndexedTriangleSet& theTS)
{
    ModelData_IndexedTriangleSet::IndexType n = theTS.NumberOfFaces();

    cout << "Triangle set contains " << n << " Triangles" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Triangle " << i << ":" << endl;

        for (int j = 0; j < 3; ++j) {
            cout << "    Node " << j << ":" << endl;
            // Coordinates
            const ModelData_IndexedTriangleSet::CoordType& aV = theTS.Coordinate (i, j);
            cout << "    Coordinates:    (" <<
                aV.X() << ", " << aV.Y() << ", " << aV.Z() << ")" << endl;

            // UV-coordinates
            if (theTS.HasUVCoordinates()) {
                const ModelData_Point2d& aUV = theTS.UVCoordinate (i, j);
                cout << "    UV coordinates: (" <<
                    aUV.X() << ", " << aUV.Y() << ")" << endl;
            }

            // Normals
            if (theTS.HasNormals()) {
                const ModelData_IndexedTriangleSet::NormalType& aN = theTS.VertexNormal (i, j);
                cout << "    Normal vector:  (" <<
                    aN.X() << ", " << aN.Y() << ", " << aN.Z() << ")" << endl;
            }

            // Colors
            if (theTS.HasColors()) {
                const ModelData_Color& aColor = theTS.VertexColor (i, j);
                cout << "    Color (RGBA):   (" <<
                    aColor.R() << ", " << aColor.G() << ", " << aColor.B() << ", " << aColor.A() << ")" << endl;
            }
        }
    }
}

// Function to print a PolyVertexSet info
static void PrintPVSInfo (const ModelData_PolyVertexSet& thePVS)
{
    if (thePVS.IsOfType<ModelData_IndexedTriangleSet>()) {
        cout << "IndexedTriangleSet type." << endl;
        const auto& anITS = static_cast<const ModelData_IndexedTriangleSet&> (thePVS);
        DumpTriangleSet (anITS);
    } else if (thePVS.IsOfType<ModelData_PolyLineSet>()) {
        cout << "PolyLineSet type" << endl;
        const auto& aPLS = static_cast<const ModelData_PolyLineSet&> (thePVS);
        DumpPolyLineSet (aPLS);
    } else if (thePVS.IsOfType<ModelData_PolyPointSet>()) {
        cout << "PolyPointSet type" << endl;
        const auto& aPPS = static_cast<const ModelData_PolyPointSet&> (thePVS);
        DumpPolyPointSet (aPPS);
    } else {
        cout << "Undefined type" << endl;
    }
}

// Explores PolyVertexSets of Poly representation
static void ExplorePoly (const ModelData_PolyRepresentation& thePoly)
{
    // Get() method retrieves PolyVertexSets listed in Poly representation by calling data providers flushing
    // Because of internal mechanics providers flushing is faster than for B-Rep representations
    const ModelData_PolyShapeList& aList = thePoly.Get();

    // Iterate over PolyShape list
    for (ModelData_PolyShapeList::SizeType i = 0; i < aList.Size(); ++i) {
        const ModelData_PolyVertexSet& aPVS = aList[i];
        cout << "PolyShape " << i << ":" << endl;
        PrintPVSInfo (aPVS);
    }
}

// Visits directly every part and calls Poly representation exploring if a part has one
class PartPolyVisitor : public ModelData_Model::VoidElementVisitor
{
protected:

    void operator() (const ModelData_Part& thePart) override
    {
        const ModelData_PolyRepresentation& aPolyRep = thePart.PolyRepresentation (ModelData_RM_Poly);
        if (aPolyRep) {
            ExplorePoly (aPolyRep);
        }
    }
};

int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    // Get the input
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>, where:" << endl;
        cerr << "    <input_file> is a name of the XML file to be read" << endl;
        return 1;
    }

    const char* aSource = argv[1];

    // Open the model
    ModelData_Model aModel;

    if (!aModel.Open (aSource)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }

    // If there is no Poly representation in the model, mesher will compute it
    ModelAlgo_BRepMesher aMesher (ModelAlgo_BRepMesherParameters::Fine);
    aMesher.Compute (aModel);

    // Explore Poly representation of model parts
    PartPolyVisitor aVisitor;
    aModel.Accept (aVisitor);

    return 0;
}

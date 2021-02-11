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
#include <cadex/ModelData_Body.hxx>
#include <cadex/ModelData_BodyList.hxx>
#include <cadex/ModelData_BodyType.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Curve.hxx>
#include <cadex/ModelData_Curve2d.hxx>
#include <cadex/ModelData_Edge.hxx>
#include <cadex/ModelData_Face.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_Surface.hxx>
#include <cadex/ModelData_Vertex.hxx>
#include <cadex/ModelData_Wire.hxx>
#include <array>
#include <iostream>
#include <unordered_set>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

// Define which level of equality we need in shape comparing
// Shapes comparison includes three components: entity, location and orientation
// There are two ways to compare shapes while using ShapeHashers: IsEqual() and IsSame()
// Two shapes are Equal if all three equivalence parts are identical for both shapes
// Two shapes are Same if all equivalence parts are identical except orientation
// Hence the difference between two ShapeHashes is what comparison method we need
#define ShapesOrientationIsUsed 0

#if ShapesOrientationIsUsed
// Use Oriented- ShapeHash and ShapeEqual if you want to consider orientation of shape in hash computing
typedef ModelData_OrientedShapeHash  HasherType;
typedef ModelData_OrientedShapeEqual EqualerType;
#else
// Use Unoriented- ShapeHash and ShapeEqual if shape orientation is negligible
typedef ModelData_UnorientedShapeHash  HasherType;
typedef ModelData_UnorientedShapeEqual EqualerType;
#endif

// Set to collect unique shapes from model
typedef unordered_set<ModelData_Shape, HasherType, EqualerType> ShapeSetType;

// Visits directly each part and calls B-Rep representation exploring if a part has one
class PartBRepVisitor : public ModelData_Model::VoidElementVisitor
{
public:

    PartBRepVisitor() : myNestingLevel (0) {}

    void PrintUniqueShapesCount()
    {
        cout << endl << "Total unique shapes count: " << myShapeSet.size() << endl;
    }

protected:

    void operator() (const ModelData_Part& thePart) override
    {
        const ModelData_BRepRepresentation& aBRep = thePart.BRepRepresentation();
        if (aBRep) {
            ExploreBRep (aBRep);
        }
    }

private:

    void ExploreBRep (const ModelData_BRepRepresentation& theBRep)
    {
        // Get() method retrieves bodies listed in B-Rep representation by calling data providers flushing
        // Flushing isn't an elementary process so it can take a significant time (seconds, minutes depending on a model structure)
        const ModelData_BodyList& aBodyList = theBRep.Get();

        // Iterate over bodies
        for (ModelData_BodyList::SizeType i = 0; i < aBodyList.Size(); ++i) {
            const ModelData_Body& aBody = aBodyList[i];
            cout << "Body " << i << " : -type " << PrintBodyType (aBody) << endl;

            ExploreShape (aBody);
        }
    }

    // Recursive iterating over the Shape untill reaching vertices
    void ExploreShape (const ModelData_Shape& theShape)
    {
        myShapeSet.insert (theShape);
        ++myNestingLevel;
        ModelData_Shape::Iterator aShapeIt (theShape);
        while (aShapeIt.HasNext()) {
            const ModelData_Shape& aShape = aShapeIt.Next();
            PrintShapeInfo (aShape);
            ExploreShape (aShape);
        }
        --myNestingLevel;
    }

    // Returns body type name
    const char* PrintBodyType (const ModelData_Body& theBody)
    {
        switch (theBody.BodyType()) {
        case ModelData_BT_Solid:     return "Solid";
        case ModelData_BT_Sheet:     return "Sheet";
        case ModelData_BT_Wireframe: return "Wireframe";
        case ModelData_BT_Acorn:     return "Acorn";
        default:
            break;
        }
        return "Undefined";
    }

    // Returns shape type name and prints shape info in some cases
    void PrintShapeInfo (const ModelData_Shape& theShape)
    {
        PrintTabulation();

        switch (theShape.Type()) {
        case ModelData_ST_Body:   cout << "Body";   break;
        case ModelData_ST_Solid:  cout << "Solid";  break;
        case ModelData_ST_Shell:  cout << "Shell";  break;
        case ModelData_ST_Wire:   cout << "Wire";   PrintWireInfo   (ModelData_Wire::Cast   (theShape)); break;
        case ModelData_ST_Face:   cout << "Face";   PrintFaceInfo   (ModelData_Face::Cast   (theShape)); break;
        case ModelData_ST_Edge:   cout << "Edge";   PrintEdgeInfo   (ModelData_Edge::Cast   (theShape)); break;
        case ModelData_ST_Vertex: cout << "Vertex"; PrintVertexInfo (ModelData_Vertex::Cast (theShape)); break;
        default:
            cout << "Undefined"; break;
        }

        cout << endl;
    }

    void PrintWireInfo (const ModelData_Wire& theWire)
    {
        ++myNestingLevel;
        cout << ". Orientation: " << PrintOrientation (theWire.Orientation());
        --myNestingLevel;
    }

    void PrintFaceInfo (const ModelData_Face& theFace)
    {
        ++myNestingLevel;
        cout << ". Orientation: " << PrintOrientation (theFace.Orientation()) << endl;

        ModelData_Surface aSurface = theFace.Surface();
        PrintTabulation();
        cout << "Surface: " << PrintSurfaceType (aSurface);

        --myNestingLevel;
    }

    const char* PrintSurfaceType (const ModelData_Surface& theSurface)
    {
        switch (theSurface.Type()) {
        case ModelData_ST_Plane:           return "Plane";
        case ModelData_ST_Cylinder:        return "Cylinder";
        case ModelData_ST_Cone:            return "Cone";
        case ModelData_ST_Sphere:          return "Sphere";
        case ModelData_ST_Torus:           return "Torus";
        case ModelData_ST_LinearExtrusion: return "LinearExtrusion";
        case ModelData_ST_Revolution:      return "Revolution";
        case ModelData_ST_Bezier:          return "Bezier";
        case ModelData_ST_BSpline:         return "BSpline";
        case ModelData_ST_Offset:          return "Offset";
        case ModelData_ST_Trimmed:         return "Trimmed";;
        default:
            break;
        }

        return "Undefined";
    }

    void PrintEdgeInfo (const ModelData_Edge& theEdge)
    {
        ++myNestingLevel;
        if (theEdge.IsDegenerated()) {
            cout << "(Degenerated)";
        }
        cout << ". Orientation: " << PrintOrientation (theEdge.Orientation()) <<
                ". Tolerance: "   << theEdge.Tolerance();

        if (!theEdge.IsDegenerated()) {
            array<double, 2> aParameters;
            enum {First, Last};
            ModelData_Curve aCurve = theEdge.Curve (aParameters[First], aParameters[Last]);
            cout << endl;
            PrintTabulation();
            cout << "Curve: " << PrintCurvetype (aCurve);
        }
        --myNestingLevel;
    }

    const char* PrintCurvetype (const ModelData_Curve& theCurve)
    {
        switch (theCurve.Type()) {
        case ModelData_CT_Line:      return "Line";
        case ModelData_CT_Circle:    return "Circle";
        case ModelData_CT_Ellipse:   return "Ellipse";
        case ModelData_CT_Hyperbola: return "Hyperbola";
        case ModelData_CT_Parabola:  return "Parabola";
        case ModelData_CT_Bezier:    return "Bezier";
        case ModelData_CT_BSpline:   return "BSpline";
        case ModelData_CT_Offset:    return "Offset";
        case ModelData_CT_Trimmed:   return "Trimmed";
        default:
            break;
        }

        return "Undefined";
    }

    void PrintVertexInfo (const ModelData_Vertex& theVertex)
    {
        cout << ". Orientation: " << PrintOrientation (theVertex.Orientation()) <<
                ". Tolerance "    << theVertex.Tolerance();
    }

    const char* PrintOrientation (ModelData_ShapeOrientation theOrientation)
    {
        switch (theOrientation) {
        case ModelData_SO_Forward:  return "Forward";
        case ModelData_SO_Reversed: return "Reversed";
        default:
            break;
        }

        return "Undefined";
    }

    void PrintTabulation()
    {
        for (size_t i = 0; i < myNestingLevel; ++i) {
            cout << "- ";
        }
    }

    size_t myNestingLevel;
    ShapeSetType myShapeSet;
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

    ModelData_Model aModel;

    if (!aModel.Open (aSource)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }

    // Explore B-Rep representation of model parts
    PartBRepVisitor aVisitor;
    aModel.Accept (aVisitor);

    aVisitor.PrintUniqueShapesCount();

    return 0;
}

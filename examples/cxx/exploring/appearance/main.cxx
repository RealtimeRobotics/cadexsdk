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
#include <cadex/ModelData_Appearance.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_PolyRepresentation.hxx>
#include <cadex/ModelData_PolyShape.hxx>
#include <cadex/ModelData_PolyShapeList.hxx>
#include <cadex/ModelData_PolyVertexSet.hxx>
#include <cadex/ModelData_SceneGraphElement.hxx>
#include <iostream>
#include <unordered_set>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

// AppearanceHash value depends on color, material and other properties of appearance
typedef unordered_set<ModelData_Appearance, ModelData_AppearanceHash> AppSetType;

class SubshapeAppearancesCollector : public ModelData_BRepRepresentation::SubshapeVisitor
{
public:

    SubshapeAppearancesCollector (const ModelData_BRepRepresentation& theBRep, AppSetType& theAppSet) :
        myBRep (theBRep), myAppSet (theAppSet) {}

protected:

    void operator() (const ModelData_Shape& theShape) override
    {
        ExploreShapeAppearances (theShape);
    }

private:

    // Iterates through Shapes to collect it's appearances
    void ExploreShapeAppearances (const ModelData_Shape& theShape)
    {
        ModelData_Appearance anApp = myBRep.Appearance (theShape);
        if (anApp) {
            myAppSet.insert (anApp);
        }
    }

    ModelData_BRepRepresentation myBRep;
    AppSetType& myAppSet;
};

class RepVisitor : public ModelData_Part::RepresentationVisitor
{
public:

    RepVisitor (AppSetType& theAppSet) : myAppSet (theAppSet) {}

protected:

    void operator() (const ModelData_BRepRepresentation& theBRep) override
    {
        SubshapeAppearancesCollector aCollector (theBRep, myAppSet);
        theBRep.Accept (aCollector);
    }

    void operator() (const ModelData_PolyRepresentation& thePolyRep) override
    {
        ExplorePVSAppearances (thePolyRep);
    }

private:
    // Iterates through PolyShapes to collect it's appearances
    void ExplorePVSAppearances (const ModelData_PolyRepresentation& thePolyRep)
    {
        const ModelData_PolyShapeList& aList = thePolyRep.Get();
        for (ModelData_PolyShapeList::SizeType i = 0; i < aList.Size(); ++i) {
            const ModelData_PolyVertexSet& aPVS = aList[i];
            ModelData_Appearance anApp = aPVS.Appearance();
            if (anApp) {
                myAppSet.insert (anApp);
            }
        }
    }

    AppSetType& myAppSet;
};

class SGEAppearancesCollector : public ModelData_Model::CombinedElementVisitor
{
public:

    SGEAppearancesCollector (AppSetType& theAppset) : myAppSet (theAppset) {}

protected:

    void operator() (const ModelData_Part& thePart) override
    {
        ExploreSGEAppearance (thePart);

        RepVisitor aVisitor (myAppSet);
        thePart.Accept (aVisitor);
    }

    bool VisitEnter (const ModelData_SceneGraphElement& theElement) override
    {
        ExploreSGEAppearance (theElement);
        return true;
    }

private:
    // Collects SceneGraphElement appearance
    void ExploreSGEAppearance (const ModelData_SceneGraphElement& theSGE)
    {
        ModelData_Appearance anApp = theSGE.Appearance();
        if (anApp) {
            myAppSet.insert (anApp);
        }
    }

    AppSetType& myAppSet;
};

class AppearancesCollector
{
public:

    AppearancesCollector (ModelData_Model theModel) : myModel (theModel)
    {
        SGEAppearancesCollector aCollector (myAppSet);
        myModel.Accept (aCollector);
    }

    void PrintAppearancesCount()
    {
        cout << "Total Model Unique Appearances Count: " << myAppSet.size() << endl;
    }

private:

    AppSetType myAppSet;
    ModelData_Model myModel;
};

int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

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

    // Explore model's appearances
    AppearancesCollector aCollector (aModel);

    // Print the number of unique appearances in our model
    aCollector.PrintAppearancesCount();

    return 0;
}

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
#include <cadex/ModelData_Assembly.hxx>
#include <cadex/ModelData_Body.hxx>
#include <cadex/ModelData_BodyList.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_PropertyTable.hxx>
#include <cadex/ModelData_Shape.hxx>
#include <iostream>
#include <vector>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

// Print only I32 and double properties. Should be extended to print other supported properties (I64, float, etc)
class PropertyVisitor : public ModelData_PropertyTable::VoidVisitor
{
public:

    PropertyVisitor()
    {
        cout << "\nProperty table: " << endl;
    }

    void operator() (PropertyNameConstReference theName, I32 theValue) override
    {
        OutputData (theName, theValue);
    }

    void operator() (PropertyNameConstReference theName, double theValue) override
    {
        OutputData (theName, theValue);
    }

    void operator() (PropertyNameConstReference theName, const Base_UTF16String& theValue) override
    {
        OutputData (theName, theValue);
    }

protected:

    template <typename T>
    void OutputData (PropertyNameConstReference& theName, T theValue)
    {
        cout << theName << ": " << theValue << endl;
    }
};

static void ExplorePropertyTable (const ModelData_PropertyTable& thePT)
{
    // Traverse property table
    PropertyVisitor aPropVisitor;
    thePT.Accept (aPropVisitor);
}

class SubshapePropertiesVisitor : public ModelData_BRepRepresentation::SubshapeVisitor
{
public:

    SubshapePropertiesVisitor (const ModelData_BRepRepresentation& theBRep) : myBRep (theBRep) {}

    vector<ModelData_PropertyTable> PropertyTables()
    {
        return myPTVector;
    }

protected:

    void operator() (const ModelData_Shape& theShape) override
    {
        ModelData_PropertyTable aPT = myBRep.PropertyTable (theShape);
        myPTVector.push_back (aPT);
    }

private:

    ModelData_BRepRepresentation myBRep;
    vector<ModelData_PropertyTable> myPTVector;
};

class PropertiesVisitor : public ModelData_Model::CombinedElementVisitor
{
protected:

    void operator() (const ModelData_Part& thePart) override
    {
        ModelData_PropertyTable aPT = thePart.Properties();
        ExplorePropertyTable (aPT);

        const ModelData_BRepRepresentation& aBRep = thePart.BRepRepresentation();
        if (aBRep) {
            SubshapePropertiesVisitor aVisitor (aBRep);
            aBRep.Accept (aVisitor);

            // Extract all PropertyTables from SubShapes in B-Rep and explore it
            vector<ModelData_PropertyTable> aPTVector = aVisitor.PropertyTables();
            for (size_t i = 0; i < aPTVector.size(); ++i) {
                ExplorePropertyTable (aPTVector[i]);
            }
        }
    }

    bool VisitEnter (const ModelData_SceneGraphElement& theElement) override
    {
        ModelData_PropertyTable aPT = theElement.Properties();
        ExplorePropertyTable (aPT);

        return true;
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

    ModelData_Model aModel;

    if (!aModel.Open (aSource)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }

    PropertiesVisitor aVisitor;
    aModel.Accept (aVisitor);

    return 0;
}

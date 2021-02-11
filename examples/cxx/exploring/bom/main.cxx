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
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_SceneGraphElement.hxx>
#include <iostream>
#include <unordered_map>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

typedef unordered_map<ModelData_SceneGraphElement, size_t, ModelData_BaseObjectHash> SGEMapType;

const char* PrintSGEType (const ModelData_SceneGraphElement& theSGE)
{
    if (theSGE.IsOfType<ModelData_Part>()) {
        return "Part";
    } else if (theSGE.IsOfType<ModelData_Assembly>()) {
        return "Assembly";
    } else if (theSGE.IsOfType<ModelData_Instance>()) {
        return "Instance";
    }
    return "Undefined";
}

class SceneGraphVisitor : public ModelData_Model::ElementVisitor
{
public:
    SceneGraphVisitor () : myNestingLevel (0)
    {
    }

    void PrintCounts()
    {
        cout << endl << "Total:" << endl << "name | type | count" << endl;
        for (auto it = mySGEMap.begin(); it != mySGEMap.end(); ++it) {
            cout << (*it).first.Name()         << " | " <<
                    PrintSGEType ((*it).first) << " | " <<
                    (*it).second << endl;
        }
    }

protected:

    void operator() (const ModelData_Part& thePart) override
    {
        PrintName ("Part", thePart.Name());
        UpdateTable (thePart);
    }

    bool VisitEnter (const ModelData_Assembly& theAssembly) override
    {
        PrintName ("Assembly", theAssembly.Name());
        UpdateTable (theAssembly);
        ++myNestingLevel;
        return true;
    }

    void VisitLeave (const ModelData_Assembly&) override
    {
        --myNestingLevel;
    }

    bool VisitEnter (const ModelData_Instance& theInstance) override
    {
        PrintName ("Instance", theInstance.Name());
        ++myNestingLevel;
        return true;
    }

    void VisitLeave (const ModelData_Instance&) override
    {
        --myNestingLevel;
    }

private:

    void PrintName (const char* theSGElement, const Base_UTF16String& theName)
    {
        for (size_t i = 0; i < myNestingLevel; ++i) {
            cout << "--- ";
        }

        if (!theName.IsEmpty()) {
            cout << theSGElement << ": " << theName << endl;
        } else {
            cout << theSGElement << ": <noname>" << endl;
        }
    }

    void UpdateTable (const ModelData_SceneGraphElement& theSGEElement)
    {
        if (!mySGEMap.insert (make_pair (theSGEElement, 1)).second) {
            ++mySGEMap[theSGEElement];
        }
    }

    size_t myNestingLevel;
    SGEMapType mySGEMap;
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

    // Load the model
    ModelData_Model aModel;
    if (!aModel.Open (aSource)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }

    // Create a Counter
    SceneGraphVisitor aCounter;
    aModel.Accept (aCounter);
    aCounter.PrintCounts();

    return 0;
}

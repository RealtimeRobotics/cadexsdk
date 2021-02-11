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

#ifndef __CADEX_PREVIEW_PMI
#define __CADEX_PREVIEW_PMI 1
#endif __CADEX_PREVIEW_PMI

#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelAlgo_BRepMesher.hxx>
#include <cadex/ModelAlgo_BRepMesherParameters.hxx>
#include <cadex/ModelData_Appearance.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_Layer.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_PMITable.hxx>
#include <cadex/ModelData_PropertyTable.hxx>
#include <cadex/SLD_Reader.hxx>
#include <cadex/VRML_Writer.hxx>

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

class MeshReplacementVisitor : public ModelData_Model::VoidElementVisitor
{
public:
    bool VisitEnter (const ModelData_Instance& theInstance) override
    {
        myInstances.push(theInstance);
        return true;
    }

    void VisitLeave (const ModelData_Instance& theInstance) override
    {
        myInstances.pop();
    }

    void operator() (const ModelData_Part& thePart) override
    {
        if (thePart.BRepRepresentation().IsNull()) {
            return;
        }

        if (myReplacedParts.find (thePart) != myReplacedParts.end() && myInstances.size() > 0) {
            myInstances.top().SetReference (myReplacedParts[thePart]);
            return;
        }

        ModelData_Part aNewPart (thePart.BRepRepresentation(), thePart.Name());
        aNewPart.SetAppearance (thePart.Appearance());
        aNewPart.AddProperties (thePart.Properties());
        aNewPart.AddPMI (thePart.PMI());
        for (ModelData_SceneGraphElement::LayerIterator anIt (thePart); anIt.HasNext();) {
            aNewPart.AddToLayer (anIt.Next());
        }

        ModelAlgo_BRepMesherParameters aMesherParams (ModelAlgo_BRepMesherParameters::Granularity::Fine);
        ModelAlgo_BRepMesher aMesher (aMesherParams);
        aMesher.Compute (aNewPart);

        if (myInstances.empty()) {
            myRootReplacements[thePart] = aNewPart;
        } else {
            myReplacedParts[thePart] = aNewPart;
            myInstances.top().SetReference (aNewPart);
        }
    }

    const unordered_map <ModelData_Part, ModelData_Part, ModelData_BaseObjectHash>& RootReplacements() const
    {
        return myRootReplacements; 
    }
private:
    stack <ModelData_Instance> myInstances;
    unordered_map <ModelData_Part, ModelData_Part, ModelData_BaseObjectHash> myRootReplacements;
    unordered_map <ModelData_Part, ModelData_Part, ModelData_BaseObjectHash> myReplacedParts;
};

int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>, where:" << endl;
        cerr << "    <input_file>  is a name of the SLD file to be read" << endl;
        cerr << "    <output_file>  is a name of the VRML file to be saved" << endl;
        return 1;
    }

    const char* aSource = argv[1];
    const char* aDest = argv[2];


    SLD_Reader aReader;

    ModelData_Model aModel;

    cout << "Conversion started..." << endl;

    // Reading the file
    if (!aReader.ReadFile (aSource)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }

    // Making a model data
    if (!aReader.Transfer (aModel)) {
        cerr << "Failed to transfer model data to specified format" << endl;
        return 1;
    }


    MeshReplacementVisitor aVisitor;
    aModel.Accept (aVisitor);
    vector <ModelData_SceneGraphElement> aNewRoots;
    for (ModelData_Model::ElementIterator anIt (aModel); anIt.HasNext();) {
        ModelData_SceneGraphElement aRoot = anIt.Next();
        if (aRoot.TypeId() == ModelData_Part::GetTypeId()) {
            const ModelData_Part* aRootPart = static_cast <ModelData_Part*> (&aRoot);
            auto aNewRootIt = aVisitor.RootReplacements().find (*aRootPart);
            assert (aNewRootIt != aVisitor.RootReplacements().end());
            aNewRoots.push_back (aNewRootIt->second);
        } else {
            aNewRoots.push_back (aRoot);
        }
    }
    aModel.Clear();

    for (auto& aRoot : aNewRoots) {
        aModel.AddRoot (aRoot);
    }

    VRML_Writer aWriter;

    // Converting from inner format
    if (!aWriter.Transfer (aModel)) {
        cerr << "Failed to transfer the file from inner format." << endl;
        return 1;
    }

    if (!aWriter.WriteFile (Base_UTF16String (aDest))) {
        cerr << "Failed to write the file..." << aDest << endl;
        return 1;
    }

    return 0;
}

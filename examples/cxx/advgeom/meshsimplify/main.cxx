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
#include <cadex/ModelData_IndexedTriangleSet.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_PolyRepresentation.hxx>
#include <cadex/ModelData_PolyShape.hxx>
#include <cadex/ModelData_PolyShapeList.hxx>
#include <cadex/ModelSimplifier_MeshSimplifier.hxx>
#include <cadex/ModelSimplifier_MeshSimplifierParameters.hxx>
#include <cadex/VRML_Reader.hxx>
#include <iostream>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

class TriangleCounter : public ModelData_Model::VoidElementVisitor
{
public:
    class PolyRepExplorer : public ModelData_Part::VoidRepresentationVisitor
    {
    public:
        void operator() (const ModelData_PolyRepresentation& theRep) override
        {
            const auto& aShapeList = theRep.Get();
            for (size_t i = 0; i < aShapeList.Size(); i++) {
                ModelData_PolyShape aShape = aShapeList.Element (i);
                if (aShape.IsOfType <ModelData_IndexedTriangleSet>()) {
                    const auto& anITS = static_cast <const ModelData_IndexedTriangleSet&> (aShape);
                    myNumberOfTriangles += anITS.NumberOfFaces();
                }
            }
        }

        size_t myNumberOfTriangles = 0;
    };

    void operator() (const ModelData_Part& thePart) override
    {
        PolyRepExplorer aRepExplorer;
        thePart.Accept (aRepExplorer);
        myNumberOfTriangles += aRepExplorer.myNumberOfTriangles;
    }

    size_t NumberOfTriangles() const
    { return myNumberOfTriangles; }

private:
    size_t myNumberOfTriangles = 0;
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
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>, where:"   << endl;
        cerr << "    <input_file>  is a name of the VRML file to be read"       << endl;
        cerr << "    <output_file>  is a name of the XML file to be saved"      << endl;
        return 1;
    }

    const char* aSource = argv[1];
    const char* aDest   = argv[2];

    VRML_Reader aReader;

    ModelData_Model aModel;

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

    // Basic info about model
    TriangleCounter aBeforeCounter;
    aModel.Accept (aBeforeCounter);
    cout << "Model name: "            << aModel.Name()                      << endl;
    cout << "# of triangles before: " << aBeforeCounter.NumberOfTriangles() << endl;

    // Running the simplifier
    ModelSimplifier_MeshSimplifierParameters aParams;
    aParams.SetDegreeOfSimplification (ModelSimplifier_MeshSimplifierParameters::High);

    ModelSimplifier_MeshSimplifier aSimplifier;
    aSimplifier.SetParameters (aParams);
    ModelData_Model aNewModel = aSimplifier.Perform (aModel);

    // How many triangles does simplified model contain?
    TriangleCounter anAfterCounter;
    aNewModel.Accept (anAfterCounter);
    cout << "# of triangles after: " << anAfterCounter.NumberOfTriangles() << endl;

    // Saving the simplified model
    if (!aNewModel.Save (aDest)) {
        cerr << "Failed to write the file " << aDest << endl;
        return 1;
    };

    return 0;
}

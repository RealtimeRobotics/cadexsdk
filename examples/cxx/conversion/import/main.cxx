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
#include <cadex/ModelData_Model.hxx>
#include <cadex/STEP_Reader.hxx>
#include <cadex/STEP_ReaderParameters.hxx>
#include <iostream>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>, where:"     << endl;
        cerr << "    <input_file>  is a name of the STEP file to be read"         << endl;
        cerr << "    <output_file> is a name of the XML file to Save() the model" << endl;
        return 1;
    }

    const char* aSource = argv[1];
    const char* aDest   = argv[2];

    STEP_Reader aReader;
    STEP_ReaderParameters& aReaderParams = aReader.Parameters();

    // Let's set new parameters
    aReaderParams.PreferredBRepRepresentationType() = STEP_ReaderParameters::AdvancedBRep;

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

    // Now we can get some model data
    cout << "Model name: "      << aModel.Name()          << endl;
    cout << "Number of roots: " << aModel.NumberOfRoots() << endl;
    
    // Saving the model
    if (!aModel.Save (aDest)) {
        cerr << "Failed to write the file " << aDest << endl;
        return 1;
    };

    return 0;
}

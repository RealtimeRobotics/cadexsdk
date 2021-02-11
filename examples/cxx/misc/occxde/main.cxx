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


#include <Standard_Version.hxx>
#include <cadex/ModelXDE_Converter.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/LicenseManager_Activate.h>
#include <cadex/JT_Reader.hxx>
#include <cadex/STEP_Writer.hxx>

#include <TDocStd_Document.hxx>

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
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>, where:" << endl;
        cerr << "    <input_file> is a name of the JT file to be read"        << endl;
        cerr << "    <output_file> is a name of the STEP file to be written"  << endl;
        return 1;
    }
    const char* aSource = argv[1];
    const char* aDest   = argv[2];

    ModelData_Model anInModel;
    ModelData_Model anOutModel;
    Handle (TDocStd_Document) aDoc = new TDocStd_Document ("dd");

    // Import
    JT_Reader aReader;
    if (!(aReader.ReadFile (aSource) && aReader.Transfer (anInModel))) {
        cout << "Couldn't read the file!" << endl;
        return 1;
    }

    if (!ModelXDE_Converter::Convert (anInModel, aDoc)) {
        cerr << "Unable to convert from model to XDE!" << endl;
        return 1;
    }

    // Export
    if (!ModelXDE_Converter::Convert (aDoc, anOutModel)) {
        cerr << "Unable to convert from XDE to model!" << endl;
        return 1;
    }

    STEP_Writer aWriter;
    if (!(aWriter.Transfer (anOutModel) && aWriter.WriteFile (aDest))) {
        cout << "Couldn't write the file!" << endl;
        return 1;
    }

    return 0;
}

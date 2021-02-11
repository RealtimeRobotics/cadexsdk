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


#include <cadex/ACIS_Reader.hxx>
#include <cadex/Base_ProgressScope.hxx>
#include <cadex/Base_ProgressStatus.hxx>
#include <cadex/Base_String.hxx>
#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelAlgo_BRepMesher.hxx>
#include <cadex/ModelData_Model.hxx>
#include <iostream>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

class ProgressBarObserver : public Base_ProgressStatus::Observer
{
public:

    void ChangedValue (const Base_ProgressStatus& theInfo) override
    {
        cout << theInfo.Value() << endl;
    }

    void Completed (const Base_ProgressStatus& theInfo) override
    {
        cout << theInfo.Value() << ": complete!" << endl;
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
        cerr << "    <input_file> is a name of the .sat file to be read" << endl;
        return 1;
    }
    const char* aSource = argv[1];

    // Create observer
    // An observer must have a greater life span than aStatus
    // so create it in explicit external scope for aStatus
    ProgressBarObserver anObserver;
    anObserver.SetAllNotifyingThreads();

    ModelData_Model aModel;

    Base_ProgressStatus aStatus;
    aStatus.Register (anObserver);                              // Register an Observer to progress status

    bool anIsOK = false;
    Base_ProgressScope aTopScope (aStatus);                     // The top scope occupies the whole progress status range
    {
        Base_ProgressScope aReaderScope (aTopScope, 40);        // 40% of TopScope for file importing

        ACIS_Reader aReader;
        aReader.ProgressStatus() = aStatus;                     // Connect progress status object

        {
            Base_ProgressScope aSubScope (aReaderScope, 25);    // 25% of ReaderScope (10% of TopScope)
            anIsOK = aReader.ReadFile (aSource);
        }
        if (anIsOK) {
            Base_ProgressScope aSubScope (aReaderScope, 75);    // 75% of ReaderScope (30% of TopScope)
            anIsOK = aReader.Transfer (aModel);
        }
    }
    if (anIsOK) {
        Base_ProgressScope aMesherScope (aTopScope, -1);        // The remaining 60% of TopScope for meshing
        ModelAlgo_BRepMesher aMesher;
        aMesher.ProgressStatus() = aStatus;                     // Connect progress status object
        aMesher.Compute (aModel);
    }

    return anIsOK ? 0 : 1;
}

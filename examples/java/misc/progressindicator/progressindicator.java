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

import cadex.*;

public class progressindicator {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExACIS");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(1);
        }
    }

    public static void main(String[] args) {
        String aKey = LicenseKey.Value();

        // Activate the license (aKey must be defined in LicenseKey.java)
        if (!LicenseManager.Activate(aKey)) {
            System.out.println("Failed to activate CAD Exchanger license.");
            System.exit(1);
        }

        if (args.length != 1) {
            System.out.println("Usage: " + " <input_file>, where:");
            System.out.println("    <input_file>  is a name of the ACIS file to be read");
            System.exit(1);
        }

        String aSource = args[0];

        ModelData_Model aModel = new ModelData_Model();

        ProgressBarObserver anObserver = new ProgressBarObserver();
        anObserver.SetAllNotifyingThreads();

        boolean anIsOK = false;
        try (Base_ProgressStatus aStatus = new Base_ProgressStatus()) {
            aStatus.Register(anObserver); // Register an Observer to progress status

            try (Base_ProgressScope aTopScope = new Base_ProgressScope(aStatus)) // The top scope occupies the whole progress status range
            {
                try (Base_ProgressScope aReaderScope = new Base_ProgressScope(aTopScope, 40)) // 40% of TopScope for file importing
                {
                    ACIS_Reader aReader = new ACIS_Reader();
                    aReader.SetProgressStatus(aStatus); // Connect progress status object

                    if (!aStatus.WasCanceled()) {
                        try (Base_ProgressScope aSubScope =
                                new Base_ProgressScope(aReaderScope, 25)) // 25% of ReaderScope (10% of TopScope)
                        {
                            anIsOK = aReader.ReadFile(new Base_UTF16String(aSource));
                        }
                    }
                    if (anIsOK && !aStatus.WasCanceled()) {
                        try (Base_ProgressScope aSubScope =
                                new Base_ProgressScope(aReaderScope, 75)) // 75% of ReaderScope (30% of TopScope)
                        {
                            anIsOK = aReader.Transfer(aModel);
                        }
                    }
                }
                if (anIsOK && !aStatus.WasCanceled()) {
                    try (Base_ProgressScope aMesherScope =
                            new Base_ProgressScope(aTopScope, -1)) // The remaining 60% of TopScope for meshing
                    {
                        ModelAlgo_BRepMesher aMesher = new ModelAlgo_BRepMesher();
                        aMesher.SetProgressStatus(aStatus); // Connect progress status object
                        aMesher.Compute(aModel);
                    }
                }
            }
        }
        // Observer will be automatically unregistered from progress status on destruction (end of the "try" scope).

        System.exit(anIsOK ? 0 : 1);
    }
}

class ProgressBarObserver extends Base_ProgressStatus.Observer {
    @Override
    public void ChangedValue(Base_ProgressStatus theInfo) {
        System.out.println(theInfo.Value());
    }

    @Override
    public void Completed(Base_ProgressStatus theInfo) {
        System.out.println(theInfo.Value() + ": complete!");
    }
}

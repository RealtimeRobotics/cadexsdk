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


using cadex;
using System;
using System.Runtime.InteropServices;

namespace progressindicator
{
    class Program
    {
        // For more information see https://stackoverflow.com/questions/8836093/how-can-i-specify-a-dllimport-path-at-runtime
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool SetDllDirectory(string lpPathName);

        static int Main(string[] args)
        {
            // Add runtime path to CAD Exchanger libraries (e.g. compiled with Visual Studio 2015)
            SetDllDirectory("../../../../../../win64/vc14.1/bin");

            string aKey = LicenseKey.Value();

            // Activate the license (aKey must be defined in cadex_license.cs)
            if (!LicenseManager.Activate(aKey))
            {
                Console.WriteLine("Failed to activate CAD Exchanger license.");
                return 1;
            }

            if (args.Length != 1)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the SAT file to be read");
                return 1;
            }

            string aSource = args[0];

            ModelData_Model aModel = new ModelData_Model();

            ProgressBarObserver anObserver = new ProgressBarObserver();
            anObserver.SetAllNotifyingThreads();

            bool anIsOK = false;
            using (var aStatus = new Base_ProgressStatus())
            {
                aStatus.Register(anObserver);                                                  // Register an Observer to progress status

                using (var aTopScope = new Base_ProgressScope(aStatus))                        // The top scope occupies the whole progress status range
                {
                    using (var aReaderScope = new Base_ProgressScope(aTopScope, 40))           // 40% of TopScope for file importing
                    {
                        ACIS_Reader aReader = new ACIS_Reader();
                        aReader.SetProgressStatus(aStatus);                                     // Connect progress status object

                        if (!aStatus.WasCanceled())
                        {
                            using (var aSubScope = new Base_ProgressScope(aReaderScope, 25))   // 25% of ReaderScope (10% of TopScope)
                            {
                                anIsOK = aReader.ReadFile(new Base_UTF16String(aSource));
                            }
                        }
                        if (anIsOK && !aStatus.WasCanceled())
                        {
                            using (var aSubScope = new Base_ProgressScope(aReaderScope, 75))   // 75% of ReaderScope (30% of TopScope)
                            {
                                anIsOK = aReader.Transfer(aModel);
                            }
                        }
                    }
                    if (anIsOK && !aStatus.WasCanceled())
                    {
                        using (var aMesherScope = new Base_ProgressScope(aTopScope, -1))       // The remaining 60% of TopScope for meshing
                        {
                            ModelAlgo_BRepMesher aMesher = new ModelAlgo_BRepMesher();
                            aMesher.SetProgressStatus(aStatus);                                // Connect progress status object
                            aMesher.Compute(aModel);
                        }
                    }
                }
            }
            // Observer will be automatically unregistered from progress status on destruction (end of the "using" scope).

            return anIsOK ? 0 : 1;
        }
    }

    class ProgressBarObserver : Base_ProgressStatus.Observer
    {
        public override void ChangedValue(Base_ProgressStatus theInfo)
        {
            Console.WriteLine(theInfo.Value());
        }

        public override void Completed(Base_ProgressStatus theInfo)
        {
            Console.WriteLine(theInfo.Value() + ": complete!");
        }
    }
}

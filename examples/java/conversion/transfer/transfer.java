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

public class transfer {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExJT");
            System.loadLibrary("CadExSTEP");
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

        if (args.length != 2) {
            System.out.println("Usage: " + " <input_file> <output_file>, where:");
            System.out.println("    <input_file>  is a name of the STEP file to be read  ");
            System.out.println("    <output_file> is a name of the JT file to be written");
            System.exit(1);
        }

        String aSource = args[0];
        String aDest = args[1];

        STEP_Reader aReader = new STEP_Reader();

        // Read the file
        if (!aReader.ReadFile(new Base_UTF16String(aSource))) {
            System.out.println("Failed to read the file " + aSource);
            System.exit(1);
        }

        ModelData_Model aModel = new ModelData_Model();

        // Make model data
        if (!aReader.Transfer(aModel)) {
            System.out.println("Failed to transfer model data to specified format " + aSource);
            System.exit(1);
        }

        JT_Writer aWriter = new JT_Writer();

        // Transfer model data to JT format
        if (!aWriter.Transfer(aModel)) {
            System.out.println("Failed to transfer model data to specified format " + aSource);
            System.exit(1);
        }

        // Write the file
        if (!aWriter.WriteFile(new Base_UTF16String(aDest))) {
            System.out.println("Failed to write the file " + aSource);
            System.exit(1);
        }
    }
}

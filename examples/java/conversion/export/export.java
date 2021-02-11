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

public class export {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExOBJ");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(1);
        }
    }

    public static void main(String[] args) {
        String aKey = LicenseKey.Value();

        // Activate the license (aKey must be defined in LicenseKey.java)
        if (!LicenseManager.Activate(aKey)) {
            System.err.println("Failed to activate CAD Exchanger license.");
            System.exit(1);
        }

        if (args.length != 2) {
            System.err.println("Usage: " + " <input_file> <output_file>, where:");
            System.err.println("    <input_file>  is a name of the XML file to to Open() model from");
            System.err.println("    <output_file> is a name of the OBJ file to be written          ");
            System.exit(1);
        }

        String aSource = args[0];
        String aDest = args[1];

        ModelData_Model aModel = new ModelData_Model();

        // Read an XML file
        if (!aModel.Open(new Base_UTF16String(aSource))) {
            System.err.println("Failed to read the file " + aSource);
            System.exit(1);
        }

        OBJ_Writer aWriter = new OBJ_Writer();
        OBJ_WriterParameters aWriterParams = aWriter.Parameters();

        // Set some writer parameters
        aWriterParams.SetLengthUnit(Base_LengthUnit.Base_LU_Centimeters);
        aWriterParams.SetToGenerateMtlFile(true);

        // Transfer model data to OBJ format
        if (!aWriter.Transfer(aModel)) {
            System.err.println("Failed to transfer model data to specified format");
            System.exit(1);
        }

        // Write model data to a file
        if (!aWriter.WriteFile(new Base_UTF16String(aDest))) {
            System.err.println("Failed to write the file " + aDest);
            System.exit(1);
        }
    }
}

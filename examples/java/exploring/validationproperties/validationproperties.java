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

public class validationproperties {
    static {
        try {
            System.loadLibrary("CadExCore");
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

        ModelData_Solid aCylinder = ModelAlgo_TopoPrimitives.CreateCylinder(5., 10.);

        // Compute Properties
        double aSurfaceArea = ModelAlgo_ValidationProperty.ComputeSurfaceArea(aCylinder);
        double aVolume = ModelAlgo_ValidationProperty.ComputeVolume(aCylinder);

        ModelData_Point aCentroid = new ModelData_Point();
        ModelAlgo_ValidationProperty.ComputeCentroid(aCylinder, aCentroid);

        ModelData_Box aBBox = new ModelData_Box();
        ModelAlgo_BoundingBox.Compute(new ModelData_BRepRepresentation(aCylinder), aBBox);

        // Output Properties
        System.out.println("Surface area:  " + aSurfaceArea);
        System.out.println("Volume:        " + aVolume);
        System.out.println("Centroid:     (" + aCentroid.X() + ", " + aCentroid.Y() + ", " + aCentroid.Z() + ")");
        System.out.println("Bounding Box: (" + aBBox.XRange() + ", " + aBBox.YRange() + ", " + aBBox.ZRange() + ")");
    }
}

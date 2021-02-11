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
#include <cadex/ModelAlgo_BoundingBox.hxx>
#include <cadex/ModelAlgo_TopoPrimitives.hxx>
#include <cadex/ModelAlgo_ValidationProperty.hxx>
#include <cadex/ModelAlgo_ValidationPropertyData.hxx>
#include <cadex/ModelData_Box.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Point.hxx>
#include <cadex/ModelData_Solid.hxx>
#include <iostream>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

int main()
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    ModelData_Solid aCylinder = ModelAlgo_TopoPrimitives::CreateCylinder (5., 10.);
    ModelAlgo_ValidationPropertyData aData;

    // Compute Properties
    ModelAlgo_ValidationProperty::ComputeValidationProperties (aCylinder, aData);

    double aSurfaceArea = aData.SurfaceArea();
    double aVolume = aData.Volume();
    ModelData_Point aCentroid = aData.Centroid();

    ModelData_Box aBBox;
    ModelAlgo_BoundingBox::Compute (ModelData_BRepRepresentation (aCylinder), aBBox);

    // Output Properties
    cout << "Surface area:  " << aSurfaceArea << endl;
    cout << "Volume:        " << aVolume      << endl;
    cout << "Centroid:     (" << aCentroid.X()  << ", " << aCentroid.Y()  << ", " << aCentroid.Z()  << ")" << endl;
    cout << "Bounding Box: (" << aBBox.XRange() << ", " << aBBox.YRange() << ", " << aBBox.ZRange() << ")" << endl;

    return 0;
}
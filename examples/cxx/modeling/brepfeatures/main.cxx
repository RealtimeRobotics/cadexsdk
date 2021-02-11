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


#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelAlgo_BRepFeatures.hxx>
#include <cadex/ModelData_Axis1Placement.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Direction.hxx>
#include <cadex/ModelData_Edge.hxx>
#include <cadex/ModelData_Face.hxx>
#include <cadex/ModelData_Line.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_Plane.hxx>
#include <cadex/ModelData_Shell.hxx>
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

    // Extrusion

    // Edge to Face
    ModelData_Line anExtrusionLine (ModelData_Point (-2., 0., -4.), ModelData_Direction::XDir());
    ModelData_Edge anExtrusionEdge (anExtrusionLine, 0., 4.);
    auto aPlane = ModelAlgo_BRepFeatures::CreateExtrusion (anExtrusionEdge, ModelData_Vector (0., 4., 0.));

    // Face to Solid
    auto aBlock = ModelAlgo_BRepFeatures::CreateExtrusion (aPlane, ModelData_Vector (0., 0., 8.));

    // Revolution

    // Edge to Face
    ModelData_Line aRevolutionLine (ModelData_Point (10., 0., 0.), ModelData_Direction::ZDir());
    ModelData_Edge aRevolutionEdge (aRevolutionLine, 1., 3.);
    auto aCircularPlane = ModelAlgo_BRepFeatures::CreateRevolution (aRevolutionEdge,
        ModelData_Axis1Placement (ModelData_Point (10., 0., 0.), ModelData_Direction::YDir()),
        M_PI * 2);

    // Face to Solid
    auto aTunnel = ModelAlgo_BRepFeatures::CreateRevolution (aCircularPlane, ModelData_Axis1Placement::OZ(), M_PI);

    // Create a model
    ModelData_Model aModel;

    ModelData_Part anExtrusionPart (ModelData_BRepRepresentation (aBlock), "Block");
    aModel.AddRoot (anExtrusionPart);

    ModelData_Part aRevolutionPart (ModelData_BRepRepresentation (aTunnel), "Tunnel");
    aModel.AddRoot (aRevolutionPart);

    // Save the result
    if (!aModel.Save ("Features.xml")) {
        cout << "Unable to save the model!" << endl;
        return 1;
    }

    return 0;
}
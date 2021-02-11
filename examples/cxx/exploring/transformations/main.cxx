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
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Transformation.hxx>
#include <cadex/ModelData_Vector.hxx>
#include <iostream>
#include <stack>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

class InstancesTransformationsVisitor : public ModelData_Model::VoidElementVisitor
{
public:

    InstancesTransformationsVisitor()
    {
        // We are going to multiply each matrix to produce transformations relative to the SceneGraph root
        ModelData_Transformation anIdentity (ModelData_Vector (0., 0., 0.));
        myTransformationMatrix.push (anIdentity);
    }

protected:

    bool VisitEnter (const ModelData_Instance& theInstance) override
    {
        ModelData_Transformation aTrsf;
        if (theInstance.HasTransformation()) {
            aTrsf = theInstance.Transformation();
        }
        ModelData_Transformation aCumulativeTrsf = myTransformationMatrix.top() * aTrsf;
        myTransformationMatrix.push (aCumulativeTrsf);

        PrintTransformation (theInstance.Name());

        return true;
    }

    void VisitLeave (const ModelData_Instance&) override
    {
        myTransformationMatrix.pop();
    }

private:

    void PrintTransformation (Base_UTF16String theName)
    {
        if (theName.IsEmpty()) {
            theName = "noName";
        }
        cout << "Instance " << theName << " has transformations: " << endl;

        // Current transformations are relative to the SceneGraph root
        double v00, v01, v02, v10, v11, v12, v20, v21, v22;
        myTransformationMatrix.top().RotationPart (v00, v01, v02, v10, v11, v12, v20, v21, v22);
        ModelData_Vector aTranslation = myTransformationMatrix.top().TranslationPart();
        cout << "| " << v00 << " " << v01 << " " << v02 << " " << aTranslation.X() << " |" << endl <<
                "| " << v10 << " " << v11 << " " << v12 << " " << aTranslation.Y() << " |" << endl <<
                "| " << v20 << " " << v21 << " " << v22 << " " << aTranslation.Z() << " |" << endl;
    }

    stack<ModelData_Transformation> myTransformationMatrix;
};

int main (int argc, char *argv[])
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>, where:" << endl;
        cerr << "    <input_file> is a name of the XML file to be read" << endl;
        return 1;
    }

    const char* aSource = argv[1];

    ModelData_Model aModel;
    if (!aModel.Open (aSource)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }

    // Visitor to check and print trasformations of instances 
    InstancesTransformationsVisitor aVisitor;
    aModel.Accept (aVisitor);

    return 0;
}

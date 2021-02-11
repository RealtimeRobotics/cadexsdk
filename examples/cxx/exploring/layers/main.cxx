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
#include <cadex/ModelData_Assembly.hxx>
#include <cadex/ModelData_Body.hxx>
#include <cadex/ModelData_BodyList.hxx>
#include <cadex/ModelData_BRepRepresentation.hxx>
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_Layer.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <iostream>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

// Visitor checks elements of specific layer
class LayerItemVisitor : public ModelData_Layer::ItemVisitor
{
public:

    LayerItemVisitor() : myPartsNb(0), myAssembliesNb(0), myInstancesNb(0), myShapesNb(0)
    {
    }

    void GetElementsCount()
    {
        cout << "Number of parts:      " << myPartsNb      << endl;
        cout << "Number of assemblies: " << myAssembliesNb << endl;
        cout << "Number of instances:  " << myInstancesNb  << endl;
        cout << "Number of shapes:     " << myShapesNb     << endl;
    }

protected:

    void operator() (const ModelData_SceneGraphElement& theSGE) override
    {
        if (theSGE.IsOfType<ModelData_Part>()) {
            ++myPartsNb;
        } else if (theSGE.IsOfType<ModelData_Assembly>()) {
            ++myAssembliesNb;
        }  else if (theSGE.IsOfType<ModelData_Instance>()) {
            ++myInstancesNb;
        }
    }

    void operator() (const ModelData_Shape& theShape, const ModelData_BRepRepresentation& theBRep) override
    {
        ++myShapesNb;
    }

private:

    size_t myPartsNb;
    size_t myAssembliesNb;
    size_t myInstancesNb;
    size_t myShapesNb;
};

// Visitor to explore model layers
class LayersVisitor : public ModelData_Model::LayerVisitor
{
protected:

    void operator() (const ModelData_Layer& theLayer) override
    {
        LayerItemVisitor aLayerItemVisitor;
        theLayer.Accept (aLayerItemVisitor);
        cout << "Layer " << theLayer.Name() << " contains:" << endl;
        aLayerItemVisitor.GetElementsCount();
    }
};

// Visitor used to add model's parts to layer
class LayersFiller : public ModelData_Model::CombinedElementVisitor
{
public:

    LayersFiller() : mySubshapesLayer ("SubshapesLayer"), mySGELayer ("SGELayer") // another layers
    {
    }

    const ModelData_Layer& SGELayer()
    {
        return mySGELayer;
    }

    const ModelData_Layer& SubshapesLayer()
    {
        return mySubshapesLayer;
    }

protected:

    void operator() (const ModelData_Part& thePart) override
    {
        mySGELayer.Add (thePart);
        ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
        if (aBRep) {
            ModelData_BodyList aBodyList = aBRep.Get();
            for (ModelData_BodyList::SizeType i = 0; i < aBodyList.Size(); ++i) {
                const ModelData_Body& aBody = aBodyList[i];
                aBRep.AddToLayer (aBody, mySubshapesLayer);
            }
        }
    }

    bool VisitEnter (const ModelData_SceneGraphElement& theElement) override
    {
        mySGELayer.Add (theElement);
        return true;
    }

private:

    ModelData_Layer mySubshapesLayer;
    ModelData_Layer mySGELayer;
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
        cerr << "    <input_file> is a name of the XML file to be read" << endl;
        return 1;
    }

    const char* aSource = argv[1];

    ModelData_Model aModel;

    if (!aModel.Open (aSource)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }

    // Check the model if it has any layer
    ModelData_Model::LayerIterator aLayerIt (aModel);
    if (!aLayerIt.HasNext()) {
        // Create a visitor to fill its layers
        LayersFiller aVisitor;
        aModel.Accept (aVisitor);

        // Add created layers to the model
        aModel.AddLayer (aVisitor.SGELayer());
        aModel.AddLayer (aVisitor.SubshapesLayer());
    }

    LayersVisitor aLayerVisitor;
    aModel.Accept (aLayerVisitor);

    return 0;
}

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


#include <cadex/Base_UTF16String.hxx>
#include <cadex/LicenseManager_Activate.h>
#include <cadex/ModelData_Assembly.hxx>
#include <cadex/ModelData_Instance.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../../cadex_license.cxx"


using namespace std;
using namespace cadex;

class RemovedSGEFinder : public ModelData_Model::VoidElementVisitor
{
public:
    typedef std::unordered_map <ModelData_Assembly,
                                std::vector <ModelData_Instance>,
                                ModelData_BaseObjectHash>           RemovedSGEMapType;

    explicit RemovedSGEFinder (const Base_UTF16String& theNameToRemove) :
        myNameToRemove (theNameToRemove)
    {}

    // Non-root SGEs that can be removed are under assemblies. Iterate
    // through the assembly's child instances and find those that reference
    // SGEs with given name
    bool VisitEnter (const ModelData_Assembly& theElement) override
    {
        for (ModelData_Model::ElementIterator anIt (theElement); anIt.HasNext();) {
            ModelData_Instance aChild = static_cast <ModelData_Instance&> (anIt.Next());

            if (!aChild.Reference().IsNull() && aChild.Reference().Name() == myNameToRemove) {
                mySGEsToRemove[theElement].push_back (aChild);
            }
        }

        return true;
    }

    RemovedSGEMapType& SGEsToRemove()
    {
        return mySGEsToRemove;
    }

private:

    Base_UTF16String    myNameToRemove;
    RemovedSGEMapType   mySGEsToRemove;
};

int main (int argc, char** argv)
{
    auto aKey = LicenseKey::Value();

    // Activate the license (aKey must be defined in cadex_license.cxx)
    if (!CADExLicense_Activate (aKey)) {
        cerr << "Failed to activate CAD Exchanger license." << endl;
        return 1;
    }

    // Get the input
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file> <sge_to_remove>, where:" << endl;
        cerr << "    <input_file>    is a name of the XML file to be read" << endl;
        cerr << "    <input_file>    is a name of the XML file where the output should be stored" << endl;
        cerr << "    <sge_to_remove> is a name of the scene graph elements to remove" << endl;
        return 1;
    }
    const char* aSource  = argv[1];
    const char* anOutput = argv[2];

    // Load the model
    ModelData_Model aModel;
    if (!aModel.Open (aSource)) {
        cerr << "Failed to read the file " << aSource << endl;
        return 1;
    }


    // Remove roots with specified name
    const char* aNameToRemove = argv[3];
    std::vector <ModelData_SceneGraphElement> aRootsToRemove;
    for (ModelData_Model::ElementIterator anIt (aModel); anIt.HasNext();) {
        const auto& anElement = anIt.Next();
        if (anElement.Name() == aNameToRemove) {
            aRootsToRemove.push_back (anElement);
        }
    }
    for (const auto& aRootToRemove : aRootsToRemove) {
        aModel.RemoveRoot (aRootToRemove);
    }

    // Find the rest of scene graph elements that need to be removed and their parents
    RemovedSGEFinder aFinder (aNameToRemove);
    aModel.Accept (aFinder);

    // Perform the recorded removals of non-root SGEs
    auto& anSGEsToRemove = aFinder.SGEsToRemove();
    for (const auto& aParentWithChildren : anSGEsToRemove) {
        auto aParent = aParentWithChildren.first;
        const auto& aChildrenToRemove = aParentWithChildren.second;

        for (const auto& aChildToRemove : aChildrenToRemove) {
            aParent.RemoveInstance (aChildToRemove);
        }
    }

    // Save the result
    aModel.Save (anOutput);

    return 0;
}

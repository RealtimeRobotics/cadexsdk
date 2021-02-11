// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2020, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// This file may be used under the terms and conditions of the License
// Agreement supplied with the software.
//
// This file is provided "AS IS" WITH NO WARRANTY OF ANY KIND, EITHER EXPRESSED
// OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE WARRANTY OF DESIGN,
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// ****************************************************************************


#ifndef _ModelData_SceneGraphElement_HeaderFile
#define _ModelData_SceneGraphElement_HeaderFile

#include <cadex/ModelData_BaseObject.hxx>
#include <cadex/ModelData_Model.hxx>

namespace cadex {

class ModelData_Appearance;
class ModelData_Layer;
class ModelData_PMITable;
class ModelData_PropertyTable;

namespace internal {
class ModelData_SceneGraphElementImpl;
}

class ModelData_SceneGraphElement : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_SceneGraphElementImpl   ImplType;

    //! Constructor.
    /*! Creates a null object (see IsNull()).*/
    ModelData_SceneGraphElement() {}

    __CADEX_EXPORT void SetAppearance (const ModelData_Appearance& theAppearance);
    __CADEX_EXPORT ModelData_Appearance Appearance() const;

    __CADEX_EXPORT void AddProperties (const ModelData_PropertyTable& theProperties);
    __CADEX_EXPORT ModelData_PropertyTable Properties() const;

    __CADEX_EXPORT void AddPMI (const ModelData_PMITable& thePMI);
    __CADEX_EXPORT ModelData_PMITable PMI() const;

    __CADEX_EXPORT void AddToLayer (const ModelData_Layer& theLayer);
    
    class LayerIterator
    {
    public:
        __CADEX_EXPORT explicit LayerIterator (const ModelData_SceneGraphElement& theSGE);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT ModelData_Layer Next();
    private:
        internal::Base_Handle myImpl;
    };

    //! Accepts an element visitor.
    __CADEX_EXPORT void Accept (ModelData_Model::ElementVisitor& theVisitor) const;

protected:

    //! Constructor (reserved for internal use).
    ModelData_SceneGraphElement (const internal::ModelData_BaseObjectImpl* theImpl) :
        ModelData_BaseObject (theImpl)
    {}

    //! Constructor (reserved for internal use).
    ModelData_SceneGraphElement (const internal::ModelData_BaseObjectImpl* theImpl,
        const Base_UTF16String& theName) :
        ModelData_BaseObject (theImpl, theName)
    {}
};

}

#endif

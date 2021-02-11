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


#ifndef _ModelData_Layer_HeaderFile
#define _ModelData_Layer_HeaderFile

#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {
namespace internal {
class ModelData_LayerImpl;
}

class ModelData_BRepRepresentation;
class ModelData_SceneGraphElement;
class ModelData_Shape;

class ModelData_Layer : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_LayerImpl ImplType;

    __CADEX_EXPORT ModelData_Layer();
    __CADEX_EXPORT ModelData_Layer (initialized);
    __CADEX_EXPORT ModelData_Layer (ImplType* theImpl);
    __CADEX_EXPORT ModelData_Layer (const Base_UTF16String& theName);

    __CADEX_MODELDATA_DEFINE_TYPEID

    __CADEX_EXPORT bool IsVisible() const;

    __CADEX_EXPORT bool& IsVisible();

    __CADEX_EXPORT void Add (const ModelData_SceneGraphElement& theElement);

    __CADEX_EXPORT bool Remove (const ModelData_SceneGraphElement& theElement);

    __CADEX_EXPORT bool Find (const ModelData_SceneGraphElement& theElement) const;

    class ItemVisitor
    {
    public:

        __CADEX_EXPORT virtual ~ItemVisitor();

        virtual void operator() (const ModelData_SceneGraphElement& theSGE) = 0;
        virtual void operator() (const ModelData_Shape& theShape, const ModelData_BRepRepresentation& theRep) = 0;
    };

    __CADEX_EXPORT void Accept (ItemVisitor& theVisitor) const;
};

}

#endif

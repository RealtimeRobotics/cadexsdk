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


#ifndef _ModelData_Material_HeaderFile
#define _ModelData_Material_HeaderFile

#include <cadex/ModelData_Color.hxx>
#include <cadex/Base_Macro.hxx>

namespace cadex {

class ModelData_Material
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    __CADEX_EXPORT ModelData_Material();

    //! Constructor.
    ModelData_Material (const ModelData_Color& theAmbientColor,
                        const ModelData_Color& theDiffuseColor,
                        const ModelData_Color& theSpecularColor,
                        const ModelData_Color& theEmissionColor,
                        float theShininess) :
        myAmbientColor (theAmbientColor),
        myDiffuseColor (theDiffuseColor),
        mySpecularColor (theSpecularColor),
        myEmissionColor (theEmissionColor),
        myShininess (theShininess)
    {}

    //! Constructor.
    __CADEX_EXPORT ModelData_Material (const ModelData_Color& theDiffuseColor);

    __CADEX_DEFINE_PROPERTY(ModelData_Color,AmbientColor)
    __CADEX_DEFINE_PROPERTY(ModelData_Color,DiffuseColor)
    __CADEX_DEFINE_PROPERTY(ModelData_Color,SpecularColor)
    __CADEX_DEFINE_PROPERTY(ModelData_Color,EmissionColor)

    /*! \a theValue must be in the [0, 128] range.*/
    __CADEX_DEFINE_PRIMITIVE_PROPERTY(float,Shininess)
};


__CADEX_EXPORT bool operator== (const ModelData_Material& theV1, const ModelData_Material& theV2);

class ModelData_MaterialHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Material& theMaterial) const;
};

}

#endif

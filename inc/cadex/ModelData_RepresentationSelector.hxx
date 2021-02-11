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


#ifndef _ModelData_RepresentationSelector_HeaderFile
#define _ModelData_RepresentationSelector_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_VISUALIZATION
#include <cadex/Base_NoCopy.hxx>
#include <cadex/Base_UTF16String.hxx>
#include <cadex/ModelData_RepresentationMask.hxx>
#include <memory>

namespace cadex {

class ModelData_RepresentationSelector: public internal::Base_NoAssignment
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT

    enum Type { Mask, Name };

    __CADEX_EXPORT virtual ~ModelData_RepresentationSelector();

    virtual bool IsEqual (const ModelData_RepresentationSelector& theOther) const = 0;

    __CADEX_DEFINE_PRIMITIVE_PROPERTY (Type, SelectorType)

protected:
    ModelData_RepresentationSelector (const Type theType);
};

//! Represents a representation mode as a mask (according to enum ModelData_RepresentationMask)
class ModelData_RepresentationMaskSelector: public ModelData_RepresentationSelector
{
public:
    __CADEX_EXPORT ModelData_RepresentationMaskSelector (const int theMask);

    __CADEX_EXPORT ModelData_RepresentationMaskSelector (const ModelData_RepresentationMask theMask);

    __CADEX_EXPORT virtual bool IsEqual (const ModelData_RepresentationSelector& theOther) const override;

    __CADEX_DEFINE_PRIMITIVE_PROPERTY (ModelData_RepresentationMask, Mask)
};

//! Represents a representation mode as a name of a representation
class ModelData_RepresentationNameSelector: public ModelData_RepresentationSelector
{
public:
    __CADEX_EXPORT ModelData_RepresentationNameSelector (const Base_UTF16String& theName);

    __CADEX_EXPORT virtual bool IsEqual (const ModelData_RepresentationSelector& theOther) const override;

    __CADEX_DEFINE_PROPERTY (Base_UTF16String, Name)
};

}

#endif // __CADEX_PREVIEW_VISUALIZATION
#endif // _ModelData_RepresentationSelector_HeaderFile

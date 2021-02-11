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


#ifndef _ModelData_Representation_HeaderFile
#define _ModelData_Representation_HeaderFile

#include <cadex/ModelData_Part.hxx>

namespace cadex {
namespace internal {
class ModelData_RepresentationImpl;
}

class ModelData_Representation : public ModelData_BaseObject
{
public:

    typedef cadex::internal::ModelData_RepresentationImpl   ImplType;

    //! Constructor.
    /*! Creates a null object (see IsNull()).*/
    ModelData_Representation() {}

    //! Accepts a representation visitor.
    __CADEX_EXPORT void Accept (ModelData_Part::RepresentationVisitor& theVisitor) const;

protected:

    //! Constructor (reserved for internal use).
    ModelData_Representation (internal::ModelData_BaseObjectImpl* theImpl) :
        ModelData_BaseObject (theImpl)
    {}
};

}

#endif

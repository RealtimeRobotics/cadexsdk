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

#ifndef _ModelData_PolyShape_HeaderFile
#define _ModelData_PolyShape_HeaderFile

#include <cadex/ModelData_BaseObject.hxx>

namespace cadex {

class ModelData_PolyShape : public ModelData_BaseObject
{
public:

    //! Constructor.
    /*! Creates a null object (see IsNull()).*/
    ModelData_PolyShape() {}

protected:

    //! Constructor (reserved for internal use).
    ModelData_PolyShape (const internal::ModelData_BaseObjectImpl* theImpl) :
        ModelData_BaseObject (theImpl)
    {}
};

}

#endif 
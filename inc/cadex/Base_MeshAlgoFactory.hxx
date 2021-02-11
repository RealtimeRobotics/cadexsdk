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


#ifndef _Base_MeshAlgoFactory_HeaderFile
#define _Base_MeshAlgoFactory_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_SharedPtr.hxx>

namespace cadex {
namespace internal {

class Base_MeshAlgoFactoryImpl;

class Base_MeshAlgoFactory
{
public:

    //! Constructor.
    /*! Creates a null object (IsNull() returns true).*/
    Base_MeshAlgoFactory() {}

    //! Constructor.
    __CADEX_EXPORT Base_MeshAlgoFactory (const std::shared_ptr<Base_MeshAlgoFactoryImpl>& theImpl);

    //! Returns an implementation object.
    const std::shared_ptr<Base_MeshAlgoFactoryImpl> Impl() const { return myImpl; }

    //! Returns true if the object is null.
    bool IsNull() const { return !myImpl; }

    operator bool() const { return !IsNull(); }

protected:

    std::shared_ptr<Base_MeshAlgoFactoryImpl>   myImpl;
};

}}

#endif

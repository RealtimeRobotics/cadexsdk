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


#ifndef _Base_MissingExternalReference_HeaderFile
#define _Base_MissingExternalReference_HeaderFile

#if __CADEX_PREVIEW_READER_STATISTICS

#include <memory>

namespace cadex {
class Base_UTF16String;
class ModelData_SceneGraphElement;

namespace internal {
class Base_MissingExternalReferenceImpl;
}

class Base_MissingExternalReference
{
public:
    __CADEX_EXPORT Base_MissingExternalReference();

    explicit Base_MissingExternalReference (
        const std::shared_ptr <internal::Base_MissingExternalReferenceImpl>& theImpl);

    __CADEX_EXPORT const ModelData_SceneGraphElement& ParentElement() const;
    __CADEX_EXPORT const Base_UTF16String& FilePath() const;

private:
    std::shared_ptr <internal::Base_MissingExternalReferenceImpl> myImpl;
};

}

#endif
#endif

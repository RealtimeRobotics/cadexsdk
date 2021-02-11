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


#ifndef _Base_Reader_HeaderFile
#define _Base_Reader_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cadex/Base_StreamProvider.hxx>

#include <istream>
#include <memory>

class TopoDS_Shape;

namespace cadex {

class Base_ProgressStatus;
class Base_ReaderStatistics;
class Base_UTF16String;
class ModelData_Model;

namespace internal {
class Base_Reader_Private;
}

class Base_Reader
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ~Base_Reader();

    //! Reads the file into memory.
    __CADEX_EXPORT bool ReadFile (const Base_UTF16String& theFileName);

    //! Reads the file into memory.
    __CADEX_EXPORT bool ReadFile (std::istream& theStream);

    //! Reads the file into memory.
    __CADEX_EXPORT bool ReadFile (const std::shared_ptr<Base_IStreamProviderFactory>& theFactory,
        const Base_UTF16String& theFileName);

    //! Converts read file into a resulting model.
    __CADEX_EXPORT bool Transfer (ModelData_Model& theModel);

    //! Converts read file into a resulting shape.
    __CADEX_EXPORT bool Transfer (TopoDS_Shape& theShape);

    //! Returns a progress status.
    __CADEX_EXPORT Base_ProgressStatus& ProgressStatus() const;

#if __CADEX_PREVIEW_READER_STATISTICS
    //! Returns an object containing information about import process.
    __CADEX_EXPORT Base_ReaderStatistics Statistics() const;
#endif

    //! \internal
    /*! Returns the pointer to the implementation object.

        \warning This function is not part of CAD Exchanger API and should not be used.
    */
    internal::Base_Reader_Private* Impl() const { return myImpl.get(); }

    //! Reserved for internal use.
    template<typename T>
    T* Impl() const { return static_cast<T*> (Impl()); }

protected:
    //! Constructor.
    __CADEX_EXPORT Base_Reader (internal::Base_Reader_Private* theImpl);

private:

    std::shared_ptr<internal::Base_Reader_Private>  myImpl;
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExCored.lib")
        #else
            #pragma comment(lib, "CadExCore.lib")
        #endif
    #endif
#endif

#endif

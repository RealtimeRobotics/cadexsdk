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


#ifndef _Base_Writer_HeaderFile
#define _Base_Writer_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cadex/Base_SharedPtr.hxx>
#include <cadex/Base_WriterStatistics.hxx>
#include <ostream>

class TopoDS_Shape;

namespace cadex {

class Base_ProgressStatus;
class Base_UTF16String;
class Base_Model;
class ModelData_Model;

namespace internal {
class Base_Writer_Private;
}

class Base_Writer
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ~Base_Writer();

    //! Converts source model into memory representation of the target file.
    __CADEX_EXPORT bool Transfer (const ModelData_Model& theModel);

    //! Converts source shape into memory representation of the target file.
    __CADEX_EXPORT bool Transfer (const TopoDS_Shape& theShape);

    //! Writes contents to a target file.
    __CADEX_EXPORT bool WriteFile (const Base_UTF16String& theFileName);

    //! Writes contents to a target stream.
    __CADEX_EXPORT bool WriteFile (std::ostream& theStream);

    //! Returns a progress status.
    __CADEX_EXPORT Base_ProgressStatus& ProgressStatus() const;

#if __CADEX_PREVIEW_WRITER_STATISTICS
    //! Returns an object containing information about export process.
    __CADEX_EXPORT Base_WriterStatistics Statistics() const;
#endif
    //! \internal
    /*! Returns the pointer to the implementation object.

        \warning This function is not part of CAD Exchanger API and should not be used.
    */
    internal::Base_Writer_Private* Impl() const { return myImpl.get(); }

    //! Reserved for internal use.
    template<typename T>
    T* Impl() const { return static_cast<T*> (Impl()); }

protected:
    //! Constructor.
    __CADEX_EXPORT Base_Writer (internal::Base_Writer_Private* theImpl);

private:

    std::shared_ptr<internal::Base_Writer_Private>  myImpl;
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

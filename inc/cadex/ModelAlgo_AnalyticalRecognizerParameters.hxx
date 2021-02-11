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


#ifndef _ModelAlgo_AnalyticalRecognizerParameters_HeaderFile
#define _ModelAlgo_AnalyticalRecognizerParameters_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_SharedPtr.hxx>

namespace cadex {

namespace internal {
class ModelAlgo_AnalyticalRecognizerParametersImpl;
}

class ModelAlgo_AnalyticalRecognizerParameters
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    __CADEX_EXPORT ModelAlgo_AnalyticalRecognizerParameters();

    __CADEX_EXPORT void SetProcessSurfaces (bool theProcess);
    __CADEX_EXPORT bool ProcessSurfaces() const;

    __CADEX_EXPORT void SetProcessCurves (bool theProcess);
    __CADEX_EXPORT bool ProcessCurves() const;

    __CADEX_EXPORT void SetProcessCurves2d (bool theProcess);
    __CADEX_EXPORT bool ProcessCurves2d() const;

    //! Returns an implementation object.
    /*! \internal
    */
    const std::shared_ptr<internal::ModelAlgo_AnalyticalRecognizerParametersImpl>& Impl() const { return myImpl; }

private:
    std::shared_ptr<internal::ModelAlgo_AnalyticalRecognizerParametersImpl>   myImpl;
};

}

#endif
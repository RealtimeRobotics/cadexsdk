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


#ifndef _ModelAlgo_BSplineConverterParameters_HeaderFile
#define _ModelAlgo_BSplineConverterParameters_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <memory>

namespace cadex {

namespace internal {
class ModelAlgo_BSplineConverterParametersImpl;
}

class ModelAlgo_BSplineConverterParameters
{
public:

    enum PriorityConstraintType {
        NumOfSpans,
        Degree
    };

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    __CADEX_EXPORT ModelAlgo_BSplineConverterParameters();

    __CADEX_EXPORT bool ProcessSurfaces() const;
    __CADEX_EXPORT bool& ProcessSurfaces();
    __CADEX_EXPORT void SetProcessSurfaces (bool theValue);

    __CADEX_EXPORT bool ProcessCurves() const;
    __CADEX_EXPORT bool& ProcessCurves();
    __CADEX_EXPORT void SetProcessCurves (bool theValue);

    __CADEX_EXPORT bool ProcessCurves2d() const;
    __CADEX_EXPORT bool& ProcessCurves2d();
    __CADEX_EXPORT void SetProcessCurves2d (bool theValue);

    __CADEX_EXPORT int MaxDegree() const;
    __CADEX_EXPORT int& MaxDegree();
    __CADEX_EXPORT void SetMaxDegree (int theValue);

    __CADEX_EXPORT int MaxNumOfSpans() const;
    __CADEX_EXPORT int& MaxNumOfSpans();
    __CADEX_EXPORT void SetMaxNumOfSpans (int theValue);

    __CADEX_EXPORT double MaxTolerance() const;
    __CADEX_EXPORT double& MaxTolerance();
    __CADEX_EXPORT void SetMaxTolerance (double theValue);

    __CADEX_EXPORT PriorityConstraintType PriorityConstraint() const;
    __CADEX_EXPORT PriorityConstraintType& PriorityConstraint();
    __CADEX_EXPORT void SetPriorityConstraint (PriorityConstraintType theValue);

    //! Returns an implementation object.
    /*! \internal
    */
    const std::shared_ptr<internal::ModelAlgo_BSplineConverterParametersImpl>& Impl() const { return myImpl; }

private:

    //! Internal implementation object.
    std::shared_ptr<internal::ModelAlgo_BSplineConverterParametersImpl>   myImpl;
};

}

#endif
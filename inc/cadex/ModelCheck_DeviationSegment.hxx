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


#ifndef _ModelCheck_DeviationSegment_HeaderFile
#define _ModelCheck_DeviationSegment_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_SharedPtr.hxx>


namespace cadex {
namespace internal {
class ModelCheck_DeviationSegmentImpl;
}

class ModelCheck_DeviationSegment
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    typedef std::pair<double, double>    ParamsType;

    //! Constructor.
    __CADEX_EXPORT ModelCheck_DeviationSegment();

    //! Returns \c true if segment is empty and \c false otherwise.
    __CADEX_EXPORT bool IsEmpty() const;

    //! Returns a parameter range of segment for first curve.
    __CADEX_EXPORT const ParamsType& Curve1Params() const;

    //! Returns a parameter range of segment for second curve.
    __CADEX_EXPORT const ParamsType& Curve2Params() const;

    //! Returns a distance between curves on this segment.
    __CADEX_EXPORT double Distance() const;

    __CADEX_DEFINE_IMPL (ModelCheck_DeviationSegment)
};

}

#endif

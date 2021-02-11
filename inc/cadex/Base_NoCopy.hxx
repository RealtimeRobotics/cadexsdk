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


#ifndef _Base_NoCopy_HeaderFile
#define _Base_NoCopy_HeaderFile

namespace cadex {
namespace internal {

class Base_NoAssignment
{
private:
    Base_NoAssignment& operator= (const Base_NoAssignment&);
};

class Base_NoCopy : public Base_NoAssignment
{
public:
    //! Constructor.
    /*! Empty constructor.*/
    Base_NoCopy() {}

private:
    Base_NoCopy (const Base_NoCopy&);
};

}}

#endif

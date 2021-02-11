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


#ifndef _MeshAlgo_MefistoFactory_HeaderFile
#define _MeshAlgo_MefistoFactory_HeaderFile

#include <cadex/Base_MeshAlgoFactory.hxx>

namespace cadex {

class MeshAlgo_MefistoFactory : public internal::Base_MeshAlgoFactory
{
public:

    /*! \struct Parameters
        \brief Defines parameters used by the Mefisto meshing algorithm.

        Parameters include:
        \li Absolute value of the global maximum size of an element. 
        \li Relative value of the global maximum size of an element. 
            Relative value is calculated by multiplying the value by the diagonal of the
            bounding box of the parent shape (Shell or Solid).
        \li Relative value of the local maximum size of element edge. 
            Relative value is calculated per each face by multiplying the value by the
            diagonal of the bounding box of the face.

        If any of these parameters is negative or zero then it is ignored. At least one of
        them must be positive. Relative parameters must be within a (0., 1.] range.

        \sa \ref sdk_meshing_advalgos.
    */
    struct Parameters {
        //! Constructor.
        /*! Constructs parameters with \a myGlobAbsMaxSize as -1., \a myGlobRelMaxSize as -1.,
            \a myLocRelMaxSize as 5% (1./20.) of the corresponding
            bounding box diagonal. Thus, only local max size is used, global ones are ignored.
        */
        Parameters() : myGlobAbsMaxSize (-1.), myGlobRelMaxSize (-1.), myLocRelMaxSize (1./20.) {}

        //! Constructor.
        /*! Constructs parameters using explicitly specified values.
        */
        Parameters(double theAbsMaxSize, double theGlobRelMaxSize, double theLocRelMaxSize) :
            myGlobAbsMaxSize (theAbsMaxSize), myGlobRelMaxSize (theGlobRelMaxSize),
            myLocRelMaxSize (theLocRelMaxSize) {}

        double  myGlobAbsMaxSize; //!< Absolute value of the global maximum size of element edge.
        double  myGlobRelMaxSize; //!< Relative value of the global maximum size of element edge.
        double  myLocRelMaxSize; //!< Relative value of the local maximum size of element edge.
    };

    //! Constructor.
    __CADEX_EXPORT MeshAlgo_MefistoFactory();

    //! Sets parameters to be used by the factory.
    __CADEX_EXPORT void SetParameters (const Parameters& theParam);
};

}


#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExMeshd.lib")
        #else
            #pragma comment(lib, "CadExMesh.lib")
        #endif
    #endif
#endif

#endif

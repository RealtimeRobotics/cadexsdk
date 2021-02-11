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


#ifndef _MeshAlgo_NetgenFactory_HeaderFile
#define _MeshAlgo_NetgenFactory_HeaderFile

#include <cadex/Base_MeshAlgoFactory.hxx>


namespace cadex {

class MeshAlgo_NetgenFactory : public internal::Base_MeshAlgoFactory
{
public:
    struct Parameters {

        enum Granularity {
            VeryCoarse, Coarse, Moderate, Fine, VeryFine, Custom
        };

        //! Constructor.
        /*! Constructs parameters with \a myGlobAbsMaxSize as -1., \a myGlobRelMaxSize as -1.,
            \a myLocRelMaxSize as 10% (1./10.) of the corresponding bounding box diagonal,
            \a myGlobAbsMinSize as -1., \a myGlobRelMinSize as 1% (1./100.), \a myOptSteps as 3.
            \a myGranularity as Moderate,
            \a myIsVolumeMesh as false,
            \a myVolumeOptSteps as 2.
        */
        Parameters() : myGlobAbsMaxSize (-1.), myGlobRelMaxSize (-1.), myLocRelMaxSize (1./10.),
            myGlobAbsMinSize (-1.), myGlobRelMinSize (1. / 100.), myOptSteps (3),
            myIsVolumeMesh (false), myVolumeOptSteps (2)
        { SetGranularity (Moderate); }

        //! Sets mesh granularity policy.
        void SetGranularity (Granularity theVal)
        {
            myGranularity = theVal;
            switch (theVal) {
            case VeryCoarse: myGrading = 0.7; mySegPerEdge = 1; myCrv = 1. ; break;
            case Coarse:     myGrading = 0.5; mySegPerEdge = 1; myCrv = 1.5; break;
            case Moderate:   myGrading = 0.3; mySegPerEdge = 1; myCrv = 2. ; break;
            case Fine:       myGrading = 0.2; mySegPerEdge = 2; myCrv = 3. ; break;
            case VeryFine:   myGrading = 0.1; mySegPerEdge = 3; myCrv = 5. ; break;
            default: break;
            }
        }

        double          myGlobAbsMaxSize;
        double          myGlobRelMaxSize;
        double          myLocRelMaxSize;

        double          myGlobAbsMinSize;
        double          myGlobRelMinSize;

        Granularity     myGranularity;
        double          myGrading;
        unsigned int    mySegPerEdge;
        double          myCrv;

        unsigned int    myOptSteps;

        bool            myIsVolumeMesh;
        unsigned int    myVolumeOptSteps;
    };

    //! Constructor.
    __CADEX_EXPORT MeshAlgo_NetgenFactory();

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

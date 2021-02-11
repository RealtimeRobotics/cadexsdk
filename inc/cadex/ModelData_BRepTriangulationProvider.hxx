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


#ifndef _ModelData_BRepTriangulationProvider_HeaderFile
#define _ModelData_BRepTriangulationProvider_HeaderFile

#include <cadex/ModelData_PolyRepresentation.hxx>

namespace cadex {

class ModelData_BRepRepresentation;

class ModelData_BRepTriangulationProvider : public ModelData_PolyRepresentation::Provider
{
public:

    //! Constructor.
    __CADEX_EXPORT ModelData_BRepTriangulationProvider (
        const ModelData_BRepRepresentation& theRep,
        const ModelAlgo_BRepMesherParameters& theParameters = ModelAlgo_BRepMesherParameters());

    //! Destructor.
    __CADEX_EXPORT virtual ~ModelData_BRepTriangulationProvider();

    __CADEX_EXPORT const ModelData_BRepRepresentation& Ref() const;


    //! Sets mesher parameters.
    __CADEX_EXPORT void SetParameters (const ModelAlgo_BRepMesherParameters& theParameters);

    //! Returns mesher parameters.
    __CADEX_EXPORT const ModelAlgo_BRepMesherParameters& Parameters() const;

    //! Returns mesher parameters.
    __CADEX_EXPORT ModelAlgo_BRepMesherParameters& Parameters();


    //! Feeds the representation.
    __CADEX_EXPORT virtual void Feed (ModelData_PolyRepresentation& theRepresentation) const override;

private:

    ModelData_BRepTriangulationProvider (const ModelData_BRepTriangulationProvider&);
    ModelData_BRepTriangulationProvider& operator= (const ModelData_BRepTriangulationProvider&);

    internal::Base_Handle myImpl;
};

}

#endif

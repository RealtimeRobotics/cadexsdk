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


#ifndef _ModelAlgo_BSplineConverter_HeaderFile
#define _ModelAlgo_BSplineConverter_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <memory>

namespace cadex {

class ModelAlgo_BSplineConverterParameters;
class ModelData_Model;
class ModelData_SceneGraphElement;
class ModelData_Shape;

namespace internal {
class ModelAlgo_BSplineConverterImpl;
}

class ModelAlgo_BSplineConverter
{
public:

    //! Defines a converter parameters type.
    typedef ModelAlgo_BSplineConverterParameters ParametersType;

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelAlgo_BSplineConverter();

    __CADEX_EXPORT ModelAlgo_BSplineConverter (const ParametersType& theParameters);

    __CADEX_EXPORT const ParametersType& Parameters() const;

    __CADEX_EXPORT ParametersType& Parameters();

    __CADEX_EXPORT void SetParameters (const ParametersType& theParameters);

    __CADEX_EXPORT void Perform (const ModelData_Model& theModel) const;

    __CADEX_EXPORT void Perform (const ModelData_SceneGraphElement& theElement) const;

    __CADEX_EXPORT ModelData_Shape Perform (const ModelData_Shape& theShape) const;


    //! Returns an implementation object.
    /*! \internal
    */
    const std::shared_ptr<internal::ModelAlgo_BSplineConverterImpl>& Impl() const { return myImpl; }

protected:

    //! Internal implementation object.
    std::shared_ptr<internal::ModelAlgo_BSplineConverterImpl>   myImpl;

};

}

#endif

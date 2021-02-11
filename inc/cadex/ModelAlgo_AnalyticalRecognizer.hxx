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


#ifndef _ModelAlgo_AnalyticalRecognizer_HeaderFile
#define _ModelAlgo_AnalyticalRecognizer_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_SharedPtr.hxx>

namespace cadex {

class ModelAlgo_AnalyticalRecognizerParameters;
class ModelData_Model;
class ModelData_SceneGraphElement;
class ModelData_Shape;

namespace internal {
class ModelAlgo_AnalyticalRecognizerImpl;
}

class ModelAlgo_AnalyticalRecognizer
{
public:

    //! Defines a parameters type for Analytical recognizer.
    typedef ModelAlgo_AnalyticalRecognizerParameters ParametersType;

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    __CADEX_EXPORT ModelAlgo_AnalyticalRecognizer();

    //! Constructor.
    __CADEX_EXPORT ModelAlgo_AnalyticalRecognizer (const ParametersType& theParameters);

    //! Returns parameters.
    __CADEX_EXPORT const ParametersType& Parameters() const;

    //! Returns parameters.
    __CADEX_EXPORT ParametersType& Parameters();


    __CADEX_EXPORT void Perform (const ModelData_Model& theModel) const;

    __CADEX_EXPORT void Perform (const ModelData_SceneGraphElement& theElement) const;

    __CADEX_EXPORT ModelData_Shape Perform (const ModelData_Shape& theShape) const;

    bool Status() const;


    //! Returns an implementation object.
    /*! \internal
    */
    const std::shared_ptr<internal::ModelAlgo_AnalyticalRecognizerImpl>& Impl() const { return myImpl; }

private:

    //! Internal implementation object.
    std::shared_ptr<internal::ModelAlgo_AnalyticalRecognizerImpl> myImpl;

};

}

#endif
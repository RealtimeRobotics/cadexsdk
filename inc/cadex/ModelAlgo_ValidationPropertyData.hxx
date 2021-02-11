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


#ifndef _ModelAlgo_ValidationPropertyData_HeaderFile
#define _ModelAlgo_ValidationPropertyData_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <memory>


namespace cadex {

class ModelData_Direction;
class ModelData_Point;

namespace internal {
class ModelAlgo_ValidationPropertyDataImpl;
}

class ModelAlgo_ValidationPropertyData
{
public:
    typedef cadex::internal::ModelAlgo_ValidationPropertyDataImpl   ImplType;

    __CADEX_EXPORT ModelAlgo_ValidationPropertyData();

    __CADEX_EXPORT double  Volume() const;
    __CADEX_EXPORT double& Volume();

    __CADEX_EXPORT double  SurfaceArea() const;
    __CADEX_EXPORT double& SurfaceArea();

    __CADEX_EXPORT const ModelData_Point& Centroid() const;
    __CADEX_EXPORT ModelData_Point& Centroid();

    __CADEX_EXPORT const ModelData_Direction& FirstAxisOfInertia() const;
    __CADEX_EXPORT ModelData_Direction& FirstAxisOfInertia();

    __CADEX_EXPORT const ModelData_Direction& SecondAxisOfInertia() const;
    __CADEX_EXPORT ModelData_Direction& SecondAxisOfInertia();

    __CADEX_EXPORT const ModelData_Direction& ThirdAxisOfInertia() const;
    __CADEX_EXPORT ModelData_Direction& ThirdAxisOfInertia();

    ImplType* Impl() const { return myImpl.get(); }

private:
    std::shared_ptr<ImplType>   myImpl;
};

}

#endif

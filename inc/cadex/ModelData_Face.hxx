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


#ifndef _ModelData_Face_HeaderFile
#define _ModelData_Face_HeaderFile

#include <cadex/ModelData_Shape.hxx>

class TopoDS_Face;

namespace cadex {

class ModelData_Surface;
class ModelData_Wire;

class ModelData_Face : public ModelData_Shape
{
public:

    ModelData_Face() {}

    __CADEX_EXPORT ModelData_Face (const ModelData_Surface& theSurface, bool theMakeWire = false);

    __CADEX_EXPORT ModelData_Face (const ModelData_Surface& theSurface, const ModelData_Wire& theWire);

    __CADEX_EXPORT ModelData_Face (const ModelData_Surface& theSurface, double theUMin, double theUMax, double theVMin, double theVMax);

    __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(ModelData_Face, TopoDS_Face)

    __CADEX_EXPORT bool Append (const ModelData_Wire& theWire);

    __CADEX_EXPORT ModelData_Surface Surface() const;

    __CADEX_EXPORT ModelData_Wire OuterWire() const;

    __CADEX_EXPORT static const ModelData_Face& Cast (const ModelData_Shape& theShape);

    __CADEX_EXPORT static ModelData_Face& Cast (ModelData_Shape& theShape);
};

}

#endif

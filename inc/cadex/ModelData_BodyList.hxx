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


#ifndef _ModelData_BodyList_HeaderFile
#define _ModelData_BodyList_HeaderFile

#include <cadex/ModelData_Shape.hxx>

class TopoDS_Compound;

namespace cadex {

class ModelData_Body;

class ModelData_BodyList : public ModelData_Shape
{
public:

    typedef size_t  SizeType;

    __CADEX_EXPORT ModelData_BodyList();

    __CADEX_EXPORT static const ModelData_BodyList& Cast (const ModelData_Shape& theShape);

    __CADEX_EXPORT static ModelData_BodyList& Cast (ModelData_Shape& theShape);

    __CADEX_EXPORT void Append (const ModelData_Body& theChild);

    __CADEX_EXPORT void Append (const ModelData_BodyList& theChildren);

    __CADEX_EXPORT const TopoDS_Shape& ToOCC() const;

    __CADEX_DEFINE_CONST_CAST_OPERATOR(TopoDS_Compound)

    __CADEX_EXPORT SizeType Size() const;

    __CADEX_EXPORT const ModelData_Body& First() const { return Element(0); }

    __CADEX_EXPORT const ModelData_Body& Element (SizeType theIndex) const;

    const ModelData_Body& operator[] (SizeType theIndex) const { return Element (theIndex); }

private:

    __CADEX_EXPORT ModelData_BodyList (const TopoDS_Compound& theOther);

#ifndef SWIG
    //to prevent implicit cast, use explicit ToOCCShape() instead
    using ModelData_Shape::operator const TopoDS_Shape&;
#endif

    friend class ModelData_ShapeFactory;
};

}

#endif

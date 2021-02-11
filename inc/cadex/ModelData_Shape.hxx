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


#ifndef _ModelData_Shape_HeaderFile
#define _ModelData_Shape_HeaderFile

#include <cadex/Base_Handle.hxx>
#include <cadex/Base_NoCopy.hxx>
#include <cadex/ModelData_ShapeOrientation.hxx>
#include <cadex/ModelData_ShapeType.hxx>

class TopoDS_Shape;

namespace cadex {

namespace internal {
class ModelData_ShapeImpl;
class ModelData_ShapeIteratorImpl;
}

class ModelData_Shape
{
public:

    class Iterator : private internal::Base_NoCopy
    {
    public:
        __CADEX_EXPORT Iterator (const ModelData_Shape& theShape);
        __CADEX_EXPORT Iterator (const ModelData_Shape& theShape, ModelData_ShapeType theType);
        __CADEX_EXPORT ~Iterator();
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT ModelData_Shape Next();
    private:
        internal::Base_Handle   myImpl;
    };

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    __CADEX_EXPORT ModelData_Shape();
    __CADEX_EXPORT ModelData_Shape (const ModelData_Shape& theOther);
    __CADEX_EXPORT ModelData_Shape (ModelData_Shape&& theOther);

    __CADEX_EXPORT ~ModelData_Shape();

    __CADEX_EXPORT ModelData_Shape& operator= (const ModelData_Shape& theOther);
    __CADEX_EXPORT ModelData_Shape& operator= (ModelData_Shape&& theOther);

    __CADEX_DEFINE_CONST_CAST_OPERATOR(TopoDS_Shape)

    __CADEX_EXPORT ModelData_ShapeType Type() const;

    __CADEX_EXPORT ModelData_ShapeOrientation Orientation() const;

    __CADEX_EXPORT ModelData_Shape Reversed() const;

    __CADEX_EXPORT ModelData_Shape Oriented (ModelData_ShapeOrientation theOrientation) const;

    void Nullify() { myImpl.reset(); }

    __CADEX_EXPORT bool IsNull() const;

    operator bool() const
    {
        return !IsNull();
    }

    __CADEX_EXPORT bool IsEqual (const ModelData_Shape& theOther) const;

    __CADEX_EXPORT bool IsSame (const ModelData_Shape& theOther) const;

    __CADEX_EXPORT internal::ModelData_ShapeImpl* Impl() const;

protected:

    __CADEX_EXPORT ModelData_Shape (const TopoDS_Shape& theOther, bool);
    __CADEX_EXPORT ModelData_Shape (internal::ModelData_ShapeImpl* theImpl);

    internal::Base_Handle   myImpl;

private:
    __CADEX_EXPORT explicit ModelData_Shape (const TopoDS_Shape& theRef);

    friend class internal::ModelData_ShapeIteratorImpl;
};

__CADEX_EXPORT bool operator== (const ModelData_Shape& theShape1, const ModelData_Shape& theShape2);

//! Non-equality operator.
inline bool operator!= (const ModelData_Shape& theShape1, const ModelData_Shape& theShape2)
{
    return !(theShape1 == theShape2);
}

class ModelData_UnorientedShapeHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Shape& theShape) const;
};

class ModelData_OrientedShapeHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Shape& theShape) const;
};

class ModelData_UnorientedShapeEqual
{
public:
    __CADEX_EXPORT bool operator() (const ModelData_Shape& theShape1, const ModelData_Shape& theShape2) const;
};

class ModelData_OrientedShapeEqual
{
public:
    __CADEX_EXPORT bool operator() (const ModelData_Shape& theShape1, const ModelData_Shape& theShape2) const;
};

}

#endif

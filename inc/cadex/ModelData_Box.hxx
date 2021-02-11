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


#ifndef _ModelData_Box_HeaderFile
#define _ModelData_Box_HeaderFile

#include <cadex/ModelData_Point.hxx>
#include <cadex/Base_Macro.hxx>
#include <float.h>

class Bnd_Box;

namespace cadex {

class ModelData_Box
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    /*! Creates a box with infinite boundaries.*/
    ModelData_Box() :
        myMinCorner (-DBL_MAX, -DBL_MAX, -DBL_MAX),
        myMaxCorner ( DBL_MAX,  DBL_MAX,  DBL_MAX)
    {}

    //! Constructor.
    /*! Creates a box with specified corners.*/
    __CADEX_EXPORT ModelData_Box (const ModelData_Pointd& theCorner1, const ModelData_Pointd& theCorner2);

    //! Constructor.
    __CADEX_EXPORT ModelData_Box (const Bnd_Box& theBox);

    __CADEX_DEFINE_PROPERTY(ModelData_Point,MinCorner)
    __CADEX_DEFINE_PROPERTY(ModelData_Point,MaxCorner)

    const ModelData_Point& Corner (size_t theIdx) const
    {
        return (&myMinCorner)[theIdx];
    }

    //! Returns a center point.
    /*! Returns a middle of the diagonal between MinCorner() and MaxCorner().*/
    ModelData_Point Center() const
    {
        return (myMinCorner + myMaxCorner) / 2.;
    }

    //! Adds a point into the bounding box.
    __CADEX_EXPORT void Add (const ModelData_Point& thePoint);

    //! Accumulates another bounding box.
    __CADEX_EXPORT void Add (const ModelData_Box& theBox);

    //! Resets the bounding box.
    __CADEX_EXPORT void Clear();

    void SetXRange (double theMin, double theMax)
    {
        SetRange (0, theMin, theMax);
    }

    void SetYRange (double theMin, double theMax)
    {
        SetRange (1, theMin, theMax);
    }

    void SetZRange (double theMin, double theMax)
    {
        SetRange (2, theMin, theMax);
    }

    void SetRange (size_t theIdx, double theMin, double theMax)
    {
        myMinCorner[theIdx] = theMin;
        myMaxCorner[theIdx] = theMax;
    }

    double Range (size_t theIdx) const { return abs (myMaxCorner[theIdx] - myMinCorner[theIdx]); }

    double XRange() const { return Range (0); }

    double YRange() const { return Range (1); }

    double ZRange() const { return Range (2); }

    void Enlarge (double theX, double theY, double theZ)
    {
        myMinCorner.X() -= theX / 2.;
        myMaxCorner.X() += theX / 2.;
        myMinCorner.Y() -= theY / 2.;
        myMaxCorner.Y() += theY / 2.;
        myMinCorner.Z() -= theZ / 2.;
        myMaxCorner.Z() += theZ / 2.;
    }

    void Enlarge (double theSize)
    {
        Enlarge (theSize, theSize, theSize);
    }

    ModelData_Box Enlarged (double theX, double theY, double theZ) const
    {
        auto r = *this;
        r.Enlarge (theX, theY, theZ);
        return r;
    }

    ModelData_Box Enlarged (double theSize) const
    {
        auto r = *this;
        r.Enlarge (theSize);
        return r;
    }

    //! Returns true if the point lies inside the box.
    bool IsIn (const ModelData_Point& thePoint) const
    {
        return thePoint.X() >= myMinCorner.X() && thePoint.X() <= myMaxCorner.X() &&
               thePoint.Y() >= myMinCorner.Y() && thePoint.Y() <= myMaxCorner.Y() &&
               thePoint.Z() >= myMinCorner.Z() && thePoint.Z() <= myMaxCorner.Z();
    }

    //! Returns the other box has at least one common point with this box.
    bool Intersects (const ModelData_Box& theOther) const
    {
        bool anIsOut = false;
        for (size_t i = 0; i < 3; ++i) {
            anIsOut |= (         myMaxCorner[i] < theOther.myMinCorner[i]) ||
                       (theOther.myMaxCorner[i] <          myMinCorner[i]);
        }
        return !anIsOut;
    }

    //! Returns true if at least one coordinate is infinite.
    __CADEX_EXPORT bool IsInfinite() const;

    __CADEX_EXPORT void Multiply (double theValue);

    ModelData_Box Multiplied (double theValue) const
    {
        auto r = *this;
        r.Multiply (theValue);
        return r;
    }

    //! Applies transformation.
    __CADEX_EXPORT void Transform (const ModelData_Transformation& theTransformation);

    ModelData_Box Transformed (const ModelData_Transformation& theTransformation) const
    {
        ModelData_Box r = *this;
        r.Transform (theTransformation);
        return r;
    }

    //! Casts to a Bnd_Box object.
    __CADEX_EXPORT operator Bnd_Box() const;

private:

    //own implementation of std::abs() to avoid including <cmath> into public header
    static double abs (double v) { return v >= 0.? v : -v; }
};

//! Multiplication operator.
__CADEX_EXPORT ModelData_Box operator * (const ModelData_Box& theV, double theVal);

//! Division operator.
__CADEX_EXPORT ModelData_Box operator / (const ModelData_Box& theV, double theVal);

//! Multiplication operator.
__CADEX_EXPORT void operator *= (ModelData_Box& theV, double theVal);

//! Division operator.
__CADEX_EXPORT void operator /= (ModelData_Box& theV, double theVal);

}

#endif

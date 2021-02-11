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


#ifndef _ModelData_Box2d_HeaderFile
#define _ModelData_Box2d_HeaderFile

#include <cadex/ModelData_Point2d.hxx>
#include <float.h>

class Bnd_Box2d;

namespace cadex {

class ModelData_Box2d
{
public:

    //! Constructor.
    /*! Creates a box with infinite boundaries.*/
    ModelData_Box2d() : myMinCorner (-DBL_MAX, -DBL_MAX), myMaxCorner (DBL_MAX, DBL_MAX) {}

    //! Constructor.
    /*! Creates a box with specified corners.*/
    __CADEX_EXPORT ModelData_Box2d (const ModelData_Point2dd& theCorner1, const ModelData_Point2dd& theCorner2);

    //! Constructor.
    __CADEX_EXPORT ModelData_Box2d (const Bnd_Box2d& theBox);

    __CADEX_DEFINE_PROPERTY(ModelData_Point2d, MinCorner)
    __CADEX_DEFINE_PROPERTY(ModelData_Point2d, MaxCorner)

    //! Returns a center point.
    /*! Returns a middle of the diagonal between MinCorner() and MaxCorner().*/
    ModelData_Point2d Center() const
    {
        return (myMinCorner + myMaxCorner) / 2.;
    }

    //! Adds a point into the bounding box.
    __CADEX_EXPORT void Add (const ModelData_Point2d& thePoint);

    //! Accumulates another bounding box.
    __CADEX_EXPORT void Add (const ModelData_Box2d& theBox);

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

    void SetRange (size_t theIdx, double theMin, double theMax)
    {
        myMinCorner[theIdx] = theMin;
        myMaxCorner[theIdx] = theMax;
    }

    double Range (size_t theIdx) const { return abs (myMaxCorner[theIdx] - myMinCorner[theIdx]); }

    double XRange() const { return Range (0); }

    double YRange() const { return Range (1); }

    void Enlarge (double theX, double theY)
    {
        myMinCorner.X() -= theX / 2.;
        myMaxCorner.X() += theX / 2.;
        myMinCorner.Y() -= theY / 2.;
        myMaxCorner.Y() += theY / 2.;
    }

    void Enlarge (double theSize)
    {
        Enlarge (theSize, theSize);
    }

    ModelData_Box2d Enlarged (double theX, double theY) const
    {
        auto r = *this;
        r.Enlarge (theX, theY);
        return r;
    }

    ModelData_Box2d Enlarged (double theSize) const
    {
        auto r = *this;
        r.Enlarge (theSize);
        return r;
    }

    //! Returns true if the point lies inside the box.
    bool IsIn (const ModelData_Point2d& thePoint) const
    {
        return thePoint.X() >= myMinCorner.X() && thePoint.X() <= myMaxCorner.X() &&
               thePoint.Y() >= myMinCorner.Y() && thePoint.Y() <= myMaxCorner.Y();
    }

    //! Returns the other box has at least one common point with this box.
    bool Intersects (const ModelData_Box2d& theOther) const
    {
        bool anIsOut = false;
        for (size_t i = 0; i < 2; ++i) {
            anIsOut |= (         myMaxCorner[i] < theOther.myMinCorner[i]) ||
                       (theOther.myMaxCorner[i] <          myMinCorner[i]);
        }
        return !anIsOut;
    }

    //! Returns true if at least one coordinate is infinite.
    __CADEX_EXPORT bool IsInfinite() const;

    __CADEX_EXPORT void Multiply (double theValue);

    ModelData_Box2d Multiplied (double theValue) const
    {
        auto r = *this;
        r.Multiply (theValue);
        return r;
    }

    //! Applies transformation.
    __CADEX_EXPORT void Transform (const ModelData_Transformation2d& theTransformation);

    ModelData_Box2d Transformed (const ModelData_Transformation2d& theTransformation) const
    {
        ModelData_Box2d r = *this;
        r.Transform (theTransformation);
        return r;
    }

    //! Casts to a Bnd_Box object.
    __CADEX_EXPORT operator Bnd_Box2d() const;

private:

    //own implementation of std::abs() to avoid including <cmath> into public header
    static double abs (double v) { return v >= 0.? v : -v; }
};

//! Multiplication operator.
__CADEX_EXPORT ModelData_Box2d operator * (const ModelData_Box2d& theV, double theVal);

//! Division operator.
__CADEX_EXPORT ModelData_Box2d operator / (const ModelData_Box2d& theV, double theVal);

//! Multiplication operator.
__CADEX_EXPORT void operator *= (ModelData_Box2d& theV, double theVal);

//! Division operator.
__CADEX_EXPORT void operator /= (ModelData_Box2d& theV, double theVal);

}

#endif

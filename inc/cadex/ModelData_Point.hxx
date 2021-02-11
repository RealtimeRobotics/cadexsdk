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


#ifndef _ModelData_Point_HeaderFile
#define _ModelData_Point_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cadex/ModelData_XYZ.hxx>

class gp_Pnt;

namespace cadex {

class ModelData_Axis1Placement;
class ModelData_Axis2Placement;
class ModelData_Transformation;

namespace internal {

template<typename T>
class ModelData_BaseVector;

template<typename T>
struct ModelData_PointTraits
{
    typedef typename ModelData_XYZTraits<T>::ValueType   ValueType;
    static ValueType CoincidenceTolerance()
    {
        return ModelData_XYZTraits<T>::CoincidenceTolerance();
    }
};

/*! \class ModelData_BasePoint
*/
template<typename T>
class ModelData_BasePoint
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Defines a type of the Point component.
    typedef T    ValueType;

    //! Defines a type of the vector component.
    typedef ValueType                                       value_type;

    //! Defines a type of the point component traits.
    typedef ModelData_PointTraits<T>                        TraitsType;

    //! Constructor.
    ModelData_BasePoint() {}

    //! Constructor.
    /*! Creates a Point with equal components.*/
    ModelData_BasePoint (ValueType theV) : myCoord (theV) {}

    //! Constructor.
    ModelData_BasePoint (ValueType theX, ValueType theY, ValueType theZ) :
        myCoord (theX, theY, theZ) {}

    //! Constructor.
    ModelData_BasePoint (const ModelData_BaseXYZ<T>& theXYZ) : myCoord (theXYZ) {}

    //! Constructor.
    ModelData_BasePoint (const ModelData_BasePoint& theOther) : myCoord (theOther.myCoord) {}

    ValueType operator[] (size_t i) const { return myCoord[i]; }
    ValueType& operator[] (size_t i) { return myCoord[i]; }

    ValueType X() const { return myCoord[0]; }
    ValueType& X() { return myCoord[0]; }

    ValueType Y() const { return myCoord[1]; }
    ValueType& Y() { return myCoord[1]; }

    ValueType Z() const { return myCoord[2]; }
    ValueType& Z() { return myCoord[2]; }

    //! Sets coordinates.
    /*! \sa Coord().*/
    void SetCoord (ValueType theX, ValueType theY, ValueType theZ)
    {
        Coord().SetCoord (theX, theY, theZ);
    }

    //! Returns coordinates.
    /*! Populates arguments with values of X(), Y() and Z().
        \sa SetCoord().
    */
    void Coord (ValueType& theX, ValueType& theY, ValueType& theZ) const
    {
        Coord().Coord (theX, theY, theZ);
    }

    //! Compares if two points are coincident within a tolerance.
    /*! Uses ModelData_BaseXYZ::IsEqual().
    */
    bool IsEqual (const ModelData_BasePoint& theOther, ValueType theTolerance) const
    {
        return myCoord.IsEqual (theOther.Coord(), theTolerance);
    }

    //! Returns square distance between \a this and \a theOther point.
    /*! Distance() uses sqrt() what may incur performance penalty so favor using SquareDistance() in
        performance-sensitive algorithms.
    */
    ValueType Distance (const ModelData_BasePoint& theOther) const
    {
        return sqrt (SquareDistance (theOther));
    }

    //! Returns square distance between \a this and \a theOther point.
    /*! \sa Distance().*/
    ValueType SquareDistance (const ModelData_BasePoint& theOther) const
    {
        ValueType r = ValueType();
        for (int i = 0; i < 3; ++i) {
            auto d = theOther[i] - myCoord[i];
            r += d * d;
        }
        return r;
    }

    //! Transforms the point with a transformation matrix.
    void Transform (const ModelData_Transformation& theTransformation);

    //! Returns a point which is transformed with a transformation matrix.
    /*! \sa Transform().*/
    ModelData_BasePoint Transformed (const ModelData_Transformation& theTransformation) const
    {
        ModelData_BasePoint r = *this;
        r.Transform (theTransformation);
        return r;
    }

    void Mirror (const ModelData_BasePoint& theAxis);

    void Mirror (const ModelData_Axis1Placement& theAxis);

    void Mirror (const ModelData_Axis2Placement& theAxis);

    template<typename U>
    ModelData_BasePoint Mirrored (const U& theRef) const
    {
        ModelData_BasePoint r = *this;
        r.Mirror (theRef);
        return r;
    }

    void Rotate (const ModelData_Axis1Placement& theAxis, double theAngle);

    ModelData_BasePoint Rotated (const ModelData_Axis1Placement& theAxis, double theAngle)
    {
        ModelData_BasePoint r = *this;
        r.Rotate (theAxis, theAngle);
        return r;
    }

    void Translate (const ModelData_BaseVector<ValueType>& theVector);

    ModelData_BasePoint Translated (const ModelData_BaseVector<ValueType>& theVector)
    {
        ModelData_BasePoint r = *this;
        r.Translate (theVector);
        return r;
    }

    __CADEX_EXPORT void Scale (const ModelData_BasePoint& thePoint, double theScale);

    ModelData_BasePoint Scaled (const ModelData_BasePoint& thePoint, double theScale)
    {
        auto r = *this;
        r.Scale (thePoint, theScale);
        return r;
    }

    void operator -= (const ModelData_BasePoint<T>& theOther)
    {
        myCoord -= theOther.Coord ();
    }

    void operator += (const ModelData_BasePoint<T>& theOther)
    {
        myCoord += theOther.Coord ();
    }

    __CADEX_DEFINE_PROPERTY(ModelData_BaseXYZ<T>, Coord)
};

//! Equality operator
/*! Returns true if two points are equal with default distance tolerance.

    \sa ModelData_Point::IsEqual().
*/
template<typename T>
inline bool operator == (const ModelData_BasePoint<T>& theV1,
                         const ModelData_BasePoint<T>& theV2)
{
    return theV1.IsEqual (theV2, ModelData_BasePoint<T>::TraitsType::CoincidenceTolerance());
}

//! Non-equality operator.
/*! Returns !operator==().
*/
template<typename T>
inline bool operator != (const ModelData_BasePoint<T>& theV1,
                         const ModelData_BasePoint<T>& theV2)
{
    return !(theV1 == theV2);
}

//! Operator +.
/*! Returns a point equal to point \a theV1 plus \a theV2.
*/
template<typename T>
inline ModelData_BasePoint<T> operator + (const ModelData_BasePoint<T>& theV1,
                                         const ModelData_BasePoint<T>& theV2)
{
    ModelData_BasePoint<T> r = theV1.Coord() + theV2.Coord();
    return r;
}

//! Operator -.
/*! Returns a point equal to point \a theV1 minus \a theV2.
*/
template<typename T>
inline ModelData_BasePoint<T> operator - (const ModelData_BasePoint<T>& theV1,
                                         const ModelData_BasePoint<T>& theV2)
{
    ModelData_BasePoint<T> r = theV1.Coord() - theV2.Coord();
    return r;
}

template<typename T>
inline ModelData_BasePoint<T> operator * (const ModelData_BasePoint<T>& theV,
                                         typename ModelData_BasePoint<T>::ValueType theVal)
{
    ModelData_BasePoint<T> r = theV.Coord() * theVal;
    return r;
}

template<typename T>
inline void operator *= (ModelData_BasePoint<T>& theV,
                         typename ModelData_BasePoint<T>::ValueType theVal)
{
    theV.Coord() *= theVal;
}

template<typename T>
inline ModelData_BasePoint<T> operator / (const ModelData_BasePoint<T>& theV,
                                         typename ModelData_BasePoint<T>::ValueType theVal)
{
    ModelData_BasePoint<T> r = theV.Coord() / theVal;
    return r;
}

template<typename T>
inline void operator /= (ModelData_BasePoint<T>& theV,
                         typename ModelData_BasePoint<T>::ValueType theVal)
{
    theV.Coord() /= theVal;
}

}

typedef cadex::internal::ModelData_BasePoint<double>   ModelData_Pointd;

typedef cadex::internal::ModelData_BasePoint<float>    ModelData_Pointf;


#ifdef SWIG
%template (ModelData_Pointd) cadex::internal::ModelData_BasePoint<double>;
%template (ModelData_Pointf) cadex::internal::ModelData_BasePoint<float>;
#endif


class ModelData_Point : public ModelData_Pointd
{
public:
    ModelData_Point() {}

    //! Constructor.
    ModelData_Point (const ModelData_XYZ& theOther) :
        ModelData_Pointd (theOther) {}

    //! Constructor.
    ModelData_Point (const internal::ModelData_BaseXYZ<ModelData_Pointd::ValueType>& theOther) :
        ModelData_Pointd (theOther) {}

    //! Constructor.
    ModelData_Point (const ModelData_Pointd& theOther) :
        ModelData_Pointd (theOther) {}

    //! Constructor.
    ModelData_Point (double theX, double theY, double theZ) :
        ModelData_Pointd (theX, theY, theZ) {}

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_Point, gp_Pnt)

    __CADEX_EXPORT static const ModelData_Point& Origin();

    __CADEX_EXPORT void Transform (const ModelData_Transformation& theTransformation);

    ModelData_Point Transformed (const ModelData_Transformation& theTransformation) const
    {
        ModelData_Point r = *this;
        r.Transform (theTransformation);
        return r;
    }
};

}

#endif

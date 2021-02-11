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


#ifndef _ModelData_Vector2d_HeaderFile
#define _ModelData_Vector2d_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelData_Point2d.hxx>

class gp_Vec2d;

namespace cadex {

class ModelData_Transformation2d;

namespace internal {

template<typename T>
struct ModelData_VectorTraits2d;

template<>
struct ModelData_VectorTraits2d<double>
{
    typedef double  ValueType;
    static ValueType AngularTolerance()     { return 1e-12; }
    static ValueType CoincidenceTolerance()
    {
        return ModelData_XYTraits<double>::CoincidenceTolerance();
    }
};

template<>
struct ModelData_VectorTraits2d<float>
{
    typedef float   ValueType;
    static ValueType AngularTolerance()     { return 1e-12f; }
    static ValueType CoincidenceTolerance()
    {
        return ModelData_XYTraits<float>::CoincidenceTolerance();
    }
};

/*! \class ModelData_BaseVector2d
*/
template<typename T>
class ModelData_BaseVector2d
{
public:

    //! Defines a type of the vector component.
    typedef T    ValueType;

    //! Defines a type of the vector component traits.
    typedef ModelData_VectorTraits2d<T>                        TraitsType;

    //! Constructor.
    ModelData_BaseVector2d() {}

    //! Constructor.
    /*! Creates a vector with equal components.*/
    ModelData_BaseVector2d (ValueType theV) : myCoord (theV) {}

    //! Constructor.
    ModelData_BaseVector2d (ValueType theX, ValueType theY) :
        myCoord (theX, theY) {}

    //! Constructor.
    template<typename Y>
    ModelData_BaseVector2d (const ModelData_BaseXY<Y>& theXYZ) :
        myCoord (theXYZ.X(), theXYZ.Y()) {}

    //! Constructor.
    template<typename Y>
    ModelData_BaseVector2d (const ModelData_BaseVector2d<Y>& theOther) :
        myCoord (theOther.X(), theOther.Y()) {}

    //! Constructor.
    ModelData_BaseVector2d (const ModelData_BasePoint2d<T>& theStart, const ModelData_BasePoint2d<T>& theEnd) :
        myCoord (theEnd.Coord() - theStart.Coord()) {}

    ValueType operator[] (size_t i) const { return myCoord[i]; }
    ValueType& operator[] (size_t i) { return myCoord[i]; }

    ValueType X() const { return myCoord[0]; }
    ValueType& X() { return myCoord[0]; }

    ValueType Y() const { return myCoord[1]; }
    ValueType& Y() { return myCoord[1]; }

    //! Returns a square modulus.
    /*! \sa Modulus().*/
    ValueType SquareModulus() const
    {
        return myCoord.SquareModulus();
    }

    //! Returns a modulus.
    /*! \sa SquareModulus().*/
    ValueType Modulus() const
    {
        return myCoord.Modulus();
    }

    bool IsParallel (const ModelData_BaseVector2d<T>& theOther, ValueType theTolerance) const
    {
        ValueType aModulus1 = Modulus();
        ValueType aModulus2 = theOther.Modulus();
        ModelData_BaseVector2d<T> aV1 (*this / aModulus1);
        ModelData_BaseVector2d<T> aV2 (theOther / aModulus2);
        ValueType d = aV1 * aV2;
        return (1. - fabs (d)) <= theTolerance;
    }

    //! Compares if two vectors are equal within a distance tolerance.
    /*! Uses ModelData_BaseXY::IsEqual().
    */
    bool IsEqual (const ModelData_BaseVector2d<T>& theOther, ValueType theTolerance) const
    {
        return myCoord.IsEqual (theOther.Coord(), theTolerance);
    }

    __CADEX_DEFINE_PROPERTY(ModelData_BaseXY<T>, Coord)
};

//! Equality operator
/*! Returns true if two vectors are equal with default distance tolerance.

    \sa ModelData_Vector2d::IsEqual().
*/
template<typename T>
inline bool operator == (const ModelData_BaseVector2d<T>& theV1,
                         const ModelData_BaseVector2d<T>& theV2)
{
    return theV1.IsEqual (theV2, ModelData_BaseVector2d<T>::TraitsType::CoincidenceTolerance());
}

//! Non-equality operator.
/*! Returns !operator==().
*/
template<typename T>
inline bool operator != (const ModelData_BaseVector2d<T>& theV1,
                         const ModelData_BaseVector2d<T>& theV2)
{
    return !(theV1 == theV2);
}

//! Operator +.
/*! Returns a vector equal to vector \a theV1 plus \a theV2.
*/
template<typename T>
inline ModelData_BaseVector2d<T> operator + (const ModelData_BaseVector2d<T>& theV1,
                                            const ModelData_BaseVector2d<T>& theV2)
{
    ModelData_BaseVector2d<T> r = theV1.Coord() + theV2.Coord();
    return r;
}

//! Operator -.
/*! Returns a vector equal to vector \a theV1 minus \a theV2.
*/
template<typename T>
inline ModelData_BaseVector2d<T> operator - (const ModelData_BaseVector2d<T>& theV1,
                                            const ModelData_BaseVector2d<T>& theV2)
{
    ModelData_BaseVector2d<T> r = theV1.Coord() - theV2.Coord();
    return r;
}

template<typename T>
inline typename ModelData_BaseVector2d<T>::ValueType operator ^ (
    const ModelData_BaseVector2d<T>& theV1,
    const ModelData_BaseVector2d<T>& theV2)
{
    typename ModelData_BaseVector2d<T>::ValueType r = theV1.Coord() ^ theV2.Coord();
    return r;
}

template<typename T>
inline ModelData_BaseVector2d<T> operator * (const ModelData_BaseVector2d<T>& theV,
                                            typename ModelData_BaseVector2d<T>::ValueType theVal)
{
    ModelData_BaseVector2d<T> r = theV.Coord() * theVal;
    return r;
}

template<typename T>
inline void operator *= (ModelData_BaseVector2d<T>& theV,
                         typename ModelData_BaseVector2d<T>::ValueType theVal)
{
    theV.Coord() *= theVal;
}

//! Returns a dot-product.
template<typename T>
inline typename ModelData_BaseVector2d<T>::ValueType operator * (
    const ModelData_BaseVector2d<T>& theV1,
    const ModelData_BaseVector2d<T>& theV2)
{
    return theV1.Coord() * theV2.Coord();
}

template<typename T>
inline ModelData_BaseVector2d<T> operator / (const ModelData_BaseVector2d<T>& theV,
                                            typename ModelData_BaseVector2d<T>::ValueType theVal)
{
    ModelData_BaseVector2d<T> r = theV.Coord() / theVal;
    return r;
}

template<typename T>
inline void operator /= (ModelData_BaseVector2d<T>& theV,
                         typename ModelData_BaseVector2d<T>::ValueType theVal)
{
    theV.Coord() /= theVal;
}

}

typedef cadex::internal::ModelData_BaseVector2d<double>   ModelData_Vectord2d;
typedef cadex::internal::ModelData_BaseVector2d<float>    ModelData_Vectorf2d;

typedef cadex::internal::ModelData_BasePoint2d<double>    ModelData_Point2dd;

#ifdef SWIG
    %template (ModelData_Vectord2d) cadex::internal::ModelData_BaseVector2d<double>;
    %template (ModelData_Vectorf2d) cadex::internal::ModelData_BaseVector2d<float>;
#endif

class ModelData_Vector2d : public ModelData_Vectord2d
{
public:
    ModelData_Vector2d() {}

    //! Constructor.
    ModelData_Vector2d (const ModelData_Vector2d& theOther) :
        ModelData_Vectord2d (theOther.X(), theOther.Y()) {}

    //! Constructor.
    ModelData_Vector2d (double theX, double theY) :
        ModelData_Vectord2d (theX, theY) {}

    //! Constructor.
    template<typename T>
    ModelData_Vector2d (const internal::ModelData_BaseVector2d<T>& theOther) :
        ModelData_Vectord2d (theOther.X(), theOther.Y()) {}

    //! Constructor.
    template<typename T>
    ModelData_Vector2d (const internal::ModelData_BaseXY<T>& theOther) :
        ModelData_Vectord2d (theOther.X(), theOther.Y()) {}

    //! Constructor.
    ModelData_Vector2d (const ModelData_Point2dd& theStart, const ModelData_Point2dd& theEnd) :
        ModelData_Vectord2d (theStart, theEnd) {}

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_Vector2d, gp_Vec2d)

    __CADEX_EXPORT void Transform (const ModelData_Transformation2d& theTransformation);

    ModelData_Vector2d Transformed (const ModelData_Transformation2d& theTransformation) const
    {
        ModelData_Vector2d r = *this;
        r.Transform (theTransformation);
        return r;
    }
};

}

#endif

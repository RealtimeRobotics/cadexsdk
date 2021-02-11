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


#ifndef _ModelData_Vector_HeaderFile
#define _ModelData_Vector_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/ModelData_Point.hxx>

class gp_Vec;

namespace cadex {

class ModelData_Axis1Placement;
class ModelData_Axis2Placement;
class ModelData_Transformation;

namespace internal {

template<typename T>
struct ModelData_VectorTraits;

template<>
struct ModelData_VectorTraits<double>
{
    typedef double  ValueType;
    static ValueType AngularTolerance()     { return 1e-12; }
    static ValueType CoincidenceTolerance()
    {
        return ModelData_XYZTraits<double>::CoincidenceTolerance();
    }
};

template<>
struct ModelData_VectorTraits<float>
{
    typedef float   ValueType;
    static ValueType AngularTolerance()     { return 1e-12f; }
    static ValueType CoincidenceTolerance()
    {
        return ModelData_XYZTraits<float>::CoincidenceTolerance();
    }
};

/*! \class ModelData_BaseVector
*/
template<typename T>
class ModelData_BaseVector
{
public:

    //! Defines a type of the vector component.
    typedef T    ValueType;

    //! Defines a type of the vector component.
    typedef ValueType                                      value_type;

    //! Defines a type of the vector component traits.
    typedef ModelData_VectorTraits<T>                        TraitsType;

    //! Constructor.
    ModelData_BaseVector() {}

    //! Constructor.
    /*! Creates a vector with equal components.*/
    ModelData_BaseVector (ValueType theV) : myCoord (theV) {}

    //! Constructor.
    ModelData_BaseVector (ValueType theX, ValueType theY, ValueType theZ) :
        myCoord (theX, theY, theZ) {}

    //! Constructor.
    template<typename Y>
    ModelData_BaseVector (const ModelData_BaseXYZ<Y>& theXYZ) :
        myCoord (theXYZ.X(), theXYZ.Y(), theXYZ.Z()) {}

    //! Constructor.
    template<typename Y>
    ModelData_BaseVector (const ModelData_BaseVector<Y>& theOther) :
        myCoord (theOther.X(), theOther.Y(), theOther.Z()) {}

    //! Constructor.
    ModelData_BaseVector (const ModelData_BasePoint<T>& theStart, const ModelData_BasePoint<T>& theEnd) :
        myCoord (theEnd.Coord() - theStart.Coord()) {}

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

    //! Normalizes the vector.
    /*! Invokes ModelData_XYZ::Normalize().*/
    void Normalize()
    {
        myCoord.Normalize();
    }
  
    //! Returns a vector which is a normalized vector of \a this.
    ModelData_BaseVector Normalized() const
    {
        ModelData_BaseVector r = *this;
        r.Normalize();
        return r;
    }

    bool IsParallel (const ModelData_BaseVector<T>& theOther, ValueType theTolerance) const
    {
        ValueType aModulus1 = Modulus();
        ValueType aModulus2 = theOther.Modulus();
        ModelData_BaseVector<T> aV1 (*this / aModulus1);
        ModelData_BaseVector<T> aV2 (theOther / aModulus2);
        ValueType d = aV1 * aV2;
        return (1. - fabs (d)) <= theTolerance;
    }

    //! Compares if two vectors are equal within a distance tolerance.
    /*! Uses ModelData_BaseXYZ::IsEqual().
    */
    bool IsEqual (const ModelData_BaseVector& theOther, ValueType theTolerance) const
    {
        return myCoord.IsEqual (theOther.Coord(), theTolerance);
    }

    //! Reverses the vector.
    /*! Multiplies all coordinates by (-1.).*/
    void Reverse()
    {
        myCoord.Reverse();
    }

    //! Returns a vector which is reversed of \a this.
    /*! Returns a vector with all coordinates multipled by (-1). 
        \sa Reverse().
    */
    ModelData_BaseVector Reversed() const
    {
        ModelData_BaseVector r = *this;
        r.Reverse();
        return r;
    }

    void Add (const ModelData_BaseVector& theOther)
    {
        myCoord.Add (theOther.myCoord);
    }

    ModelData_BaseVector Added (const ModelData_BaseVector& theOther) const
    {
        ModelData_BaseVector r = *this;
        r.Add (theOther);
        return r;
    }

    void Subtract (const ModelData_BaseVector& theOther)
    {
        myCoord.Subtract (theOther.myCoord);
    }

    ModelData_BaseVector Subtracted (const ModelData_BaseVector& theOther) const
    {
        ModelData_BaseVector r = *this;
        r.Subtract (theOther);
        return r;
    }

    void Multiply (ValueType theValue)
    {
        myCoord.Multiply (theValue);
    }

    ModelData_BaseVector Multiplied (ValueType theValue) const
    {
        ModelData_BaseVector r = *this;
        r.Multiply (theValue);
        return r;
    }

    void Divide (ValueType theValue)
    {
        myCoord.Divide (theValue);
    }

    ModelData_BaseVector Divided (ValueType theValue) const
    {
        ModelData_BaseVector r = *this;
        r.Divide (theValue);
        return r;
    }

    //! Returns a vector which is reversed of \a this.
    /*! Equivalent of Reversed().*/
    ModelData_BaseVector operator - () const
    {
        return Reversed();
    }

    ValueType Dot (const ModelData_BaseVector& theOther) const
    {
        return myCoord.Dot (theOther.myCoord);
    }

    void Cross (const ModelData_BaseVector& theOther)
    {
        myCoord.Cross (theOther.myCoord);
    }

    ModelData_BaseVector Crossed (const ModelData_BaseVector& theOther) const
    {
        return myCoord.Crossed (theOther.myCoord);
    }


    //! Transforms the vector with a transformation matrix.
    void Transform (const ModelData_Transformation& theTransformation);

    //! Returns a vector which is transformed with a transformation matrix.
    /*! \sa Transform().*/
    ModelData_BaseVector Transformed (const ModelData_Transformation& theTransformation) const
    {
        ModelData_BaseVector r = *this;
        r.Transform (theTransformation);
        return r;
    }

    void Mirror (const ModelData_BaseVector& theAxis);

    void Mirror (const ModelData_Axis1Placement& theAxis);

    void Mirror (const ModelData_Axis2Placement& theAxis);

    template<typename U>
    ModelData_BaseVector Mirrored (const U& theRef) const
    {
        ModelData_BaseVector r = *this;
        r.Mirror (theRef);
        return r;
    }

    void Rotate (const ModelData_Axis1Placement& theAxis, double theAngle);

    ModelData_BaseVector Rotated (const ModelData_Axis1Placement& theAxis, double theAngle)
    {
        ModelData_BaseVector r = *this;
        r.Rotate (theAxis, theAngle);
        return r;
    }

    __CADEX_DEFINE_PROPERTY(ModelData_BaseXYZ<T>, Coord)
};

//! Equality operator
/*! Returns true if two vectors are equal with default distance and angular tolerances.

    \sa ModelData_Vector3d::IsEqual().
*/
template<typename T>
inline bool operator == (const ModelData_BaseVector<T>& theV1,
                         const ModelData_BaseVector<T>& theV2)
{
    return theV1.IsEqual (theV2, ModelData_BaseVector<T>::TraitsType::CoincidenceTolerance());
}

//! Non-equality operator.
/*! Returns !operator==().
*/
template<typename T>
inline bool operator != (const ModelData_BaseVector<T>& theV1,
                         const ModelData_BaseVector<T>& theV2)
{
    return !(theV1 == theV2);
}

//! Operator +.
/*! Returns a vector equal to vector \a theV1 plus \a theV2.
*/
template<typename T>
inline ModelData_BaseVector<T> operator + (const ModelData_BaseVector<T>& theV1,
                                          const ModelData_BaseVector<T>& theV2)
{
    ModelData_BaseVector<T> r = theV1.Coord() + theV2.Coord();
    return r;
}

//! Operator +=.
/*! Adds the vector \a theV2 to \a theV1.
*/
template<typename T>
inline void operator += (ModelData_BaseVector<T>& theV1,
                         const ModelData_BaseVector<T>& theV2)
{
    theV1.Coord() += theV2.Coord();
}

//! Operator -.
/*! Returns a vector equal to vector \a theV1 minus \a theV2.
*/
template<typename T>
inline ModelData_BaseVector<T> operator - (const ModelData_BaseVector<T>& theV1,
                                          const ModelData_BaseVector<T>& theV2)
{
    ModelData_BaseVector<T> r = theV1.Coord() - theV2.Coord();
    return r;
}

//! Operator -=.
/*! Subtracts the vector \a theV2 from \a theV1.
*/
template<typename T>
inline void operator -= (ModelData_BaseVector<T>& theV1,
                         const ModelData_BaseVector<T>& theV2)
{
    theV1.Coord() -= theV2.Coord();
}

template<typename T>
inline ModelData_BaseVector<T> operator ^ (const ModelData_BaseVector<T>& theV1,
                                          const ModelData_BaseVector<T>& theV2)
{
    ModelData_BaseVector<T> r = theV1.Coord() ^ theV2.Coord();
    return r;
}

template<typename T>
inline void operator ^= (ModelData_BaseVector<T>& theV1,
                         const ModelData_BaseVector<T>& theV2)
{
    theV1.Coord() ^= theV2.Coord();
}

template<typename T>
inline ModelData_BaseVector<T> operator * (const ModelData_BaseVector<T>& theV,
                                          typename ModelData_BaseVector<T>::ValueType theVal)
{
    ModelData_BaseVector<T> r = theV.Coord() * theVal;
    return r;
}

template<typename T>
inline ModelData_BaseVector<T> operator * (typename ModelData_BaseVector<T>::ValueType theVal,
                                           const ModelData_BaseVector<T>& theV)
{
    ModelData_BaseVector<T> r = theVal * theV.Coord();
    return r;
}

template<typename T>
inline void operator *= (ModelData_BaseVector<T>& theV,
                         typename ModelData_BaseVector<T>::ValueType theVal)
{
    theV.Coord() *= theVal;
}

//! Returns a dot-product.
template<typename T>
inline typename ModelData_BaseVector<T>::ValueType operator * (
    const ModelData_BaseVector<T>& theV1,
    const ModelData_BaseVector<T>& theV2)
{
    return theV1.Coord() * theV2.Coord();
}

template<typename T>
inline ModelData_BaseVector<T> operator / (const ModelData_BaseVector<T>& theV,
                                          typename ModelData_BaseVector<T>::ValueType theVal)
{
    ModelData_BaseVector<T> r = theV.Coord() / theVal;
    return r;
}

template<typename T>
inline void operator /= (ModelData_BaseVector<T>& theV,
                         typename ModelData_BaseVector<T>::ValueType theVal)
{
    theV.Coord() /= theVal;
}

}

typedef cadex::internal::ModelData_BaseVector<double>   ModelData_Vectord;
typedef cadex::internal::ModelData_BaseVector<float>    ModelData_Vectorf;

typedef cadex::internal::ModelData_BasePoint<double>    ModelData_Pointd;

#ifdef SWIG
%template (ModelData_Vectord) cadex::internal::ModelData_BaseVector<double>;
%template (ModelData_Vectorf) cadex::internal::ModelData_BaseVector<float>;
#endif

class ModelData_Vector : public ModelData_Vectord
{
public:
    ModelData_Vector() {}

    //! Constructor.
    ModelData_Vector (const ModelData_Vector& theOther) :
        ModelData_Vectord (theOther.X(), theOther.Y(), theOther.Z()) {}

    //! Constructor.
    ModelData_Vector (double theX, double theY, double theZ) :
        ModelData_Vectord (theX, theY, theZ) {}

    //! Constructor.
    template<typename T>
    ModelData_Vector (const internal::ModelData_BaseVector<T>& theOther) :
        ModelData_Vectord (theOther.X(), theOther.Y(), theOther.Z()) {}

    //! Constructor.
    template<typename T>
    ModelData_Vector (const internal::ModelData_BaseXYZ<T>& theOther) :
        ModelData_Vectord (theOther.X(), theOther.Y(), theOther.Z()) {}

    //! Constructor.
    ModelData_Vector (const ModelData_Pointd& theStart, const ModelData_Pointd& theEnd) :
        ModelData_Vectord (theStart, theEnd) {}

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_Vector, gp_Vec)

    __CADEX_EXPORT void Transform (const ModelData_Transformation& theTransformation);

    ModelData_Vector Transformed (const ModelData_Transformation& theTransformation) const
    {
        ModelData_Vector r = *this;
        r.Transform (theTransformation);
        return r;
    }
};

}

#endif

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


#ifndef _ModelData_XYZ_HeaderFile
#define _ModelData_XYZ_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cmath>

class gp_XYZ;

namespace cadex {

namespace internal {

template<typename T>
struct ModelData_XYZTraits;

template<>
struct ModelData_XYZTraits<double>
{
    typedef double  ValueType;
    static ValueType CoincidenceTolerance() { return 1e-7; }
    __CADEX_EXPORT static ValueType Zero();
};

template<>
struct ModelData_XYZTraits<float>
{
    typedef float   ValueType;
    static ValueType CoincidenceTolerance() { return 1e-7f; }
    __CADEX_EXPORT static ValueType Zero();
};

/*! \class ModelData_XYZ
*/
template<typename T>
class ModelData_BaseXYZ
{
public:

    //! Defines a type of the vector component.
    typedef T   ValueType;

    //! Defines a type of the vector component traits.
    typedef ModelData_XYZTraits<T>                       TraitsType;

    //! Constructor.
    ModelData_BaseXYZ()
    {
        const ValueType v = ValueType();
        for (size_t i = 0; i < 3; ++i)
            myBuf[i] = v;
    }

    //! Constructor.
    /*! Creates a vector with equal components.*/
    ModelData_BaseXYZ (ValueType theV)
    { SetCoord (theV, theV, theV); }

    //! Constructor.
    ModelData_BaseXYZ (ValueType theX, ValueType theY, ValueType theZ)
    { SetCoord (theX, theY, theZ); }

    //! Compares if two points are coincident within a tolerance.
    /*! Returns true if distance between \a this and \a theOther object is not greater
        than specified tolerance.
        Expecting that most points are not equal to each other, first checks individual
        components and returns false faster in this case.
    */
    bool IsEqual (const ModelData_BaseXYZ& theOther, ValueType theTolerance) const
    {
        const ValueType d2 = theTolerance * theTolerance;
        ValueType dX2 = (X() - theOther.X()) * (X() - theOther.X());
        if (dX2 > d2)
            return false;
        ValueType dY2 = (Y() - theOther.Y()) * (Y() - theOther.Y());
        if (dY2 > d2)
            return false;
        ValueType dZ2 = (Z() - theOther.Z()) * (Z() - theOther.Z());
        if (dZ2 > d2)
            return false;
        return dX2 + dY2 + dZ2 <= d2;
    }

    //! Sets coordinates.
    /*! \sa Coord().*/
    void SetCoord (ValueType theX, ValueType theY, ValueType theZ)
    {
        X() = theX;
        Y() = theY;
        Z() = theZ;
    }

    //! Returns coordinates.
    /*! Populates arguments with values of X(), Y() and Z().
        \sa SetCoord().
    */
    void Coord (ValueType& theX, ValueType& theY, ValueType& theZ) const
    {
        theX = X();
        theY = Y();
        theZ = Z();
    }

    ValueType operator[] (size_t i) const { return myBuf[i]; }
    ValueType& operator[] (size_t i) { return myBuf[i]; }

    ValueType X() const { return myBuf[0]; }
    ValueType& X() { return myBuf[0]; }

    ValueType Y() const { return myBuf[1]; }
    ValueType& Y() { return myBuf[1]; }

    ValueType Z() const { return myBuf[2]; }
    ValueType& Z() { return myBuf[2]; }

    //! Returns a square modulus.
    /*! \sa Modulus().*/
    ValueType SquareModulus() const
    {
        return X() * X() + Y() * Y() + Z() * Z();
    }

    //! Returns a modulus.
    /*! \sa SquareModulus().*/
    ValueType Modulus() const
    {
        return std::sqrt (SquareModulus());
    }

    void Normalize()
    {
        auto m = Modulus();
        if (m > TraitsType::Zero()) {
            X() /= m;
            Y() /= m;
            Z() /= m;
        }
    }

    ModelData_BaseXYZ Normalized() const
    {
        ModelData_BaseXYZ r = *this;
        r.Normalize();
        return r;
    }

    //! Reverses the object.
    /*! Multiplies all coordinates by (-1.).*/
    void Reverse()
    {
        X() = -X();
        Y() = -Y();
        Z() = -Z();
    }

    //! Returns an object which is reversed of \a this.
    /*! Returns an object with all coordinates multipled by (-1). 
        \sa Reverse().
    */
    ModelData_BaseXYZ Reversed() const
    {
        ModelData_BaseXYZ r = *this;
        r.Reverse();
        return r;
    }

    void Add (const ModelData_BaseXYZ& theOther)
    {
        for (size_t i = 0; i < 3; ++i)
            myBuf[i] += theOther.myBuf[i];
    }

    ModelData_BaseXYZ Added (const ModelData_BaseXYZ& theOther) const
    {
        ModelData_BaseXYZ r = *this;
        r.Add (theOther);
        return r;
    }

    void Subtract (const ModelData_BaseXYZ& theOther)
    {
        for (size_t i = 0; i < 3; ++i)
            myBuf[i] -= theOther.myBuf[i];
    }

    ModelData_BaseXYZ Subtracted (const ModelData_BaseXYZ& theOther) const
    {
        ModelData_BaseXYZ r = *this;
        r.Subtract (theOther);
        return r;
    }

    void Multiply (ValueType theValue)
    {
        for (size_t i = 0; i < 3; ++i)
            myBuf[i] *= theValue;
    }

    ModelData_BaseXYZ Multiplied (ValueType theValue) const
    {
        ModelData_BaseXYZ r = *this;
        r.Multiply (theValue);
        return r;
    }

    void Divide (ValueType theValue)
    {
        for (size_t i = 0; i < 3; ++i)
            myBuf[i] /= theValue;
    }

    ModelData_BaseXYZ Divided (ValueType theValue) const
    {
        ModelData_BaseXYZ r = *this;
        r.Divide (theValue);
        return r;
    }

    //! Returns an object which is reversed of \a this.
    /*! Equivalent of Reversed().*/
    ModelData_BaseXYZ operator - () const
    {
        return Reversed();
    }

    ValueType Dot (const ModelData_BaseXYZ& theOther) const
    {
        ValueType r = 0;
        for (size_t i = 0; i < 3; ++i)
            r += myBuf[i] * theOther.myBuf[i];
        return r;
    }

    void Cross (const ModelData_BaseXYZ& theOther)
    {
        ValueType aX = Y() * theOther.Z() - Z() * theOther.Y();
        ValueType aY = Z() * theOther.X() - X() * theOther.Z();
        ValueType aZ = X() * theOther.Y() - Y() * theOther.X();
        SetCoord (aX, aY, aZ);
    }

    ModelData_BaseXYZ Crossed (const ModelData_BaseXYZ& theOther) const
    {
        ModelData_BaseXYZ r = *this;
        r.Cross (theOther);
        return r;
    }


protected:
    ValueType myBuf[3];
};

//! Equality operator
/*! Returns true if distance between two 3D points is not greater than 1e-7.

    \sa ModelData_BaseXYZd::IsEqual().
*/
template<typename T>
inline bool operator == (const ModelData_BaseXYZ<T>& theV1,
                         const ModelData_BaseXYZ<T>& theV2)
{
    return theV1.IsEqual (theV2, ModelData_BaseXYZ<T>::TraitsType::CoincidenceTolerance());
}

//! Non-equality operator.
/*! Returns !operator==().
*/
template<typename T>
inline bool operator != (const ModelData_BaseXYZ<T>& theV1,
                         const ModelData_BaseXYZ<T>& theV2)
{
    return !(theV1 == theV2);
}

//! Operator +.
/*! Returns a vector equal to vector \a theV1 plus \a theV2.
*/
template<typename T>
inline ModelData_BaseXYZ<T> operator + (const ModelData_BaseXYZ<T>& theV1,
                                       const ModelData_BaseXYZ<T>& theV2)
{
    return ModelData_BaseXYZ<T> (theV1.X() + theV2.X(),
                                theV1.Y() + theV2.Y(),
                                theV1.Z() + theV2.Z());
}

//! Operator +=.
/*! Adds the vector \a theV2 to \a theV1.
*/
template<typename T>
inline void operator += (ModelData_BaseXYZ<T>& theV1,
                         const ModelData_BaseXYZ<T>& theV2)
{
    theV1.Add (theV2);
}

//! Operator -.
/*! Returns a vector equal to vector \a theV1 minus \a theV2.
*/
template<typename T>
inline ModelData_BaseXYZ<T> operator - (const ModelData_BaseXYZ<T>& theV1,
                                       const ModelData_BaseXYZ<T>& theV2)
{
    return theV1.Subtracted (theV2);
}

//! Operator -=.
/*! Subtracts the vector \a theV2 from \a theV1.
*/
template<typename T>
inline void operator -= (ModelData_BaseXYZ<T>& theV1,
                         const ModelData_BaseXYZ<T>& theV2)
{
    theV1.Subtract (theV2);
}

//! Returns a cross-product.
template<typename T>
inline ModelData_BaseXYZ<T> operator ^ (const ModelData_BaseXYZ<T>& theV1,
                                       const ModelData_BaseXYZ<T>& theV2)
{
    return theV1.Crossed (theV2);
}

template<typename T>
inline void operator ^= (ModelData_BaseXYZ<T>& theV1,
                         const ModelData_BaseXYZ<T>& theV2)
{
    theV1.Cross (theV2);
}

template<typename T>
inline ModelData_BaseXYZ<T> operator * (const ModelData_BaseXYZ<T>& theV,
                                       typename ModelData_BaseXYZ<T>::ValueType theVal)
{
    return theV.Multiplied (theVal);
}

template<typename T>
inline ModelData_BaseXYZ<T> operator * (typename ModelData_BaseXYZ<T>::ValueType theVal,
                                        const ModelData_BaseXYZ<T>& theV)
{
    return theV.Multiplied (theVal);
}

template<typename T>
inline void operator *= (ModelData_BaseXYZ<T>& theV,
                         typename ModelData_BaseXYZ<T>::ValueType theVal)
{
    theV.Multiply (theVal);
}

//! Returns a dot-product.
template<typename T>
inline typename ModelData_BaseXYZ<T>::ValueType operator * (const ModelData_BaseXYZ<T>& theV1,
                                                           const ModelData_BaseXYZ<T>& theV2)
{
    return theV1.Dot (theV2);
}

template<typename T>
inline ModelData_BaseXYZ<T> operator / (const ModelData_BaseXYZ<T>& theV,
                                       typename ModelData_BaseXYZ<T>::ValueType theVal)
{
    return theV.Divided (theVal);
}

template<typename T>
inline void operator /= (ModelData_BaseXYZ<T>& theV,
                         typename ModelData_BaseXYZ<T>::ValueType theVal)
{
    theV.Divide (theVal);
}

}

typedef cadex::internal::ModelData_BaseXYZ<double>  ModelData_XYZd;

typedef cadex::internal::ModelData_BaseXYZ<float>   ModelData_XYZf;

#ifdef SWIG
%template (ModelData_XYZd) cadex::internal::ModelData_BaseXYZ<double>;
%template (ModelData_XYZf) cadex::internal::ModelData_BaseXYZ<float>;
#endif

class ModelData_XYZ : public ModelData_XYZd
{
public:

    //! Constructor.
    ModelData_XYZ() {}

    //! Constructor.
    ModelData_XYZ (double theX, double theY, double theZ) : ModelData_XYZd (theX, theY, theZ) {}

    //! Constructor.
    __CADEX_EXPORT ModelData_XYZ (const ModelData_XYZd& theOther) :
        ModelData_XYZd (theOther) {}

    //! Constructor.
    ModelData_XYZ (const ModelData_XYZ& theOther) :
        ModelData_XYZd (theOther.X(), theOther.Y(), theOther.Z()) {}

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_XYZ, gp_XYZ)
};

}

#endif

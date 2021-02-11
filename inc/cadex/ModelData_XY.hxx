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


#ifndef _ModelData_XY_HeaderFile
#define _ModelData_XY_HeaderFile

#include <cadex/Base_Macro.hxx>

#include <cstddef>

class gp_XY;

namespace cadex {

namespace internal {

template<typename T>
struct ModelData_XYTraits;

template<>
struct ModelData_XYTraits<double>
{
    typedef double  ValueType;
    static ValueType CoincidenceTolerance() { return 1e-9; }
};

template<>
struct ModelData_XYTraits<float>
{
    typedef float   ValueType;
    static ValueType CoincidenceTolerance() { return 1e-9f; }
};

/*! \class ModelData_XY
*/
template<typename T>
class ModelData_BaseXY
{
public:

    //! Defines a type of the vector component.
    typedef T   ValueType;

    //! Defines a type of the vector component traits.
    typedef ModelData_XYTraits<T>                        TraitsType;

    //! Constructor.
    ModelData_BaseXY()
    {
        const ValueType v = ValueType();
        for (size_t i = 0; i < 2; ++i)
            myBuf[i] = v;
    }

    //! Constructor.
    /*! Creates a vector with equal components.*/
    ModelData_BaseXY (ValueType theV)
    { SetCoord (theV, theV); }

    //! Constructor.
    ModelData_BaseXY (ValueType theX, ValueType theY)
    { SetCoord (theX, theY); }

    //! Compares if two points are coincident within a tolerance.
    /*! Returns true if distance between \a this and \a theOther object is not greater
        than specified tolerance.
        Expecting that most points are not equal to each other, first checks individual
        components and returns false faster in this case.
    */
    bool IsEqual (const ModelData_BaseXY& theOther, ValueType theTolerance) const
    {
        const ValueType d2 = theTolerance * theTolerance;
        ValueType dX2 = (X() - theOther.X()) * (X() - theOther.X());
        if (dX2 > d2)
            return false;
        ValueType dY2 = (Y() - theOther.Y()) * (Y() - theOther.Y());
        if (dY2 > d2)
            return false;
        return dX2 + dY2 <= d2;
    }

    //! Sets coordinates.
    /*! \sa Coord().*/
    void SetCoord (ValueType theX, ValueType theY)
    {
        X() = theX;
        Y() = theY;
    }

    //! Returns coordinates.
    /*! Populates arguments with values of X() and Y().
        \sa SetCoord().
    */
    void Coord (ValueType& theX, ValueType& theY) const
    {
        theX = X();
        theY = Y();
    }

    ValueType operator[] (size_t i) const { return myBuf[i]; }
    ValueType& operator[] (size_t i) { return myBuf[i]; }

    ValueType X() const { return myBuf[0]; }
    ValueType& X() { return myBuf[0]; }

    ValueType Y() const { return myBuf[1]; }
    ValueType& Y() { return myBuf[1]; }

    //! Returns a square modulus.
    /*! \sa Modulus().*/
    ValueType SquareModulus() const
    {
        return X() * X() + Y() * Y();
    }

    //! Returns a modulus.
    /*! \sa SquareModulus().*/
    ValueType Modulus() const
    {
        return sqrt (SquareModulus());
    }

protected:
    ValueType myBuf[2];
};

//! Equality operator
/*! Returns true if distance between two 3D points is not greater than 1e-7.

    \sa ModelData_BaseXYd::IsEqual().
*/
template<typename T>
inline bool operator == (const ModelData_BaseXY<T>& theV1,
                         const ModelData_BaseXY<T>& theV2)
{
    return theV1.IsEqual (theV2, ModelData_BaseXY<T>::TraitsType::CoincidenceTolerance());
}

//! Non-equality operator.
/*! Returns !operator==().
*/
template<typename T>
inline bool operator != (const ModelData_BaseXY<T>& theV1,
                         const ModelData_BaseXY<T>& theV2)
{
    return !(theV1 == theV2);
}

//! Operator +.
/*! Returns a vector equal to vector \a theV1 plus \a theV2.
*/
template<typename T>
inline ModelData_BaseXY<T> operator + (const ModelData_BaseXY<T>& theV1, const ModelData_BaseXY<T>& theV2)
{
    return ModelData_BaseXY<T> (theV1.X() + theV2.X(), theV1.Y() + theV2.Y());
}

//! Operator -.
/*! Returns a vector equal to vector \a theV1 minus \a theV2.
*/
template<typename T>
inline ModelData_BaseXY<T> operator - (const ModelData_BaseXY<T>& theV1, const ModelData_BaseXY<T>& theV2)
{
    return ModelData_BaseXY<T> (theV1.X() - theV2.X(), theV1.Y() - theV2.Y());
}

//! Returns a cross-product.
template<typename T>
inline typename ModelData_BaseXY<T>::ValueType operator ^ (
    const ModelData_BaseXY<T>& theV1,
    const ModelData_BaseXY<T>& theV2)
{
    return theV1.X() * theV2.Y() - theV1.Y() * theV2.X();
}

template<typename T>
inline ModelData_BaseXY<T> operator * (const ModelData_BaseXY<T>& theV,
                                      typename ModelData_BaseXY<T>::ValueType theVal)
{
    return ModelData_BaseXY<T> (theV.X() * theVal, theV.Y() * theVal);
}

template<typename T>
inline void operator *= (ModelData_BaseXY<T>& theV,
                         typename ModelData_BaseXY<T>::ValueType theVal)
{
    theV.X() *= theVal;
    theV.Y() *= theVal;
}

//! Returns a dot-product.
template<typename T>
inline typename ModelData_BaseXY<T>::ValueType operator * (const ModelData_BaseXY<T>& theV1,
                                                          const ModelData_BaseXY<T>& theV2)
{
    return theV1.X() * theV2.X() + theV1.Y() * theV2.Y();
}

template<typename T>
inline ModelData_BaseXY<T> operator / (const ModelData_BaseXY<T>& theV,
                                      typename ModelData_BaseXY<T>::ValueType theVal)
{
    return ModelData_BaseXY<T> (theV.X() / theVal, theV.Y() / theVal);
}

template<typename T>
inline void operator /= (ModelData_BaseXY<T>& theV,
                         typename ModelData_BaseXY<T>::ValueType theVal)
{
    theV.X() /= theVal;
    theV.Y() /= theVal;
}

}

typedef cadex::internal::ModelData_BaseXY<double>  ModelData_XYd;

typedef cadex::internal::ModelData_BaseXY<float>   ModelData_XYf;

#ifdef SWIG
%template (ModelData_XYd) cadex::internal::ModelData_BaseXY<double>;
%template (ModelData_XYf) cadex::internal::ModelData_BaseXY<float>;
#endif

class ModelData_XY : public ModelData_XYd
{
public:

    //! Constructor.
    ModelData_XY() {}

    //! Constructor.
    ModelData_XY (double theX, double theY) : ModelData_XYd (theX, theY) {}

    //! Constructor.
    ModelData_XY (const ModelData_XY& theOther) :
        ModelData_XYd (theOther.X(), theOther.Y()) {}

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_XY, gp_XY)
};

}

#endif

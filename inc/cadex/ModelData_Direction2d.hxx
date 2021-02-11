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


#ifndef _ModelData_Direction2d_HeaderFile
#define _ModelData_Direction2d_HeaderFile

#include <cadex/ModelData_Vector2d.hxx>
#include <limits>

class gp_Dir2d;

namespace cadex {

class ModelData_Transformation2d;

namespace internal {

/*! \class ModelData_BaseDirection2d
*/
template<typename T>
class ModelData_BaseDirection2d
{
public:

    //! Defines a type of the Direction component.
    typedef T    ValueType;

    //! Defines a type of the vector component traits.
    typedef ModelData_VectorTraits2d<T>                        TraitsType;

    //! Constructor.
    ModelData_BaseDirection2d() : myCoord (T(0), T(1)) {}

    //! Constructor.
    /*! Creates a vector with equal components.*/
    ModelData_BaseDirection2d (ValueType theV) : myCoord (theV) { Normalize(); }

    //! Constructor.
    ModelData_BaseDirection2d (ValueType theX, ValueType theY) :
        myCoord (theX, theY) { Normalize(); }

    //! Constructor.
    template<typename Y>
    ModelData_BaseDirection2d (const ModelData_BaseXY<Y>& theXY) :
        myCoord (theXY.X(), theXY.Y()) { Normalize(); }

    //! Constructor.
    template<typename Y>
    ModelData_BaseDirection2d (const ModelData_BaseDirection2d<Y>& theOther) :
        myCoord (theOther.X(), theOther.Y()) {}

    ValueType operator[] (size_t i) const { return myCoord[i]; }
    ValueType& operator[] (size_t i) { return myCoord[i]; }

    ValueType X() const { return myCoord[0]; }
    ValueType& X() { return myCoord[0]; }

    ValueType Y() const { return myCoord[1]; }
    ValueType& Y() { return myCoord[1]; }

    void Reverse()
    {
        for (size_t i = 0; i < 2; ++i) {
            myCoord[i] = -myCoord[i];
        }
    }

    ModelData_BaseDirection2d<T> Reversed() const
    {
        auto r = *this;
        r.Reverse();
        return r;
    }

    bool IsParallel (const ModelData_BaseDirection2d<T>& theOther, ValueType theTolerance) const
    {
        ValueType d = (*this) * theOther;
        return (1. - fabs (d)) <= theTolerance;
    }
    __CADEX_DEFINE_PROPERTY(ModelData_BaseXY<T>, Coord)

protected:

    void Normalize()
    {
        auto aModulus = myCoord.Modulus();
        if (aModulus > std::numeric_limits<T>::min()) {
            myCoord /= aModulus;
        }
    }
};

//! Non-equality operator.
/*! Returns !operator==().
*/
template<typename T>
inline bool operator != (const ModelData_BaseDirection2d<T>& theV1,
                         const ModelData_BaseDirection2d<T>& theV2)
{
    return !(theV1 == theV2);
}

template<typename T>
inline typename ModelData_BaseDirection2d<T>::ValueType operator ^ (
    const ModelData_BaseDirection2d<T>& theV1,
    const ModelData_BaseDirection2d<T>& theV2)
{
    typename ModelData_BaseDirection2d<T>::ValueType r = theV1.Coord() ^ theV2.Coord();
    return r;
}

//! Returns a dot-product.
template<typename T>
inline typename ModelData_BaseDirection2d<T>::ValueType operator * (
    const ModelData_BaseDirection2d<T>& theV1,
    const ModelData_BaseDirection2d<T>& theV2)
{
    return theV1.Coord() * theV2.Coord();
}

}

typedef cadex::internal::ModelData_BaseDirection2d<double>   ModelData_Directiond2d;

typedef cadex::internal::ModelData_BaseDirection2d<float>    ModelData_Directionf2d;

#ifdef SWIG
    %template (ModelData_Directiond2d) cadex::internal::ModelData_BaseDirection2d<double>;
    %template (ModelData_Directionf2d) cadex::internal::ModelData_BaseDirection2d<float>;
#endif


class ModelData_Direction2d : public ModelData_Directiond2d
{
public:
    ModelData_Direction2d() {}

    //! Constructor.
    ModelData_Direction2d (const ModelData_Direction2d& theOther) :
        ModelData_Directiond2d (theOther.X(), theOther.Y()) {}

    //! Constructor.
    ModelData_Direction2d (double theX, double theY) :
        ModelData_Directiond2d (theX, theY) {}

    //! Constructor.
    template<typename T>
    ModelData_Direction2d (const internal::ModelData_BaseDirection2d<T>& theOther) :
        ModelData_Directiond2d (theOther.X(), theOther.Y()) {}

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_Direction2d, gp_Dir2d)

    __CADEX_EXPORT void Transform (const ModelData_Transformation2d& theTransformation);

    ModelData_Direction2d Transformed (const ModelData_Transformation2d& theTransformation) const
    {
        ModelData_Direction2d r = *this;
        r.Transform (theTransformation);
        return r;
    }

    __CADEX_EXPORT static const ModelData_Direction2d& XDir();
    __CADEX_EXPORT static const ModelData_Direction2d& YDir();
};

}

#endif

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


#ifndef _ModelData_Direction_HeaderFile
#define _ModelData_Direction_HeaderFile

#include <cadex/ModelData_Vector.hxx>
#include <limits>

class gp_Dir;

namespace cadex {

class ModelData_Transformation;

namespace internal {

/*! \class ModelData_BaseDirection
*/
template<typename T>
class ModelData_BaseDirection
{
public:

    //! Defines a type of the Direction component.
    typedef T    ValueType;

    //! Defines a type of the vector component traits.
    typedef ModelData_VectorTraits<T>                        TraitsType;

    //! Constructor.
    ModelData_BaseDirection() : myCoord (T(0), T(0), T(1)) {}

    //! Constructor.
    /*! Creates a vector with equal components.*/
    ModelData_BaseDirection (ValueType theV) : myCoord (theV) { Normalize(); }

    //! Constructor.
    ModelData_BaseDirection (ValueType theX, ValueType theY, ValueType theZ) :
        myCoord (theX, theY, theZ) { Normalize(); }

    //! Constructor.
    template<typename Y>
    ModelData_BaseDirection (const ModelData_BaseXYZ<Y>& theXYZ) :
        myCoord (theXYZ.X(), theXYZ.Y(), theXYZ.Z()) { Normalize(); }

    //! Constructor.
    template<typename Y>
    ModelData_BaseDirection (const ModelData_BaseDirection<Y>& theOther) :
        myCoord (theOther.X(), theOther.Y(), theOther.Z()) {}

    ValueType operator[] (size_t i) const { return myCoord[i]; }
    ValueType& operator[] (size_t i) { return myCoord[i]; }

    ValueType X() const { return myCoord[0]; }
    ValueType& X() { return myCoord[0]; }

    ValueType Y() const { return myCoord[1]; }
    ValueType& Y() { return myCoord[1]; }

    ValueType Z() const { return myCoord[2]; }
    ValueType& Z() { return myCoord[2]; }

    void Reverse()
    {
        for (size_t i = 0; i < 3; ++i) {
            myCoord[i] = -myCoord[i];
        }
    }

    ModelData_BaseDirection<T> Reversed() const
    {
        auto r = *this;
        r.Reverse();
        return r;
    }

    bool IsParallel (const ModelData_BaseDirection<T>& theOther, ValueType theTolerance) const
    {
        ValueType d = (*this) * theOther;
        return (1. - fabs (d)) <= theTolerance;
    }

    __CADEX_DEFINE_PROPERTY(ModelData_BaseXYZ<T>, Coord)

protected:

    void Normalize()
    {
        auto aModulus = myCoord.Modulus();
        if (aModulus > std::numeric_limits<T>::min()) {
            myCoord /= aModulus;
        }
    }
};

#if 0
//! Equality operator
/*! Returns true if two vectors are equal with default distance and angular tolerances.

    \sa ModelData_Direction3d::IsEqual().
*/
template<typename T>
inline bool operator == (const ModelData_BaseDirection<T>& theV1,
                         const ModelData_BaseDirection<T>& theV2)
{
    //TODO - implement ModelData_BaseDirection::IsEqual()
    return theV1.IsEqual (theV2,
                          ModelData_BaseDirection<T>::TraitsType::CoincidenceTolerance(),
                          ModelData_BaseDirection<T>::TraitsType::AngularTolerance());
}
#endif

//! Non-equality operator.
/*! Returns !operator==().
*/
template<typename T>
inline bool operator != (const ModelData_BaseDirection<T>& theV1,
                         const ModelData_BaseDirection<T>& theV2)
{
    return !(theV1 == theV2);
}

template<typename T>
inline ModelData_BaseDirection<T> operator ^ (const ModelData_BaseDirection<T>& theV1,
                                              const ModelData_BaseDirection<T>& theV2)
{
    ModelData_BaseDirection<T> r = theV1.Coord() ^ theV2.Coord();
    return r;
}

//! Returns a dot-product.
template<typename T>
inline typename ModelData_BaseDirection<T>::ValueType operator * (
    const ModelData_BaseDirection<T>& theV1,
    const ModelData_BaseDirection<T>& theV2)
{
    return theV1.Coord() * theV2.Coord();
}

}

//! Defines direction with double (i.e. double precision) components.
typedef cadex::internal::ModelData_BaseDirection<double>   ModelData_Directiond;

//! Defines direction with float (i.e. single precision) components.
typedef cadex::internal::ModelData_BaseDirection<float>    ModelData_Directionf;

#ifdef SWIG
%template (ModelData_Directiond) cadex::internal::ModelData_BaseDirection<double>;
%template (ModelData_Directionf) cadex::internal::ModelData_BaseDirection<float>;
#endif

class ModelData_Direction : public ModelData_Directiond
{
public:
    ModelData_Direction() {}

    //! Constructor.
    ModelData_Direction (const ModelData_Direction& theOther) :
        ModelData_Directiond (theOther.X(), theOther.Y(), theOther.Z()) {}

    //! Constructor.
    ModelData_Direction (double theX, double theY, double theZ) :
        ModelData_Directiond (theX, theY, theZ) {}

    //! Constructor.
    template<typename T>
    ModelData_Direction (const internal::ModelData_BaseDirection<T>& theOther) :
        ModelData_Directiond (theOther.X(), theOther.Y(), theOther.Z()) {}

    //! Constructor.
    template<typename T>
    ModelData_Direction (const internal::ModelData_BaseXYZ<T>& theOther) :
        ModelData_Directiond (theOther) {}

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_Direction, gp_Dir)

    __CADEX_EXPORT void Transform (const ModelData_Transformation& theTransformation);

    ModelData_Direction Transformed (const ModelData_Transformation& theTransformation) const
    {
        ModelData_Direction r = *this;
        r.Transform (theTransformation);
        return r;
    }

    __CADEX_EXPORT static const ModelData_Direction& XDir();
    __CADEX_EXPORT static const ModelData_Direction& YDir();
    __CADEX_EXPORT static const ModelData_Direction& ZDir();
};

}

#endif

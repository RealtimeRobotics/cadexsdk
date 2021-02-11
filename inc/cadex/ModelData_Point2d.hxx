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


#ifndef _ModelData_Point2d_HeaderFile
#define _ModelData_Point2d_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cadex/ModelData_XY.hxx>

class gp_Pnt2d;

namespace cadex {

class ModelData_Transformation2d;

namespace internal {

template<typename T>
struct ModelData_Point2dTraits
{
    typedef typename ModelData_XYTraits<T>::ValueType   ValueType;
    static ValueType CoincidenceTolerance()
    {
        return ModelData_XYTraits<T>::CoincidenceTolerance();
    }
};

/*! \class ModelData_BasePoint2d
*/
template<typename T>
class ModelData_BasePoint2d
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Defines a type of the Point component.
    typedef T    ValueType;

    //! Defines a type of the vector component.
    typedef ValueType                                         value_type;

    //! Defines a type of the point component traits.
    typedef ModelData_Point2dTraits<T>                        TraitsType;

    //! Constructor.
    ModelData_BasePoint2d() {}

    //! Constructor.
    /*! Creates a Point with equal components.*/
    ModelData_BasePoint2d (ValueType theV) : myCoord (theV) {}

    //! Constructor.
    ModelData_BasePoint2d (ValueType theX, ValueType theY) :
        myCoord (theX, theY) {}

    //! Constructor.
    ModelData_BasePoint2d (const ModelData_BaseXY<T>& theXY) : myCoord (theXY) {}

    //! Constructor.
    ModelData_BasePoint2d (const ModelData_BasePoint2d& theOther) : myCoord (theOther.myCoord) {}

    ValueType  operator[] (size_t i) const { return myCoord[i]; }
    ValueType& operator[] (size_t i) { return myCoord[i]; }

    ValueType  X() const { return myCoord[0]; }
    ValueType& X() { return myCoord[0]; }

    ValueType  Y() const { return myCoord[1]; }
    ValueType& Y() { return myCoord[1]; }

    //! Sets coordinates.
    /*! \sa Coord().*/
    void SetCoord (ValueType theX, ValueType theY)
    {
        Coord().SetCoord (theX, theY);
    }

    //! Compares if two points are coincident within a tolerance.
    /*! Uses ModelData_BaseXY::IsEqual().
    */
    bool IsEqual (const ModelData_BasePoint2d& theOther, ValueType theTolerance) const
    {
        return myCoord.IsEqual (theOther.Coord(), theTolerance);
    }

    __CADEX_DEFINE_PROPERTY(ModelData_BaseXY<T>, Coord)
};

//! Equality operator
/*! Returns true if two points are equal with default distance tolerance.

    \sa ModelData_Point2d::IsEqual().
*/
template<typename T>
inline bool operator == (const ModelData_BasePoint2d<T>& theV1,
                         const ModelData_BasePoint2d<T>& theV2)
{
    return theV1.IsEqual (theV2,
        ModelData_BasePoint2d<T>::TraitsType::CoincidenceTolerance());
}

//! Non-equality operator.
/*! Returns !operator==().
*/
template<typename T>
inline bool operator != (const ModelData_BasePoint2d<T>& theV1,
                         const ModelData_BasePoint2d<T>& theV2)
{
    return !(theV1 == theV2);
}

//! Operator +.
/*! Returns a point equal to point \a theV1 plus \a theV2.
*/
template<typename T>
inline ModelData_BasePoint2d<T> operator + (const ModelData_BasePoint2d<T>& theV1,
                                           const ModelData_BasePoint2d<T>& theV2)
{
    ModelData_BasePoint2d<T> r = theV1.Coord() + theV2.Coord();
    return r;
}

//! Operator -.
/*! Returns a point equal to point \a theV1 minus \a theV2.
*/
template<typename T>
inline ModelData_BasePoint2d<T> operator - (const ModelData_BasePoint2d<T>& theV1,
                                           const ModelData_BasePoint2d<T>& theV2)
{
    ModelData_BasePoint2d<T> r = theV1.Coord() - theV2.Coord();
    return r;
}

template<typename T>
inline ModelData_BasePoint2d<T> operator * (const ModelData_BasePoint2d<T>& theV,
                                           typename ModelData_BasePoint2d<T>::ValueType theVal)
{
    ModelData_BasePoint2d<T> r = theV.Coord() * theVal;
    return r;
}

template<typename T>
inline void operator *= (ModelData_BasePoint2d<T>& theV,
                         typename ModelData_BasePoint2d<T>::ValueType theVal)
{
    theV.Coord() *= theVal;
}

template<typename T>
inline ModelData_BasePoint2d<T> operator / (const ModelData_BasePoint2d<T>& theV,
                                           typename ModelData_BasePoint2d<T>::ValueType theVal)
{
    ModelData_BasePoint2d<T> r = theV.Coord() / theVal;
    return r;
}

template<typename T>
inline void operator /= (ModelData_BasePoint2d<T>& theV,
                         typename ModelData_BasePoint2d<T>::ValueType theVal)
{
    theV.Coord() /= theVal;
}

}

typedef cadex::internal::ModelData_BasePoint2d<double>   ModelData_Point2dd;

typedef cadex::internal::ModelData_BasePoint2d<float>    ModelData_Point2df;

#ifdef SWIG
%template (ModelData_Point2dd) cadex::internal::ModelData_BasePoint2d<double>;
%template (ModelData_Point2df) cadex::internal::ModelData_BasePoint2d<float>;
#endif

class ModelData_Point2d : public ModelData_Point2dd
{
public:
    ModelData_Point2d() {}

    //! Constructor.
    ModelData_Point2d (const ModelData_XY& theOther) :
        ModelData_Point2dd (theOther) {}

    //! Constructor.
    ModelData_Point2d (const ModelData_Point2dd& theOther) :
        ModelData_Point2dd (theOther) {}

    //! Constructor.
    ModelData_Point2d (double theX, double theY) :
        ModelData_Point2dd (theX, theY) {}

    __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(ModelData_Point2d, gp_Pnt2d)

    __CADEX_EXPORT static const ModelData_Point2d& Origin();

    __CADEX_EXPORT void Transform (const ModelData_Transformation2d& theTransformation);

    ModelData_Point2d Transformed (const ModelData_Transformation2d& theTransformation) const
    {
        ModelData_Point2d r = *this;
        r.Transform (theTransformation);
        return r;
    }
};

}

#endif

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


#ifndef _ModelData_Color_HeaderFile
#define _ModelData_Color_HeaderFile

#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cmath>

namespace cadex {

/*! \class ModelData_Color
    \brief Defines an RGBA color (with alpha channel).

    Components must be within a [0, 1] range.
*/
class ModelData_Color
{
public:

    typedef float   value_type;
    typedef float   ValueType;


    __CADEX_DEFINE_MEMORY_MANAGEMENT

    //! Constructor.
    /*! Creates a black color with alpha channel 1.*/
    ModelData_Color()
    {
        SetValue (0.f);
        myBuf[3] = 1.f;
    }

    //! Constructor.
    /*! Creates a color with explicit values. Each value must be within [0, 1] range.*/
    ModelData_Color (float r, float g, float b, float a = 1.f) { Set (r, g, b, a); }

    //! Constructor.
    /*! Creates a color with explicit values. Each value must be within [0, 255] range.*/
    ModelData_Color (int r, int g, int b, int a = 255) { Set (r, g, b, a); }

    //! Constructor.
    /*! Creates a color with explicit argb value */
    explicit ModelData_Color (int argb) {
        Set ((argb & 0x00FF0000) >> 16,
             (argb & 0x0000FF00) >> 8,
             (argb & 0x000000FF),
             (argb & 0xFF000000) >> 24);
    }

    float R() const { return myBuf[0]; }
    float& R() { return myBuf[0]; }

    float G() const { return myBuf[1]; }
    float& G() { return myBuf[1]; }

    float B() const { return myBuf[2]; }
    float& B() { return myBuf[2]; }

    //! Returns alpha-channel.
    float A() const { return myBuf[3]; }

    //! Returns alpha-channel.
    float& A() { return myBuf[3]; }

    /*! \a theIndex must be in the [0, n) range.*/
    const value_type& Value (size_t theIndex) const { return myBuf[theIndex]; }

    /*! \a theIndex must be in the [0, n) range.*/
    const value_type& operator[] (size_t theIndex) const { return myBuf[theIndex]; }

    /*! \a theIndex must be in the [0, n) range.*/
    value_type& operator[] (size_t theIndex) { return myBuf[theIndex]; }

    void SetValue (const value_type& theVal)
    {
        for (int i = 0; i < 4; ++i)
            SetValue (i, theVal);
    }

    __CADEX_EXPORT void SetValue (int theIndex, const value_type& theVal);

    //! Sets individual color components.
    void Set (float r, float g, float b, float a = 1.f)
    {
        SetValue (0, r);
        SetValue (1, g);
        SetValue (2, b);
        SetValue (3, a);
    }

    //! Sets individual color components.
    void Set (int r, int g, int b, int a = 255)
    {
        Set (r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    bool IsValid() const
    {
        for (size_t i = 0; i < 4; ++i)
            if (myBuf[i] < 0.f || myBuf[i] > 1.f)
                return false;
        return true;
    }

    static float Precision() { return 0.0001f; }

protected:

    ValueType   myBuf[4];
};



//! Equality operator.
/*! Returns true if all components of \a theV1 and \a theV2 are the same or
    differences between the component do not exceed ModelData_Color::Precision().
*/
inline bool operator== (const ModelData_Color& theV1, const ModelData_Color& theV2)
{
    for (int i = 0; i < 4; ++i)
        if (fabs (theV1[i] - theV2[i]) > ModelData_Color::Precision())
            return false;
    return true;
}

//! Non-equality operator.
/*! Returns the value opposite to the value returned by the equality operator.
*/
inline bool operator != (const ModelData_Color& theV1, const ModelData_Color& theV2)
{ return !(theV1 == theV2); }

//! Compare operator.
/*! Returns true if all components of \a theV1 are less than respective components of \a theV2.
*/
inline bool operator < (const ModelData_Color& theV1, const ModelData_Color& theV2)
{
    for (int i = 0; i < 4; ++i)
        if (theV1[i] < theV2[i])
            return true;
        else if (theV1[i] > theV2[i])
            return false;
    return false;
}

/*! \class ModelData_ColorHash
    \brief Hasher for ModelData_Color objects.
*/
class ModelData_ColorHash
{
public:
    __CADEX_EXPORT size_t operator() (const ModelData_Color& theValue) const;
};

namespace internal {
//to preserve source compatibility with internal SDK methods
typedef ModelData_Color RGBA;
}

}

#endif

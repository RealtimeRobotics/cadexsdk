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


#ifndef _Base_Macro_HeaderFile
#define _Base_Macro_HeaderFile

#include <cadex/Base_BuildDate.hxx>

/*! \internal
    \file Base_Macro.hxx
    \brief Contains macro definitions common for CAD Exchanger SDK.
*/

#ifndef __CADEX_EXPORT
#if _WIN32
#define __CADEX_EXPORT __declspec(dllexport)
#else
#define __CADEX_EXPORT
#endif
#endif /* __CADEX_EXPORT */

/*! \def __CADEX_GCC_VER
    \brief Expands to full version of GNU C/C++ compiler.

    E.g., for gcc 4.8.2 this macro expands to 40802
*/
#define __CADEX_GCC_VER (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

/*! \def __CADEX_DEFINE_PROPERTY

    This macro must be used within a public section of the class definition.
*/
#define __CADEX_DEFINE_PROPERTY(PTYPE,PNAME) \
    \
    public: \
        const PTYPE & PNAME() const { return my ## PNAME ; } \
        PTYPE & PNAME() { return my ## PNAME ; } \
    protected: \
        PTYPE   my ## PNAME; \
    public:

/*! \def __CADEX_DEFINE_PRIMITIVE_PROPERTY

    This macro must be used within a public section of the class definition.
*/
#define __CADEX_DEFINE_PRIMITIVE_PROPERTY(PTYPE,PNAME) \
    \
    public: \
        PTYPE PNAME() const { return my ## PNAME ; } \
        PTYPE & PNAME() { return my ## PNAME ; } \
    protected: \
        PTYPE   my ## PNAME; \
    public:

/*! \def __CADEX_DEFINE_INITIALIZED_PRIMITIVE_PROPERTY

    This macro must be used within a public section of the class definition.
*/
#define __CADEX_DEFINE_INITIALIZED_PRIMITIVE_PROPERTY(PTYPE,PNAME,PVALUE) \
    \
    public: \
        PTYPE PNAME() const { return my ## PNAME ; } \
        PTYPE & PNAME() { return my ## PNAME ; } \
    protected: \
        PTYPE   my ## PNAME = PVALUE; \
    public:

/*! \def __CADEX_DEFINE_ARRAY_PROPERTY

    This macro must be used within a public section of the class definition.
*/
#define __CADEX_DEFINE_ARRAY_PROPERTY(PTYPE,N,PNAME) \
    \
    public: \
        inline PTYPE* PNAME() { return my ## PNAME ; } \
        inline const PTYPE* PNAME() const { return my ## PNAME ; } \
    protected: \
        PTYPE   my ## PNAME [ N ]; \
    public:

/*! \def __CADEX_DEFINE_PRIMITIVE_ARRAY_PROPERTY

    This macro must be used within a public section of the class definition.
*/
#define __CADEX_DEFINE_PRIMITIVE_ARRAY_PROPERTY(PTYPE,N,PNAME) \
    __CADEX_DEFINE_ARRAY_PROPERTY(PTYPE,N,PNAME)

/*! \def __CADEX_DEFINE_PROGRESS_STATUS
*/
#define __CADEX_DEFINE_PROGRESS_STATUS \
    __CADEX_DEFINE_PROPERTY (Base_ProgressStatus, ProgressStatus)

/*! \def __CADEX_DEFINE_CONST_CAST_OPERATOR

    This macro must be used within a public section of the class definition.
*/
#define __CADEX_DEFINE_CONST_CAST_OPERATOR(T) \
    __CADEX_EXPORT operator const T&() const;

/*! \def __CADEX_DEFINE_NOCONST_CAST_OPERATOR

    This macro must be used within a public section of the class definition.
*/
#define __CADEX_DEFINE_NOCONST_CAST_OPERATOR(T) \
    __CADEX_EXPORT operator T&();

/*! \def __CADEX_DEFINE_CAST_OPERATOR

    This macro must be used within a public section of the class definition.
*/
#define __CADEX_DEFINE_CAST_OPERATOR(T) \
    __CADEX_DEFINE_CONST_CAST_OPERATOR(T) \
    __CADEX_DEFINE_NOCONST_CAST_OPERATOR(T)

#ifndef SWIG
/*! \def __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR
    \brief Defines a constructor and cast operators.
*/
#define __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(TT,T) \
    __CADEX_EXPORT TT (const T&); \
    __CADEX_DEFINE_CAST_OPERATOR(T)

/*! \def __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR
    \brief Defines a constructor and cast operators.
*/
#define __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(TT,T) \
    __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(TT,T) \
    __CADEX_EXPORT TT& operator= (const T&);
#else
#define __CADEX_DEFINE_CTOR_AND_CAST_OPERATOR(TT,T)
#define __CADEX_DEFINE_CTOR_ASSIGN_AND_CAST_OPERATOR(TT,T)
#endif

/*! \def __CADEX_DEFINE_ALIGNED_MEMBER
    \brief Defines aligned member of a class.

    This macro must be used within a private or protected section of the class definition.
*/
#define __CADEX_DEFINE_ALIGNED_MEMBER(SIZE,ALLIGN) \
    static const size_t myImplSize = (SIZE); \
    union { \
        ALLIGN  myAlign; \
        char    myBuf[myImplSize];\
    };

/*! \def __CADEX_DEFINE_IMPL
    \brief Defines a special implementation object.

    This macro must be used within a public section of the class definition.

    \note Implementations are not a part of public CAD Exchanger API
          and are reserved for an internal usage only.
*/
#define __CADEX_DEFINE_IMPL(CLASS)                                \
    public:                                                       \
        typedef std::shared_ptr <internal::CLASS##Impl> ImplType; \
        const ImplType& Impl() const { return myImpl; }           \
    protected:                                                    \
        ImplType    myImpl;                                       \
    public:

/*! \def __CADEX_DEFINE_BASE_IMPL
    \brief Defines a special base implementation object.

    This macro must be used within a public section of the class definition.

    \note Implementations are not a part of public CAD Exchanger API
          and are reserved for an internal usage only.
*/
#define __CADEX_DEFINE_BASE_IMPL(CLASS)                       \
    __CADEX_DEFINE_IMPL (CLASS)                               \
    protected:                                                \
        CLASS (const ImplType& theImpl) : myImpl (theImpl) {} \
    public:

/*! \def __CADEX_ACCEPT_VISITOR
    \brief Implements an Accept method for the given visitor type.
*/
#define __CADEX_ACCEPT_VISITOR(V)                                          \
    public:                                                                \
        void Accept (const V& theVisitor) const override \
        { theVisitor.Visit (*this); }


/*! \def __CADEX_MODELDATA_DEFINE_TYPEID
*/
#define __CADEX_MODELDATA_DEFINE_TYPEID \
    __CADEX_EXPORT static IdType GetTypeId();


#if !defined(OCC_VERSION_HEX)
    /* Standard_Version.hxx must be included before including CAD Exchanger files. Otherwise assume
       that we are in non-OCC environment.
    */
    #define __CADEX_OCC_HANDLE_VERSION 0
#elif defined(_MSC_VER) && (_MSC_VER >= 1800) && (OCC_VERSION_HEX >= 0x070001)
    #define __CADEX_OCC_HANDLE_VERSION 3
#elif (OCC_VERSION_HEX >= 0x070000)
    #define __CADEX_OCC_HANDLE_VERSION 2
#else
    #define __CADEX_OCC_HANDLE_VERSION 1
#endif


#if (__CADEX_OCC_HANDLE_VERSION == 0) || defined(SWIG) || defined(__CADEX_DOXYGEN)
    #define __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(T,C)
    #define __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE2(T,C,A1)
    #define __CADEX_DEFINE_CONST_HANDLE_CAST_OPERATOR(C)
    #define __CADEX_DEFINE_HANDLE_CAST_OPERATOR(C)
#else
    #define __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE(T,C)     __CADEX_EXPORT T (const Handle(C)&);
    #define __CADEX_DEFINE_CONSTRUCTOR_FROM_HANDLE2(T,C,A1) __CADEX_EXPORT T (const Handle(C)&, A1);
    #define __CADEX_DEFINE_CONST_HANDLE_CAST_OPERATOR(C)    __CADEX_EXPORT operator const Handle(C)& () const;
    #define __CADEX_DEFINE_HANDLE_CAST_OPERATOR(C)          __CADEX_EXPORT operator Handle(C)() const;
#endif

#if defined(SWIG) || defined(__CADEX_DOXYGEN)
    #define __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(T,TI)
    #define __CADEX_DEFINE_TYPED_POINTER_OPERATOR(TI)
    #define __CADEX_IMPLEMENT_CONSTRUCTOR_FROM_IMPL(T,TI,BC)
    #define __CADEX_IMPLEMENT_TYPED_POINTER_OPERATOR(T,TI,BC)
#else
    #define __CADEX_DEFINE_CONSTRUCTOR_FROM_IMPL(T,TI)          __CADEX_EXPORT T (TI);
    #define __CADEX_DEFINE_TYPED_POINTER_OPERATOR(TI)           __CADEX_EXPORT TI* operator->() const;
    #define __CADEX_IMPLEMENT_CONSTRUCTOR_FROM_IMPL(T,TI,BC)    T::T (TI* theImpl) : BC (theImpl) {}
    #define __CADEX_IMPLEMENT_TYPED_POINTER_OPERATOR(T,TI,BC)   TI* T::operator->() const \
        { return static_cast<TI*> (BC::operator->()); }
#endif



#if (__CADEX_OCC_HANDLE_VERSION == 0)
    #define __CADEX_DEFINE_HANDLE_TYPE_FWD_PUBLIC
    #define __CADEX_DEFINE_HANDLE_FWD_PUBLIC(C)
#elif (__CADEX_OCC_HANDLE_VERSION == 2)
    #define __CADEX_DEFINE_HANDLE_TYPE_FWD_PUBLIC \
        namespace opencascade { \
        template<typename T> \
        class handle; \
        }

    #define __CADEX_DEFINE_HANDLE_FWD_PUBLIC(C) \
        class C; \
        typedef opencascade::handle<C> Handle_##C;

#else /* (__CADEX_OCC_HANDLE_VERSION == 0) */

    #define __CADEX_DEFINE_HANDLE_TYPE_FWD_PUBLIC
    #define __CADEX_DEFINE_HANDLE_FWD_PUBLIC(C) \
        class C; \
        class Handle_##C;
#endif /* (__CADEX_OCC_HANDLE_VERSION == 0) */

#if defined(__CADEX_SDK_BUILD) || defined(__CADEX_DEVELOPMENT)
    //when building CAD Exchanger SDK all feature previews are enabled
    #define __CADEX_PREVIEW_FILE_MODEL_TOOLS 1
    #define __CADEX_PREVIEW_MIN_BOUNDING_BOX 1
    #define __CADEX_PREVIEW_VISUALIZATION 1
    #define __CADEX_PREVIEW_PMI 1
    #define __CADEX_PREVIEW_SHEETMETAL 1
    #define __CADEX_PREVIEW_TEXTURES 1
    #define __CADEX_PREVIEW_READER_STATISTICS 1
    #define __CADEX_PREVIEW_SAVE_EXTERNAL_REFERENCE_PATHS 1
    #define __CADEX_PREVIEW_ADVANCED_GEOMETRY 1
    #define __CADEX_PREVIEW_WRITER_STATISTICS 1
#endif

#endif

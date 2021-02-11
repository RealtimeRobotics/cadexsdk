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


#ifndef _Base_Allocator_HeaderFile
#define _Base_Allocator_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <stddef.h>
#if __GXX_EXPERIMENTAL_CXX0X__ || (__cplusplus >= 201100L) || (_MSC_VER >= 1600 /*Visual Studio 2010*/)
#include <utility> // std::forward
#endif /*(__cplusplus >= 201100L) || (_MSC_VER >= 1600)*/

#ifdef __cplusplus
extern "C" {
#endif

__CADEX_EXPORT void* cadex_malloc (size_t theSize);
__CADEX_EXPORT void cadex_free (void* thePointer);
__CADEX_EXPORT void* cadex_realloc (void* thePointer, size_t theSize);

#ifdef __cplusplus
}
#endif

/*! \def __CADEX_DEFINE_MEMORY_MANAGEMENT
    \brief Defines new and delete operators to use CAD Exchanger allocator.
*/
#define __CADEX_DEFINE_MEMORY_MANAGEMENT \
    void* operator new (size_t theSize) { return cadex_malloc (theSize); } \
    void operator delete (void* theAddress) { cadex_free (theAddress); } \
    void* operator new (size_t, void* theAddress) { return theAddress; } \
    void operator delete (void*, void*) {} \
    void* operator new[] (size_t theSize) { return cadex_malloc (theSize); } \
    void operator delete[] (void* theAddress) { cadex_free (theAddress); }


namespace cadex {

#if _MSC_VER
    //Workaround for false "unreferenced parameter" warning in destroy().
    #pragma warning (push)
    #pragma warning (disable: 4100)
#endif

//! Implements allocator requirements as defined in ISO C++ Standard 2003, section 20.1.5.
/*! The allocator uses cadex_alloc(), cadex_free(). The allocator can be used with standard
    containers (std::vector, std::map, etc) to take advantage of CAD Exchanger allocator.

    Example of use:
    \code
    std::list<int, Base_Allocator<int> > aL;
    aL.push_back (0);
    \endcode
*/
template<typename T>
class Base_Allocator {
public:

    //! Defines a value type.
    typedef T value_type;

    //! Defines a value pointer type.
    typedef value_type* pointer;
    
    //! Defines a const value pointer type.
    typedef const value_type* const_pointer;

    //! Defines a value reference type.
    typedef value_type& reference;

    //! Defines a const value reference type.
    typedef const value_type& const_reference;

    //! Defines a size type.
    typedef size_t size_type;
    
    //! Defines a pointer difference type.
    typedef ptrdiff_t difference_type;
    template<typename U> struct rebind {
        typedef Base_Allocator<U> other;
    };

    //! Defines whether contents move is allowed on container move assignment.
    typedef std::true_type propagate_on_container_move_assignment;

    //! Constructor.
    /*! Empty constructor.*/
    Base_Allocator() throw() {}

    //! Constructor.
    /*! Empty constructor.*/
    Base_Allocator( const Base_Allocator& ) throw() {}

    //! Destructor.
    /*! Empty implementation.*/
    ~Base_Allocator() throw() {}

    //! Constructor.
    /*! Empty constructor.*/
    template<typename U> Base_Allocator( const Base_Allocator<U>& ) throw() {}

    //! Returns an object address.
    /*! Returns &x.*/
    pointer address( reference x ) const { return &x; }

    //! Returns an object address.
    /*! Returns &x.*/
    const_pointer address( const_reference x ) const { return &x; }

    //! Allocates memory for \a n objects.
    /*! Uses underlying allocator to allocate memory.*/
    pointer allocate( size_type n, const void* /*hint*/ = 0 )
    { return static_cast<pointer>( cadex_malloc(n * sizeof( value_type ))); }

    //! Frees previously allocated memory.
    /*! Uses underlying allocator to deallocate memory.*/
    void deallocate( pointer p, size_type ) { cadex_free( p ); }

    //! Returns the largest value for which method allocate might succeed.
    size_type max_size() const throw()
    {
        size_type aMax = static_cast<size_type>( -1 ) / sizeof( value_type );
        return (aMax > 0 ? aMax : 1);
    }

#if _MSC_VER && _MSC_VER >= 1900 /*Visual Studio 2015*/
    /* construct() and destroy() are deprecated starting from C++17 and should be avoided.
       Either way some optimizations are disabled. E.g. construction of cadex containers from raw pointers
       will use element-by-element copy instead of memmove intrinsic.

       For explicit usage, std::allocator_traits should be chosen instead.
    */

/*With c++11 need use new construct/destroy function implementation*/
#elif (__GXX_EXPERIMENTAL_CXX0X__ || (__cplusplus >= 201100L) || (_MSC_VER >= 1800 /*Visual Studio 2013*/))

    //! Constructs an object.
    /*! Forward its arguments to the appropriate constructor.*/
    template <typename U, typename... Args>
    void construct (U* p, Args&&... args)
    { new( (void*) ( p )) U ( std::forward<Args>( args )... ); }

    template <typename U>
    void destroy (U* p) { p->~U(); }

#else

    //! Constructs an object.
    /*! Uses placement new operator and copy constructor to construct an object.*/
    void construct( pointer p, const_reference val )
    { new( static_cast<void*>( p )) value_type( val ); }

    //! Constructs an object.
    /*! Uses placement new operator and move constructor to construct an object.*/
    void construct( pointer p, T&& val )
    { new( static_cast<void*>( p )) value_type( std::move (val) ); }

    //! Constructs an object.
    /*! Uses placement new operator and universal constructor to construct an object.*/
    template <typename U>
    void construct( pointer p, U&& val )
    { new( static_cast<void*>( p )) value_type( std::forward<U> (val) ); }

    //! Destroys the object.
    /*! Uses object destructor.*/
    void destroy( pointer p ) { p->~value_type(); }

#endif
};

#if _MSC_VER
    #pragma warning (pop)
#endif

//! Implements specialization Base_Allocator<void>.
/*! This allocator can be used in the same way as any other specialization:
    \code
    std::list<int, Base_Allocator<void> > aL;
    aL.push_back (0);
    \endcode
*/
template<> 
class Base_Allocator<void> {
public:

    //! Defines a pointer type.
    typedef void* pointer;

    //! Defines a const pointer type.
    typedef const void* const_pointer;

    //! Defines a value type.
    typedef void value_type;
    template<typename U> struct rebind {
        typedef Base_Allocator<U> other;
    };
};

//! Equality operator.
/*! Always returns true.*/
template<typename T, typename U>
inline bool operator==( const Base_Allocator<T>&, const Base_Allocator<U>&) { return true; }


//! Non-equality operator.
/*! Always returns false.*/
template<typename T, typename U>
inline bool operator!=( const Base_Allocator<T>&, const Base_Allocator<U>&) { return false; }

}

#endif

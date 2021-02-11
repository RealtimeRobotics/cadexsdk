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


#ifndef _ModelData_PropertyTable_HeaderFile
#define _ModelData_PropertyTable_HeaderFile

#include <cadex/ModelData_BaseObject.hxx>
#include <cadex/Base_Allocator.hxx>
#include <cadex/Base_Macro.hxx>
#include <cadex/Base_SharedPtr.hxx>
#include <cadex/Base_TypeDef.hxx>

namespace cadex {

namespace internal {
class ModelData_PropertyTableImpl;
}

class Base_String;
class Base_UTF16String;
class ModelData_Box;
class ModelData_Point;

class ModelData_PropertyTable : public ModelData_BaseObject
{
public:

    __CADEX_MODELDATA_DEFINE_TYPEID

    typedef const Base_UTF16String& PropertyNameConstReference;

    typedef cadex::internal::ModelData_PropertyTableImpl   ImplType;

#ifndef SWIG
    typedef time_t TimeVal;
#else
    typedef I64    TimeVal;
#endif

    struct TimeType
    {
        TimeType() : myValue (TimeVal()) {}
        TimeType (TimeVal theValue) : myValue (theValue) {}

        TimeVal myValue;
    };

    __CADEX_EXPORT ModelData_PropertyTable();
    __CADEX_EXPORT ModelData_PropertyTable (initialized);
    __CADEX_EXPORT ModelData_PropertyTable (ImplType* theImpl);

    __CADEX_EXPORT void Add (const Base_UTF16String& theName, I32 theValue);
    __CADEX_EXPORT void Add (const Base_UTF16String& theName, I64 theValue);
    __CADEX_EXPORT void Add (const Base_UTF16String& theName, float theValue);
    __CADEX_EXPORT void Add (const Base_UTF16String& theName, double theValue);
    __CADEX_EXPORT void Add (const Base_UTF16String& theName, TimeType theValue);

    __CADEX_EXPORT void Add (const Base_UTF16String& theName, const Base_UTF16String& theValue);
    __CADEX_EXPORT void Add (const Base_UTF16String& theName, const ModelData_Point& theValue);
    __CADEX_EXPORT void Add (const Base_UTF16String& theName, const ModelData_Box& theValue);

    //! Appends properties from another property table.
    __CADEX_EXPORT void Add (const ModelData_PropertyTable& theTable);

    class Provider
    {
    public:

        __CADEX_DEFINE_MEMORY_MANAGEMENT

        __CADEX_EXPORT virtual ~Provider();

        //! Feeds the property table.
        /*! Subclasses must redefine this method to call AddProperty() of \a theTable.*/
        virtual void Feed (ModelData_PropertyTable& theTable) const = 0;
    };

    //! Adds a provider with a deleter.
    /*! \a theProvider will be deleted with the specified deleter.
    */
    __CADEX_EXPORT void AddProvider (const std::shared_ptr<Provider>& theProvider);

    //! Returns true if the table contains a property with a specified name.
    __CADEX_EXPORT bool HasProperty (const Base_UTF16String& theName,
        bool theFlushProviders = false) const;

    //! Returns true if the property table is empty.
    __CADEX_EXPORT bool IsEmpty() const;

    //! Returns the number of added properties.
    __CADEX_EXPORT size_t Size() const;

    //! Discards associated data.
    /*! Providers which have been added with their deleters will be deleted.*/
    __CADEX_EXPORT void Clear();


    class Visitor
    {
    public:
        typedef const Base_UTF16String&
            PropertyNameConstReference;
        typedef ModelData_PropertyTable::TimeType TimeType;

        __CADEX_EXPORT virtual ~Visitor();
        virtual void operator() (const Base_UTF16String& theName, I32 theValue) = 0;
        virtual void operator() (const Base_UTF16String& theName, I64 theValue) = 0;
        virtual void operator() (const Base_UTF16String& theName, float theValue) = 0;
        virtual void operator() (const Base_UTF16String& theName, double theValue) = 0;
        virtual void operator() (const Base_UTF16String& theName, TimeType theValue) = 0;
        virtual void operator() (const Base_UTF16String& theName, const Base_UTF16String& theValue) = 0;
        virtual void operator() (const Base_UTF16String& theName, const ModelData_Point& theValue) = 0;
        virtual void operator() (const Base_UTF16String& theName, const ModelData_Box& theValue) = 0;
    };

    //! Accepts the visitor.
    /*! The order of visiting will match the order of adding properties with Add().

        If there providers added with AddProvider() then they will be flushed before starting
        visiting.
    */
    __CADEX_EXPORT void Accept (Visitor& theVisitor) const;



    // Predefined property names.

    //! Returns a key to designate a 'name' property.
    /*! Returns "Name". This value can be used by different algorithms to recognize this
        predefined property and distinguish it from others. For example, the JT exporter
        will use this property to set entity names in the Logical Scene Graph.
    */
    __CADEX_EXPORT static const Base_UTF16String& NamePropertyName();

    //! Returns a key to designate a 'surface area' validation property.
    /*! Returns "CADEX_SURFACE_AREA". The JT exporter will use this property to attach
        CAD_SURFACE_AREA to an entity in the Logical Scene Graph.
    */
    __CADEX_EXPORT static const Base_UTF16String& SurfaceAreaPropertyName();

    //! Returns a key to designate a 'volume' validation property.
    /*! Returns "CADEX_VOLUME". The JT exporter will use this property to attach
        CAD_VOLUME to an entity in the Logical Scene Graph.
    */
    __CADEX_EXPORT static const Base_UTF16String& VolumePropertyName();

    //! Returns a key to designate a 'centroid' validation property.
    /*! Returns "CADEX_CENTROID". The JT exporter will use this property to attach
        CAD_CENTER_OF_GRAVITY to an entity in the Logical Scene Graph.
    */
    __CADEX_EXPORT static const Base_UTF16String& CentroidPropertyName();

    //! Returns a key to designate a 'bounding box' property.
    /*! Returns "CADEX_BOUNDING_BOX".*/
    __CADEX_EXPORT static const Base_UTF16String& BoundingBoxPropertyName();

    //! Returns a key to designate a 'external filename' validation property.
    /*! Returns "CADEX_EXTERNAL_FILENAME". This value can be used by readers to store
        absolute source file paths for SGE in imported models with external references.
        Also this value can be set by PartSaver and stores relative path to the external file.
    */
    __CADEX_EXPORT static const Base_UTF16String& ExternalFilenamePropertyName();

    //__CADEX_EXPORT bool FindNameProperty (const Base_UTF16String& theName) const;

    //TODO - add Find* for validation properties

    // Returns true if property with name "theName" was found and false otherwise.
    __CADEX_EXPORT bool FindProperty (const Base_UTF16String& theName, I32& theValue,
        bool theFlushProviders = false) const;

    __CADEX_EXPORT bool FindProperty (const Base_UTF16String& theName, I64& theValue,
        bool theFlushProviders = false) const;

    __CADEX_EXPORT bool FindProperty (const Base_UTF16String& theName, float& theValue,
        bool theFlushProviders = false) const;

    __CADEX_EXPORT bool FindProperty (const Base_UTF16String& theName, double& theValue,
        bool theFlushProviders = false) const;

    __CADEX_EXPORT bool FindProperty (const Base_UTF16String& theName, TimeType& theValue,
        bool theFlushProviders = false) const;

    __CADEX_EXPORT bool FindProperty (const Base_UTF16String& theName, Base_UTF16String& theValue,
        bool theFlushProviders = false) const;

    __CADEX_EXPORT bool FindProperty (const Base_UTF16String& theName, ModelData_Point& theValue,
        bool theFlushProviders = false) const;

    __CADEX_EXPORT bool FindProperty (const Base_UTF16String& theName, ModelData_Box& theValue,
        bool theFlushProviders = false) const;

    __CADEX_EXPORT bool Remove (const Base_UTF16String& theName, bool theFlushProviders = false);

public:

    class VoidVisitor : public Visitor
    {
    public:
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            I32 theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            I64 theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            float theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            double theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            TimeType theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            const Base_UTF16String& theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            const ModelData_Point& theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            const ModelData_Box& theValue) override;
    };

    /*! \internal
        \class CombinedVisitor
        \brief Provides combined method Visit() to visit all properties.

        All individual operator() methods call the method Visit().

        This is a convenience class allowing to redefine a single method Visit() in the
        subclasses.
    */
    class CombinedVisitor : public Visitor
    {
    public:
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            I32 theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            I64 theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            float theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            double theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            TimeType theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            const Base_UTF16String& theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            const ModelData_Point& theValue) override;
        __CADEX_EXPORT virtual void operator() (const Base_UTF16String& theName,
            const ModelData_Box& theValue) override;
        virtual void Visit (const Base_UTF16String& theName) = 0;
    };

private:
    __CADEX_EXPORT ModelData_PropertyTable (const internal::ModelData_PropertyTableImpl* theImpl);
    friend class internal::ModelData_PropertyTableImpl;
};

}

#endif

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


#ifndef _ModelData_Model_HeaderFile
#define _ModelData_Model_HeaderFile

#include <cadex/Base_Handle.hxx>
#include <cadex/Base_ProgressStatus.hxx>
#include <cadex/Base_UTF16String.hxx>

namespace cadex {

class ModelData_Assembly;
class ModelData_Instance;
class ModelData_Layer;
class ModelData_WriterParameters;
class ModelData_Part;
class ModelData_SceneGraphElement;

namespace internal {
class ModelData_ModelImpl;
}

class ModelData_Model
{
public:

    enum FileFormatType {
        Xml,
        Binary
    };

    __CADEX_EXPORT ModelData_Model (const Base_UTF16String& theName = Base_UTF16String());

    __CADEX_EXPORT ~ModelData_Model();

    //! Adds all roots of another model to the current model
    __CADEX_EXPORT void Merge (const ModelData_Model& theSrcModel,
        const Base_ProgressStatus& theProgressStatus = Base_ProgressStatus());

    __CADEX_EXPORT void SetName (const Base_UTF16String& theName);

    __CADEX_EXPORT const Base_UTF16String& Name() const;

    __CADEX_EXPORT bool Open (const Base_UTF16String& theFileName,
        bool theToAppend = false,
        const Base_ProgressStatus& theProgressStatus = Base_ProgressStatus());

    __CADEX_EXPORT bool Save (const Base_UTF16String& theFileName,
        FileFormatType theFormat = Xml,
        const Base_ProgressStatus& theProgressStatus = Base_ProgressStatus()) const;

    __CADEX_EXPORT bool Save (const Base_UTF16String& theFileName,
        const ModelData_WriterParameters& theParameters,
        const Base_ProgressStatus& theProgressStatus = Base_ProgressStatus()) const;

    __CADEX_EXPORT void Clear();

    __CADEX_EXPORT bool IsEmpty() const;

    __CADEX_EXPORT void AssignUuids();

    // Element graph

    __CADEX_EXPORT const ModelData_SceneGraphElement& AddRoot (const ModelData_SceneGraphElement& theElement);

    __CADEX_EXPORT bool RemoveRoot (const ModelData_SceneGraphElement& theElement);

    __CADEX_EXPORT size_t NumberOfRoots() const;


    __CADEX_EXPORT void AddLayer (const ModelData_Layer& theLayer);

    class ElementVisitor
    {
    public:
        __CADEX_EXPORT virtual ~ElementVisitor();
        virtual void operator() (const ModelData_Part& thePart) = 0;
        virtual bool VisitEnter (const ModelData_Assembly& theAssembly) = 0;
        virtual void VisitLeave (const ModelData_Assembly& theAssembly) = 0;
        virtual bool VisitEnter (const ModelData_Instance& theInstance) = 0;
        virtual void VisitLeave (const ModelData_Instance& theInstance) = 0;
    };

    class VoidElementVisitor : public ElementVisitor
    {
    public:
        __CADEX_EXPORT virtual void operator() (const ModelData_Part& thePart);
        __CADEX_EXPORT virtual bool VisitEnter (const ModelData_Assembly& theAssembly);
        __CADEX_EXPORT virtual void VisitLeave (const ModelData_Assembly& theAssembly);
        __CADEX_EXPORT virtual bool VisitEnter (const ModelData_Instance& theInstance);
        __CADEX_EXPORT virtual void VisitLeave (const ModelData_Instance& theInstance);
    };

    class CombinedElementVisitor : public ElementVisitor
    {
    public:
        __CADEX_EXPORT virtual void operator() (const ModelData_Part& thePart);
        __CADEX_EXPORT virtual bool VisitEnter (const ModelData_Assembly& theAssembly);
        __CADEX_EXPORT virtual void VisitLeave (const ModelData_Assembly& theAssembly);
        __CADEX_EXPORT virtual bool VisitEnter (const ModelData_Instance& theInstance);
        __CADEX_EXPORT virtual void VisitLeave (const ModelData_Instance& theInstance);

        virtual bool VisitEnter (const ModelData_SceneGraphElement& theElement) = 0;
        __CADEX_EXPORT virtual void VisitLeave (const ModelData_SceneGraphElement& theElement);
    };

    __CADEX_EXPORT void Accept (ElementVisitor& theVisitor) const;

    class ElementIterator
    {
    public:
        //! Constructor.
        /*! Creates an iterator over graph roots.*/
        __CADEX_EXPORT ElementIterator (const ModelData_Model& theModel);
        __CADEX_EXPORT ElementIterator (const ModelData_SceneGraphElement& theElement);
        __CADEX_EXPORT ElementIterator (const ModelData_Layer& theLayer);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_SceneGraphElement& Next() const;
        __CADEX_EXPORT ModelData_SceneGraphElement& Next();
    protected:
        internal::Base_Handle myImpl;
    };

    class LayerIterator
    {
    public:
        __CADEX_EXPORT LayerIterator (const ModelData_Model& theModel);
        __CADEX_EXPORT bool HasNext() const;
        __CADEX_EXPORT const ModelData_Layer& Next() const;
        __CADEX_EXPORT ModelData_Layer& Next();
    protected:
        internal::Base_Handle myImpl;
    };

    class LayerVisitor
    {
    public:
        __CADEX_EXPORT virtual ~LayerVisitor();
        virtual void operator() (const ModelData_Layer& theLayer) = 0;
    };

    __CADEX_EXPORT void Accept (LayerVisitor& theVisitor) const;

    __CADEX_EXPORT internal::ModelData_ModelImpl* Impl() const;

private:

    __CADEX_EXPORT ModelData_Model (internal::ModelData_ModelImpl* theImpl);

    internal::Base_Handle myImpl;

    friend class internal::ModelData_ModelImpl;
};

}

#if __CADEX_SDK_BUILD && !defined(__CADEX_SDK_NO_IMPLICIT_LINKAGE)
#define __CADEX_SDK_NO_IMPLICIT_LINKAGE 1
#endif

#if _MSC_VER
    #if !__CADEX_SDK_NO_IMPLICIT_LINKAGE
        #ifdef _DEBUG
            #pragma comment(lib, "CadExCored.lib")
        #else
            #pragma comment(lib, "CadExCore.lib")
        #endif
    #endif
#endif

#endif

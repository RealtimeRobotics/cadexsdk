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


#ifndef _ModelCheck_BRepChecker_HeaderFile
#define _ModelCheck_BRepChecker_HeaderFile

#include <cadex/Base_Macro.hxx>
#include <cadex/Base_ProgressStatus.hxx>
#include <cadex/Base_Templates.hxx>
#include <cadex/ModelCheck_BaseProblem.hxx>
#include <cadex/ModelCheck_ErrorLevel.hxx>
#include <cadex/ModelCheck_Continuity.hxx>
#include <cadex/ModelCheck_ProblemType.hxx>


class TopoDS_Shape;

namespace cadex {
namespace internal {
class ModelCheck_BRepCheckerImpl;
class ModelCheck_BRepCheckerOptionsImpl;
}

class Base_String;

class ModelCheck_BRepChecker
{
public:

    __CADEX_DEFINE_MEMORY_MANAGEMENT

    struct Tool {
    enum
    {
        Continuity   = 1 << 0,
        Intersection = 1 << 1,
        Overlap      = 1 << 2,
        Size         = 1 << 3,
        Tolerance    = 1 << 4,
        Topology     = 1 << 5,

        All = Continuity | Intersection | Overlap | Size | Tolerance | Topology
    };
    typedef int    FlagType;
    };

    class Options
    {
    public:

        __CADEX_DEFINE_MEMORY_MANAGEMENT

        enum ModeEnum
        {
            Coarse,
            Moderate,
            Fine
        };

        //! Constructor.
        __CADEX_EXPORT Options();

        //! Loads options from file.
        __CADEX_EXPORT bool LoadFromFile (const Base_String& theFile);

        //! Sets a preset mode.
        __CADEX_EXPORT Options& Mode (ModeEnum theMode);

        //! Sets which tools will be used by checker.
        __CADEX_EXPORT Options& Tools (Tool::FlagType theTools);
        //! Returns tools flag.
        __CADEX_EXPORT Tool::FlagType Tools() const;

        //! Sets target surface continuity for Tool::Continuity.
        __CADEX_EXPORT Options& SurfaceContinuity (ModelCheck_Continuity theSurfaceContinuity);
        //! Returns target surface continuity for Tool::Continuity.
        __CADEX_EXPORT ModelCheck_Continuity SurfaceContinuity() const;

        //! Sets target curve continuity for Tool::Continuity.
        __CADEX_EXPORT Options& CurveContinuity (ModelCheck_Continuity theCurveContinuity);
        //! Returns target curve continuity for Tool::Continuity.
        __CADEX_EXPORT ModelCheck_Continuity CurveContinuity() const;

        //! Sets number of control points for Tool::Overlap.
        __CADEX_EXPORT Options& OverlapControlPoints (size_t OverlapControlPoints);
        //! Returns number of control points for Tool::Overlap.
        __CADEX_EXPORT size_t OverlapControlPoints() const;

        //! Sets allowed overlap for Tool::Overlap.
        __CADEX_EXPORT Options& AllowedOverlap (double theAllowedOverlap);
        //! Returns allowed overlap for Tool::Overlap.
        __CADEX_EXPORT double AllowedOverlap() const;

        //! Sets target wire bounding box diagonal length for Tool::Size.
        __CADEX_EXPORT Options& WireBBoxDiagLength (double WireBBoxDiagLength);
        //! Returns target wire bounding box diagonal length for Tool::Size.
        __CADEX_EXPORT double WireBBoxDiagLength() const;

        //! Sets target edge bounding box diagonal length for Tool::Size.
        __CADEX_EXPORT Options& EdgeBBoxDiagLength (double EdgeBBoxDiagLength);
        //! Returns target edge bounding box diagonal length for Tool::Size.
        __CADEX_EXPORT double EdgeBBoxDiagLength() const;

        //! Sets number of control points for Tool::Tolerance.
        __CADEX_EXPORT Options& ToleranceControlPoints (size_t ToleranceControlPoints);
        //! Returns number of control points for Tool::Tolerance.
        __CADEX_EXPORT size_t ToleranceControlPoints() const;

        //! Sets tolerance threshold for Tool::Tolerance.
        __CADEX_EXPORT Options& ToleranceThreshold (double ToleranceThreshold);
        //! Returns tolerance threshold for Tool::Tolerance.
        __CADEX_EXPORT double ToleranceThreshold() const;

        //! Sets "use same parameter" flag for Tool::Tolerance.
        __CADEX_EXPORT Options& UseSameParam (bool UseSameParam);
        //! Returns "use same parameter" flag for Tool::Tolerance.
        __CADEX_EXPORT bool UseSameParam() const;

        __CADEX_DEFINE_IMPL (ModelCheck_BRepCheckerOptions)
    };
    typedef Options    OptionsType;

    typedef cadex::internal::cadex_vector <std::shared_ptr <ModelCheck_BaseProblem> >::type    ProblemsContainerType;
    typedef cadex::internal::cadex_vector <TopoDS_Shape>::type                                 ShapesContainerType;

    typedef std::pair <TopoDS_Shape, std::shared_ptr <ModelCheck_BaseProblem> >                     ShapeWithProblemType;
    typedef cadex::internal::cadex_multimap <ModelCheck_ProblemType, ShapeWithProblemType>::type    ProbTypeShapesMapType;

    //! Constructor.
    __CADEX_EXPORT ModelCheck_BRepChecker();

    //! Constructor.
    __CADEX_EXPORT ModelCheck_BRepChecker (const OptionsType& theOptions);

    //! Returns an internal Options object.
    __CADEX_EXPORT OptionsType& SetOptions();

    //! Sets an Options object.
    __CADEX_EXPORT void SetOptions (const OptionsType& theOptions);

    //! Returns an internal Options object.
    __CADEX_EXPORT const OptionsType& Options() const;

    //! Performs check on the given shape.
    __CADEX_EXPORT bool Check (const TopoDS_Shape& theShape);

    //! Returns \c true if last checked shape has problems and \c false otherwise.
    __CADEX_EXPORT bool HasProblems() const;

    //! Returns all subshapes which has problems.
    __CADEX_EXPORT ShapesContainerType ProblematicShapes() const;

    //! Returns problems of the given subshape.
    __CADEX_EXPORT const ProblemsContainerType& Problems (const TopoDS_Shape& theShape) const;

    //! Returns problems of the given level.
    __CADEX_EXPORT const ProbTypeShapesMapType& Problems (ModelCheck_ErrorLevel theLevel) const;

    //! Returns number of problems for the given subshape.
    __CADEX_EXPORT size_t NumberOfProblems (const TopoDS_Shape& theShape) const;

    //! Returns number of problems for the given level.
    __CADEX_EXPORT size_t NumberOfProblems (ModelCheck_ErrorLevel theLevel) const;

    //! Returns the last checked shape.
    __CADEX_EXPORT const TopoDS_Shape& Shape() const;

    //! Returns the ID of subshape.
    __CADEX_EXPORT size_t FindID (const TopoDS_Shape& theShape) const;

    //! Returns the shape with given ID.
    __CADEX_EXPORT const TopoDS_Shape& FindShape (size_t theID) const;
    
    //! Returns progress status.
    __CADEX_EXPORT const Base_ProgressStatus& ProgressStatus() const;

    //! Returns progress status.
    __CADEX_EXPORT Base_ProgressStatus& ProgressStatus();

    __CADEX_DEFINE_IMPL (ModelCheck_BRepChecker)
};

}

#endif

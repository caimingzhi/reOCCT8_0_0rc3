#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Contap_TheSegmentOfTheSearch.hpp>
#include <NCollection_Sequence.hpp>
#include <Contap_ThePathPointOfTheSearch.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
class StdFail_NotDone;
class Standard_OutOfRange;
class Standard_ConstructionError;
class Adaptor3d_HVertex;
class Contap_HCurve2dTool;
class Contap_HContTool;
class Adaptor3d_TopolTool;
class Contap_ArcFunction;
class Contap_ThePathPointOfTheSearch;
class Contap_TheSegmentOfTheSearch;

class Contap_TheSearch
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT Contap_TheSearch();

  //! Algorithm to find the points and parts of curves of Domain
  //! (domain of of restriction of a surface) which verify
  //! F = 0.
  //! TolBoundary defines if a curve is on Q.
  //! TolTangency defines if a point is on Q.
  Standard_EXPORT void Perform(Contap_ArcFunction&                     F,
                               const occ::handle<Adaptor3d_TopolTool>& Domain,
                               const double                            TolBoundary,
                               const double                            TolTangency,
                               const bool                              RecheckOnRegularity = false);

  //! Returns True if the calculus was successful.
  bool IsDone() const;

  //! Returns true if all arc of the Arcs are solution (inside
  //! the surface).
  //! An exception is raised if IsDone returns False.
  bool AllArcSolution() const;

  //! Returns the number of resulting points.
  //! An exception is raised if IsDone returns False (NotDone).
  int NbPoints() const;

  //! Returns the resulting point of range Index.
  //! The exception NotDone is raised if IsDone() returns
  //! False.
  //! The exception OutOfRange is raised if
  //! Index <= 0 or Index > NbPoints.
  const Contap_ThePathPointOfTheSearch& Point(const int Index) const;

  //! Returns the number of the resulting segments.
  //! An exception is raised if IsDone returns False (NotDone).
  int NbSegments() const;

  //! Returns the resulting segment of range Index.
  //! The exception NotDone is raised if IsDone() returns
  //! False.
  //! The exception OutOfRange is raised if
  //! Index <= 0 or Index > NbPoints.
  const Contap_TheSegmentOfTheSearch& Segment(const int Index) const;

private:
  bool                                                 done;
  bool                                                 all;
  NCollection_Sequence<Contap_TheSegmentOfTheSearch>   sseg;
  NCollection_Sequence<Contap_ThePathPointOfTheSearch> spnt;
};

#define TheVertex occ::handle<Adaptor3d_HVertex>
#define TheVertex_hxx <Adaptor3d_HVertex.hpp>
#define TheArc occ::handle<Adaptor2d_Curve2d>
#define TheArc_hxx <Adaptor2d_Curve2d.hpp>
#define TheArcTool Contap_HCurve2dTool
#define TheArcTool_hxx <Contap_HCurve2dTool.hpp>
#define TheSOBTool Contap_HContTool
#define TheSOBTool_hxx <Contap_HContTool.hpp>
#define Handle_TheTopolTool occ::handle<Adaptor3d_TopolTool>
#define TheTopolTool Adaptor3d_TopolTool
#define TheTopolTool_hxx <Adaptor3d_TopolTool.hpp>
#define TheFunction Contap_ArcFunction
#define TheFunction_hxx <Contap_ArcFunction.hpp>
#define IntStart_ThePathPoint Contap_ThePathPointOfTheSearch
#define IntStart_ThePathPoint_hxx <Contap_ThePathPointOfTheSearch.hpp>
#define IntStart_SequenceOfPathPoint NCollection_Sequence<Contap_ThePathPointOfTheSearch>
#define IntStart_SequenceOfPathPoint_hxx <NCollection_Sequence<Contap_ThePathPointOfTheSearch>.hxx>
#define IntStart_TheSegment Contap_TheSegmentOfTheSearch
#define IntStart_TheSegment_hxx <Contap_TheSegmentOfTheSearch.hpp>
#define IntStart_SequenceOfSegment NCollection_Sequence<Contap_TheSegmentOfTheSearch>
#define IntStart_SequenceOfSegment_hxx <NCollection_Sequence<Contap_TheSegmentOfTheSearch>.hxx>
#define IntStart_SearchOnBoundaries Contap_TheSearch
#define IntStart_SearchOnBoundaries_hxx <Contap_TheSearch.hpp>

#include <IntStart_SearchOnBoundaries_1.hpp>

#undef TheVertex
#undef TheVertex_hxx
#undef TheArc
#undef TheArc_hxx
#undef TheArcTool
#undef TheArcTool_hxx
#undef TheSOBTool
#undef TheSOBTool_hxx
#undef Handle_TheTopolTool
#undef TheTopolTool
#undef TheTopolTool_hxx
#undef TheFunction
#undef TheFunction_hxx
#undef IntStart_ThePathPoint
#undef IntStart_ThePathPoint_hxx
#undef IntStart_SequenceOfPathPoint
#undef IntStart_SequenceOfPathPoint_hxx
#undef IntStart_TheSegment
#undef IntStart_TheSegment_hxx
#undef IntStart_SequenceOfSegment
#undef IntStart_SequenceOfSegment_hxx
#undef IntStart_SearchOnBoundaries
#undef IntStart_SearchOnBoundaries_hxx


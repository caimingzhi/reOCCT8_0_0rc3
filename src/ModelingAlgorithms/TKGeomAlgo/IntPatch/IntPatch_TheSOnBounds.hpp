#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntPatch_TheSegmentOfTheSOnBounds.hpp>
#include <NCollection_Sequence.hpp>
#include <IntPatch_ThePathPointOfTheSOnBounds.hpp>
#include <Standard_Integer.hpp>
class StdFail_NotDone;
class Standard_OutOfRange;
class Standard_ConstructionError;
class Adaptor3d_HVertex;
class IntPatch_HCurve2dTool;
class IntPatch_HInterTool;
class Adaptor3d_TopolTool;
class IntPatch_ArcFunction;
class IntPatch_ThePathPointOfTheSOnBounds;
class IntPatch_TheSegmentOfTheSOnBounds;

class IntPatch_TheSOnBounds
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT IntPatch_TheSOnBounds();

  //! Algorithm to find the points and parts of curves of Domain
  //! (domain of of restriction of a surface) which verify
  //! F = 0.
  //! TolBoundary defines if a curve is on Q.
  //! TolTangency defines if a point is on Q.
  Standard_EXPORT void Perform(IntPatch_ArcFunction&                   F,
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
  const IntPatch_ThePathPointOfTheSOnBounds& Point(const int Index) const;

  //! Returns the number of the resulting segments.
  //! An exception is raised if IsDone returns False (NotDone).
  int NbSegments() const;

  //! Returns the resulting segment of range Index.
  //! The exception NotDone is raised if IsDone() returns
  //! False.
  //! The exception OutOfRange is raised if
  //! Index <= 0 or Index > NbPoints.
  const IntPatch_TheSegmentOfTheSOnBounds& Segment(const int Index) const;

private:
  bool                                                      done;
  bool                                                      all;
  NCollection_Sequence<IntPatch_TheSegmentOfTheSOnBounds>   sseg;
  NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds> spnt;
};

#define TheVertex occ::handle<Adaptor3d_HVertex>
#define TheVertex_hxx <Adaptor3d_HVertex.hpp>
#define TheArc occ::handle<Adaptor2d_Curve2d>
#define TheArc_hxx <Adaptor2d_Curve2d.hpp>
#define TheArcTool IntPatch_HCurve2dTool
#define TheArcTool_hxx <IntPatch_HCurve2dTool.hpp>
#define TheSOBTool IntPatch_HInterTool
#define TheSOBTool_hxx <IntPatch_HInterTool.hpp>
#define Handle_TheTopolTool occ::handle<Adaptor3d_TopolTool>
#define TheTopolTool Adaptor3d_TopolTool
#define TheTopolTool_hxx <Adaptor3d_TopolTool.hpp>
#define TheFunction IntPatch_ArcFunction
#define TheFunction_hxx <IntPatch_ArcFunction.hpp>
#define IntStart_ThePathPoint IntPatch_ThePathPointOfTheSOnBounds
#define IntStart_ThePathPoint_hxx <IntPatch_ThePathPointOfTheSOnBounds.hpp>
#define IntStart_SequenceOfPathPoint NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>
#define IntStart_SequenceOfPathPoint_hxx                                                           \
  <NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>.hxx>
#define IntStart_TheSegment IntPatch_TheSegmentOfTheSOnBounds
#define IntStart_TheSegment_hxx <IntPatch_TheSegmentOfTheSOnBounds.hpp>
#define IntStart_SequenceOfSegment NCollection_Sequence<IntPatch_TheSegmentOfTheSOnBounds>
#define IntStart_SequenceOfSegment_hxx                                                             \
  <NCollection_Sequence<IntPatch_TheSegmentOfTheSOnBounds>.hxx>
#define IntStart_SearchOnBoundaries IntPatch_TheSOnBounds
#define IntStart_SearchOnBoundaries_hxx <IntPatch_TheSOnBounds.hpp>

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


#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>
class TopOpeBRepDS_Transition;
class TopOpeBRep_VPointInter;
class TopOpeBRep_LineInter;
class TopoDS_Shape;

class TopOpeBRep_FFTransitionTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopOpeBRepDS_Transition ProcessLineTransition(
    const TopOpeBRep_VPointInter& P,
    const int                     Index,
    const TopAbs_Orientation      EdgeOrientation);

  Standard_EXPORT static TopOpeBRepDS_Transition ProcessLineTransition(
    const TopOpeBRep_VPointInter& P,
    const TopOpeBRep_LineInter&   L);

  Standard_EXPORT static TopOpeBRepDS_Transition ProcessEdgeTransition(
    const TopOpeBRep_VPointInter& P,
    const int                     Index,
    const TopAbs_Orientation      LineOrientation);

  Standard_EXPORT static TopOpeBRepDS_Transition ProcessFaceTransition(
    const TopOpeBRep_LineInter& L,
    const int                   Index,
    const TopAbs_Orientation    FaceOrientation);

  //! compute transition on "IntPatch_Restriction line" edge <R>
  //! when crossing edge <E> of face <F> at point <VP>.
  //! VP is given on edge <E> of face <F> of index <Index> (1 or 2).
  //! <VP> has been classified by FacesFiller as TopAbs_ON an edge <R>
  //! of the other face than <F> of current (face/face) intersection.
  //! Transition depends on the orientation of E in F.
  //! This method should be provided by IntPatch_Line (NYI)
  Standard_EXPORT static TopOpeBRepDS_Transition ProcessEdgeONTransition(
    const TopOpeBRep_VPointInter& VP,
    const int                     Index,
    const TopoDS_Shape&           R,
    const TopoDS_Shape&           E,
    const TopoDS_Shape&           F);
};


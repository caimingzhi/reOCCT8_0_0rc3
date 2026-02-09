#pragma once

#include <IntPatch_Line.hpp>
#include <NCollection_Sequence.hpp>
#include <IntPatch_WLine.hpp>
#include <NCollection_List.hpp>

class Adaptor3d_TopolTool;

class IntPatch_WLineTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<IntPatch_WLine> ComputePurgedWLine(
    const occ::handle<IntPatch_WLine>&      theWLine,
    const occ::handle<Adaptor3d_Surface>&   theS1,
    const occ::handle<Adaptor3d_Surface>&   theS2,
    const occ::handle<Adaptor3d_TopolTool>& theDom1,
    const occ::handle<Adaptor3d_TopolTool>& theDom2);

  Standard_EXPORT static void JoinWLines(NCollection_Sequence<occ::handle<IntPatch_Line>>& theSlin,
                                         NCollection_Sequence<IntPatch_Point>&             theSPnt,
                                         const occ::handle<Adaptor3d_Surface>&             theS1,
                                         const occ::handle<Adaptor3d_Surface>&             theS2,
                                         const double theTol3D);

  Standard_EXPORT static void ExtendTwoWLines(
    NCollection_Sequence<occ::handle<IntPatch_Line>>& theSlin,
    const occ::handle<Adaptor3d_Surface>&             theS1,
    const occ::handle<Adaptor3d_Surface>&             theS2,
    const double                                      theToler3D,
    const double* const                               theArrPeriods,
    const Bnd_Box2d&                                  theBoxS1,
    const Bnd_Box2d&                                  theBoxS2,
    const NCollection_List<gp_Pnt>&                   theListOfCriticalPoints);

  static const double myMaxConcatAngle;
};

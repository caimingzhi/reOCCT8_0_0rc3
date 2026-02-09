#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class TCollection_ExtendedString;
class gp_Pnt;
class gp_Dir;
class Geom_TrimmedCurve;

class DsgPrs_FilletRadiusPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const double                           thevalue,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          aPosition,
                                  const gp_Dir&                          aNormalDir,
                                  const gp_Pnt&                          aBasePnt,
                                  const gp_Pnt&                          aFirstPoint,
                                  const gp_Pnt&                          aSecondPoint,
                                  const gp_Pnt&                          aCenter,
                                  const DsgPrs_ArrowSide                 ArrowPrs,
                                  const bool                             drawRevers,
                                  gp_Pnt&                                DrawPosition,
                                  gp_Pnt&                                EndOfArrow,
                                  occ::handle<Geom_TrimmedCurve>&        TrimCurve,
                                  bool&                                  HasCircle);
};

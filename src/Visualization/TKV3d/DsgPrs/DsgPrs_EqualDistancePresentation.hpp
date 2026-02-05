#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Drawer.hpp>
#include <DsgPrs_ArrowSide.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class Geom_Plane;
class gp_Dir;
class gp_Circ;

//! A framework to display equal distances between shapes and a given plane.
//! The distance is the length of a projection from the shape to the plane.
//! These distances are used to compare two shapes by this vector alone.
class DsgPrs_EqualDistancePresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the points Point1, Point2, Point3 Point4, and the
  //! plane Plane to the presentation object aPresentation.
  //! The display attributes of these elements is defined by the attribute manager aDrawer.
  //! The distance is the length of a projection from the shape to the plane.
  //! These distances are used to compare two shapes by this vector alone.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          Point1,
                                  const gp_Pnt&                          Point2,
                                  const gp_Pnt&                          Point3,
                                  const gp_Pnt&                          Point4,
                                  const occ::handle<Geom_Plane>&         Plane);

  //! is used for presentation of interval between
  //! two lines or two points or between a line and a point.
  Standard_EXPORT static void AddInterval(const occ::handle<Prs3d_Presentation>& aPresentation,
                                          const occ::handle<Prs3d_Drawer>&       aDrawer,
                                          const gp_Pnt&                          aPoint1,
                                          const gp_Pnt&                          aPoint2,
                                          const gp_Dir&                          aDir,
                                          const gp_Pnt&                          aPosition,
                                          const DsgPrs_ArrowSide                 anArrowSide,
                                          gp_Pnt&                                anExtremePnt1,
                                          gp_Pnt&                                anExtremePnt2);

  //! is used for presentation of interval between two arcs.
  //! One of arcs can have a zero radius.
  Standard_EXPORT static void AddIntervalBetweenTwoArcs(
    const occ::handle<Prs3d_Presentation>& aPresentation,
    const occ::handle<Prs3d_Drawer>&       aDrawer,
    const gp_Circ&                         aCircle1,
    const gp_Circ&                         aCircle2,
    const gp_Pnt&                          aPoint1,
    const gp_Pnt&                          aPoint2,
    const gp_Pnt&                          aPoint3,
    const gp_Pnt&                          aPoint4,
    const DsgPrs_ArrowSide                 anArrowSide);
};

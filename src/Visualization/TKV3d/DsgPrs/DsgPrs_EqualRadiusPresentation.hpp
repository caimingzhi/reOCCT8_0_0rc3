#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class Geom_Plane;

//! A framework to define display of equality in radii.
class DsgPrs_EqualRadiusPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the points FirstCenter, SecondCenter,
  //! FirstPoint, SecondPoint, and the plane Plane to the
  //! presentation object aPresentation.
  //! The display attributes of these elements is defined by
  //! the attribute manager aDrawer.
  //! FirstCenter and SecondCenter are the centers of the
  //! first and second shapes respectively, and FirstPoint
  //! and SecondPoint are the attachment points of the radii to arcs.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          FirstCenter,
                                  const gp_Pnt&                          SecondCenter,
                                  const gp_Pnt&                          FirstPoint,
                                  const gp_Pnt&                          SecondPoint,
                                  const occ::handle<Geom_Plane>&         Plane);
};

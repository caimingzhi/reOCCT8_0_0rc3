#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class Geom_Plane;

class DsgPrs_EqualRadiusPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          FirstCenter,
                                  const gp_Pnt&                          SecondCenter,
                                  const gp_Pnt&                          FirstPoint,
                                  const gp_Pnt&                          SecondPoint,
                                  const occ::handle<Geom_Plane>&         Plane);
};

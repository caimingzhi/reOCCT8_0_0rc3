#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;

//! A framework for displaying the planes of an XYZ trihedron.
class DsgPrs_XYZPlanePresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Draws each plane of a trihedron displayed in the
  //! presentation aPresentation and with attributes
  //! defined by the attribute manager aDrawer. Each
  //! triangular plane is defined by the points aPt1 aPt2 and aPt3.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          aPt1,
                                  const gp_Pnt&                          aPt2,
                                  const gp_Pnt&                          aPt3);
};

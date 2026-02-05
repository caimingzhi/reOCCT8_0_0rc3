#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>

//! Computes the wireframe presentation of surfaces
//! by displaying a given number of U and/or V isoparametric
//! curves. The isoparametric curves are drawn with respect
//! to a given number of points.
class StdPrs_WFSurface : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Draws a surface by drawing the isoparametric curves with respect to
  //! a fixed number of points given by the Drawer.
  //! The number of isoparametric curves to be drawn and their color are
  //! controlled by the furnished Drawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Adaptor3d_Surface>&  aSurface,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer);
};

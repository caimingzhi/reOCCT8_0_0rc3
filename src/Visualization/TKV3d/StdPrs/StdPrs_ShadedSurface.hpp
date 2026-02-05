#pragma once

#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>

class Adaptor3d_Surface;

//! Computes the shading presentation of surfaces.
//! Draws a surface by drawing the isoparametric curves with respect to
//! a maximal chordial deviation.
//! The number of isoparametric curves to be drawn and their color are
//! controlled by the furnished Drawer.
class StdPrs_ShadedSurface : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the surface aSurface to the presentation object aPresentation.
  //! The surface's display attributes are set in the attribute manager aDrawer.
  //! The surface object from Adaptor3d provides data
  //! from a Geom surface in order to use the surface in an algorithm.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const Adaptor3d_Surface&               aSurface,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer);
};

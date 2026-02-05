#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>

//! Draws a surface by drawing the isoparametric curves with respect to
//! a maximal chordial deviation.
//! The number of isoparametric curves to be drawn and their color are
//! controlled by the furnished Drawer.
class StdPrs_WFDeflectionSurface : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the surface aSurface to the presentation object
  //! aPresentation, and defines its boundaries and isoparameters.
  //! The shape's display attributes are set in the attribute
  //! manager aDrawer. These include whether deflection
  //! is absolute or relative to the size of the shape.
  //! The surface aSurface is a surface object from
  //! Adaptor, and provides data from a Geom surface.
  //! This makes it possible to use the surface in a geometric algorithm.
  //! Note that this surface object is manipulated by handles.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Adaptor3d_Surface>&  aSurface,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer);
};

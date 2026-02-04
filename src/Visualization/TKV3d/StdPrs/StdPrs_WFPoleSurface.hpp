#pragma once


#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>

class Adaptor3d_Surface;

//! Computes the presentation of surfaces by drawing a
//! double network of lines linking the poles of the surface
//! in the two parametric direction.
//! The number of lines to be drawn is controlled
//! by the NetworkNumber of the given Drawer.
class StdPrs_WFPoleSurface : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the surface aSurface to the presentation object aPresentation.
  //! The shape's display attributes are set in the attribute manager aDrawer.
  //! The surface aSurface is a surface object from
  //! Adaptor3d, and provides data from a Geom surface.
  //! This makes it possible to use the surface in a geometric algorithm.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const Adaptor3d_Surface&               aSurface,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer);
};


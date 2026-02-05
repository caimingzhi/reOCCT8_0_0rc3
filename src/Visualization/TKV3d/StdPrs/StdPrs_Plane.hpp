#pragma once

#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>

class Adaptor3d_Surface;

//! A framework to display infinite planes.
class StdPrs_Plane : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines display of infinite planes.
  //! The infinite plane aPlane is added to the display
  //! aPresentation, and the attributes of the display are
  //! defined by the attribute manager aDrawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const Adaptor3d_Surface&               aPlane,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer);

  //! returns true if the distance between the point (X,Y,Z) and the
  //! plane is less than aDistance.
  Standard_EXPORT static bool Match(const double                     X,
                                    const double                     Y,
                                    const double                     Z,
                                    const double                     aDistance,
                                    const Adaptor3d_Surface&         aPlane,
                                    const occ::handle<Prs3d_Drawer>& aDrawer);
};

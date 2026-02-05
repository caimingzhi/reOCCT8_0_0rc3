#pragma once

#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>

class Adaptor3d_Curve;

//! A framework to provide display of Bezier or BSpline curves
//! (by drawing a broken line linking the poles of the curve).
class StdPrs_PoleCurve : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines display of BSpline and Bezier curves.
  //! Adds the 3D curve aCurve to the
  //! StdPrs_PoleCurve algorithm. This shape is found in
  //! the presentation object aPresentation, and its display
  //! attributes are set in the attribute manager aDrawer.
  //! The curve object from Adaptor3d provides data from
  //! a Geom curve. This makes it possible to use the
  //! surface in a geometric algorithm.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const Adaptor3d_Curve&                 aCurve,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer);

  //! returns true if the distance between the point (X,Y,Z) and the
  //! broken line made of the poles is less then aDistance.
  Standard_EXPORT static bool Match(const double                     X,
                                    const double                     Y,
                                    const double                     Z,
                                    const double                     aDistance,
                                    const Adaptor3d_Curve&           aCurve,
                                    const occ::handle<Prs3d_Drawer>& aDrawer);

  //! returns the pole the most near of the point (X,Y,Z) and
  //! returns its range. The distance between the pole and
  //! (X,Y,Z) must be less then aDistance. If no pole corresponds, 0 is returned.
  Standard_EXPORT static int Pick(const double                     X,
                                  const double                     Y,
                                  const double                     Z,
                                  const double                     aDistance,
                                  const Adaptor3d_Curve&           aCurve,
                                  const occ::handle<Prs3d_Drawer>& aDrawer);
};

#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Ax2;
class gp_Pnt;
class gp_Circ;
class gp_Elips;

class DsgPrs_MidPointPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! draws the representation of a MidPoint between
  //! two vertices.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Ax2&                          theAxe,
                                  const gp_Pnt&                          MidPoint,
                                  const gp_Pnt&                          Position,
                                  const gp_Pnt&                          AttachPoint,
                                  const bool                             first);

  //! draws the representation of a MidPoint between
  //! two lines or linear segments.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Ax2&                          theAxe,
                                  const gp_Pnt&                          MidPoint,
                                  const gp_Pnt&                          Position,
                                  const gp_Pnt&                          AttachPoint,
                                  const gp_Pnt&                          Point1,
                                  const gp_Pnt&                          Point2,
                                  const bool                             first);

  //! draws the representation of a MidPoint between
  //! two entire circles or two circular arcs.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Circ&                         aCircle,
                                  const gp_Pnt&                          MidPoint,
                                  const gp_Pnt&                          Position,
                                  const gp_Pnt&                          AttachPoint,
                                  const gp_Pnt&                          Point1,
                                  const gp_Pnt&                          Point2,
                                  const bool                             first);

  //! draws the representation of a MidPoint between
  //! two entire ellipses or two elliptic arcs.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Elips&                        anElips,
                                  const gp_Pnt&                          MidPoint,
                                  const gp_Pnt&                          Position,
                                  const gp_Pnt&                          AttachPoint,
                                  const gp_Pnt&                          Point1,
                                  const gp_Pnt&                          Point2,
                                  const bool                             first);
};


#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;

//! A framework to define display of perpendicular
//! constraints between shapes.
class DsgPrs_PerpenPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines the display of elements showing
  //! perpendicular constraints between shapes.
  //! These include the two axis points pAx1 and pAx2,
  //! the two points pnt1 and pnt2, the offset point
  //! OffsetPoint and the two Booleans intOut1} and intOut2{.
  //! These arguments are added to the presentation
  //! object aPresentation. Their display attributes are
  //! defined by the attribute manager aDrawer.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          pAx1,
                                  const gp_Pnt&                          pAx2,
                                  const gp_Pnt&                          pnt1,
                                  const gp_Pnt&                          pnt2,
                                  const gp_Pnt&                          OffsetPoint,
                                  const bool                             intOut1,
                                  const bool                             intOut2);
};

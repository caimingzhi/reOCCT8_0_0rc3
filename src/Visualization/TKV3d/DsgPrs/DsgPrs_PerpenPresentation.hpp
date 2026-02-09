#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;

class DsgPrs_PerpenPresentation
{
public:
  DEFINE_STANDARD_ALLOC

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

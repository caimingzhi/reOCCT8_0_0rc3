#pragma once

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Root.hpp>

class DsgPrs_DatumPrs : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const gp_Ax2&                          theDatum,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer);
};

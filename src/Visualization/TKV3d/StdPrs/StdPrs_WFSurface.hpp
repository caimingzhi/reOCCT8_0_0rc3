#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Prs3d_Root.hpp>
#include <Prs3d_Drawer.hpp>

class StdPrs_WFSurface : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Adaptor3d_Surface>&  aSurface,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer);
};

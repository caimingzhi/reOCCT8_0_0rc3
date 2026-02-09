#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Pnt;
class gp_Dir;

class DsgPrs_FixPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const gp_Pnt&                          aPntAttach,
                                  const gp_Pnt&                          aPntEnd,
                                  const gp_Dir&                          aNormPln,
                                  const double                           aSymbSize);
};

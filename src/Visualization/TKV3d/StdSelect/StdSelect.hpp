#pragma once

#include <SelectMgr_Selection.hpp>
#include <Prs3d_Drawer.hpp>

class StdSelect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void SetDrawerForBRepOwner(
    const occ::handle<SelectMgr_Selection>& aSelection,
    const occ::handle<Prs3d_Drawer>&        aDrawer);
};

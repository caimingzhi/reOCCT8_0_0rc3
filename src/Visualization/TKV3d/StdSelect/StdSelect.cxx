#include <StdSelect.hpp>

#include <SelectMgr_Selection.hpp>
#include <StdSelect_BRepOwner.hpp>

//=================================================================================================

void StdSelect::SetDrawerForBRepOwner(const occ::handle<SelectMgr_Selection>& /*Sel*/,
                                      const occ::handle<Prs3d_Drawer>& /*Drwr*/)
{
  //  occ::handle<StdSelect_BRepOwner> BROWN;

  //   for(Sel->Init();Sel->More();Sel->Next()){
  //     BROWN =
  //     occ::down_cast<StdSelect_BRepOwner>(Sel->Sensitive()->BaseSensitive()->OwnerId());
  //     if(!BROWN.IsNull())
  //       BROWN->SetDrawer(Drwr);
  //   }
}

#include <TopOpeBRepTool_box.hpp>

#include <TopOpeBRepTool_HBoxTool.hpp>
#include <Bnd_Box.hpp>

Standard_EXPORT void FBOX_Prepare()
{
  occ::handle<TopOpeBRepTool_HBoxTool> hbt = FBOX_GetHBoxTool();
  hbt->Clear();
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceBOX())
  {
    std::cout << std::endl << "TOOLBOX : Prepare" << std::endl;
  }
#endif
}

Standard_EXPORT occ::handle<TopOpeBRepTool_HBoxTool> FBOX_GetHBoxTool()
{
  static occ::handle<TopOpeBRepTool_HBoxTool> GLOBAL_TOOLBOX_hboxtool;
  if (GLOBAL_TOOLBOX_hboxtool.IsNull())
  {
    GLOBAL_TOOLBOX_hboxtool = new TopOpeBRepTool_HBoxTool();
  }
  return GLOBAL_TOOLBOX_hboxtool;
}

Standard_EXPORT const Bnd_Box& FBOX_Box(const TopoDS_Shape& S)
{
  occ::handle<TopOpeBRepTool_HBoxTool> hbt = FBOX_GetHBoxTool();
  const Bnd_Box&                       b   = hbt->Box(S);
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceBOX())
  {
    int i = hbt->Index(S);
    int n = hbt->Extent();
    std::cout << "TOOLBOX : " << i << "/" << n << std::endl;
  }
#endif
  return b;
}

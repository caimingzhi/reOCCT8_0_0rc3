#include <TopOpeBRepBuild_Builder.hpp>
#include <TopOpeBRepBuild_ShellFaceSet.hpp>
#include <TopOpeBRepBuild_ShellToSolid.hpp>
#include <TopOpeBRepBuild_SolidBuilder.hpp>
#include <TopOpeBRepDS_BuildTool.hpp>

//=================================================================================================

TopOpeBRepBuild_ShellToSolid::TopOpeBRepBuild_ShellToSolid() = default;

//=================================================================================================

void TopOpeBRepBuild_ShellToSolid::Init()
{
  myLSh.Clear();
}

//=================================================================================================

void TopOpeBRepBuild_ShellToSolid::AddShell(const TopoDS_Shell& Sh)
{
  myLSh.Append(Sh);
}

//=================================================================================================

void TopOpeBRepBuild_ShellToSolid::MakeSolids(const TopoDS_Solid&             So,
                                              NCollection_List<TopoDS_Shape>& LSo)
{
  LSo.Clear();

  TopOpeBRepBuild_ShellFaceSet sfs(So);
  for (NCollection_List<TopoDS_Shape>::Iterator it(myLSh); it.More(); it.Next())
    sfs.AddShape(it.Value());

  bool                         ForceClass = true;
  TopOpeBRepBuild_SolidBuilder SB;
  SB.InitSolidBuilder(sfs, ForceClass);

  TopOpeBRepDS_BuildTool  BT;
  TopOpeBRepBuild_Builder B(BT);
  B.MakeSolids(SB, LSo);
}

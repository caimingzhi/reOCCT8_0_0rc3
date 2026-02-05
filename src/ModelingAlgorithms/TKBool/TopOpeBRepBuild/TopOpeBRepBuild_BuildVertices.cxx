#include <gp_Pnt.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>
#include <TopOpeBRepDS_BuildTool.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>

//=================================================================================================

void TopOpeBRepBuild_Builder::BuildVertices(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  int iP, n = HDS->NbPoints();

  myNewVertices = new NCollection_HArray1<TopoDS_Shape>(0, n);

  for (iP = 1; iP <= n; iP++)
  {
    const TopOpeBRepDS_Point& aTBSPoint = HDS->Point(iP);
    myBuildTool.MakeVertex(ChangeNewVertex(iP), aTBSPoint);
  }
}

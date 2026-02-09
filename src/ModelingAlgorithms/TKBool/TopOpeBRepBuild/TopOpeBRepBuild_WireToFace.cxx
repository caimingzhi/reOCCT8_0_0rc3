#include <TopOpeBRepBuild_Builder.hpp>
#include <TopOpeBRepBuild_FaceBuilder.hpp>
#include <TopOpeBRepBuild_WireEdgeSet.hpp>
#include <TopOpeBRepBuild_WireToFace.hpp>
#include <TopOpeBRepDS_BuildTool.hpp>

TopOpeBRepBuild_WireToFace::TopOpeBRepBuild_WireToFace() = default;

void TopOpeBRepBuild_WireToFace::Init()
{
  myLW.Clear();
}

void TopOpeBRepBuild_WireToFace::AddWire(const TopoDS_Wire& W)
{
  myLW.Append(W);
}

void TopOpeBRepBuild_WireToFace::MakeFaces(const TopoDS_Face& F, NCollection_List<TopoDS_Shape>& LF)
{
  LF.Clear();

  TopOpeBRepBuild_WireEdgeSet wes(F);
  for (NCollection_List<TopoDS_Shape>::Iterator it(myLW); it.More(); it.Next())
    wes.AddShape(it.Value());

  bool                        ForceClass = true;
  TopOpeBRepBuild_FaceBuilder FB;
  FB.InitFaceBuilder(wes, F, ForceClass);

  TopOpeBRepDS_BuildTool  BT(TopOpeBRepTool_APPROX);
  TopOpeBRepBuild_Builder B(BT);
  B.MakeFaces(F, FB, LF);
}

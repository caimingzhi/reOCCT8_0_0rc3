#include <TopOpeBRepBuild_GIter.hpp>
#include <TopOpeBRepBuild_GTool.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>

//=================================================================================================

TopOpeBRepBuild_GTopo TopOpeBRepBuild_GTool::GFusUnsh(const TopAbs_ShapeEnum t1,
                                                      const TopAbs_ShapeEnum t2)
{
  return TopOpeBRepBuild_GTopo(false,
                               false,
                               false,
                               false,
                               false,
                               true,
                               false,
                               true,
                               false,
                               t1,
                               t2,
                               TopOpeBRepDS_UNSHGEOMETRY,
                               TopOpeBRepDS_UNSHGEOMETRY);
}

//=================================================================================================

TopOpeBRepBuild_GTopo TopOpeBRepBuild_GTool::GFusSame(const TopAbs_ShapeEnum t1,
                                                      const TopAbs_ShapeEnum t2)
{
  return TopOpeBRepBuild_GTopo(false,
                               false,
                               false,
                               false,
                               true,
                               true,
                               false,
                               true,
                               false,
                               t1,
                               t2,
                               TopOpeBRepDS_SAMEORIENTED,
                               TopOpeBRepDS_SAMEORIENTED);
}

//=================================================================================================

TopOpeBRepBuild_GTopo TopOpeBRepBuild_GTool::GFusDiff(const TopAbs_ShapeEnum t1,
                                                      const TopAbs_ShapeEnum t2)
{
  return TopOpeBRepBuild_GTopo(false,
                               false,
                               false,
                               false,
                               false,
                               true,
                               false,
                               true,
                               false,
                               t1,
                               t2,
                               TopOpeBRepDS_DIFFORIENTED,
                               TopOpeBRepDS_SAMEORIENTED);
}

//=================================================================================================

TopOpeBRepBuild_GTopo TopOpeBRepBuild_GTool::GCutUnsh(const TopAbs_ShapeEnum t1,
                                                      const TopAbs_ShapeEnum t2)
{
  return TopOpeBRepBuild_GTopo(false,
                               true,
                               false,
                               false,
                               false,
                               true,
                               false,
                               false,
                               false,
                               t1,
                               t2,
                               TopOpeBRepDS_UNSHGEOMETRY,
                               TopOpeBRepDS_UNSHGEOMETRY);
}

//=================================================================================================

TopOpeBRepBuild_GTopo TopOpeBRepBuild_GTool::GCutSame(const TopAbs_ShapeEnum t1,
                                                      const TopAbs_ShapeEnum t2)
{
  return TopOpeBRepBuild_GTopo(false,
                               true,
                               false,
                               false,
                               false,
                               true,
                               false,
                               false,
                               false,
                               t1,
                               t2,
                               TopOpeBRepDS_SAMEORIENTED,
                               TopOpeBRepDS_SAMEORIENTED);
}

//=================================================================================================

TopOpeBRepBuild_GTopo TopOpeBRepBuild_GTool::GCutDiff(const TopAbs_ShapeEnum t1,
                                                      const TopAbs_ShapeEnum t2)
{
  return TopOpeBRepBuild_GTopo(false,
                               true,
                               false,
                               false,
                               true,
                               true,
                               false,
                               false,
                               false,
                               t1,
                               t2,
                               TopOpeBRepDS_DIFFORIENTED,
                               TopOpeBRepDS_SAMEORIENTED);
}

//=================================================================================================

TopOpeBRepBuild_GTopo TopOpeBRepBuild_GTool::GComUnsh(const TopAbs_ShapeEnum t1,
                                                      const TopAbs_ShapeEnum t2)
{
  return TopOpeBRepBuild_GTopo(false,
                               true,
                               false,
                               true,
                               false,
                               false,
                               false,
                               false,
                               false,
                               t1,
                               t2,
                               TopOpeBRepDS_UNSHGEOMETRY,
                               TopOpeBRepDS_UNSHGEOMETRY);
}

//=================================================================================================

TopOpeBRepBuild_GTopo TopOpeBRepBuild_GTool::GComSame(const TopAbs_ShapeEnum t1,
                                                      const TopAbs_ShapeEnum t2)
{
  return TopOpeBRepBuild_GTopo(false,
                               true,
                               false,
                               true,
                               true,
                               false,
                               false,
                               false,
                               false,
                               t1,
                               t2,
                               TopOpeBRepDS_SAMEORIENTED,
                               TopOpeBRepDS_SAMEORIENTED);
}

//=================================================================================================

TopOpeBRepBuild_GTopo TopOpeBRepBuild_GTool::GComDiff(const TopAbs_ShapeEnum t1,
                                                      const TopAbs_ShapeEnum t2)
{
  return TopOpeBRepBuild_GTopo(false,
                               true,
                               false,
                               true,
                               false,
                               false,
                               false,
                               false,
                               false,
                               t1,
                               t2,
                               TopOpeBRepDS_DIFFORIENTED,
                               TopOpeBRepDS_SAMEORIENTED);
}

//=================================================================================================

void TopOpeBRepBuild_GTool::Dump(Standard_OStream& OS)
{
  TopOpeBRepBuild_GIter gi;
  TopOpeBRepBuild_GTopo g;

  g = TopOpeBRepBuild_GTool::GFusUnsh(TopAbs_FACE, TopAbs_FACE);
  g.Dump(OS);
  for (gi.Init(g); gi.More(); gi.Next())
    gi.Dump(OS);
  OS << std::endl;

  g = TopOpeBRepBuild_GTool::GFusSame(TopAbs_FACE, TopAbs_FACE);
  g.Dump(OS);
  for (gi.Init(g); gi.More(); gi.Next())
    gi.Dump(OS);
  OS << std::endl;

  g = TopOpeBRepBuild_GTool::GFusDiff(TopAbs_FACE, TopAbs_FACE);
  g.Dump(OS);
  for (gi.Init(g); gi.More(); gi.Next())
    gi.Dump(OS);
  OS << std::endl;

  g = TopOpeBRepBuild_GTool::GCutDiff(TopAbs_FACE, TopAbs_EDGE);
  g.Dump(OS);
  for (gi.Init(g); gi.More(); gi.Next())
    gi.Dump(OS);
  OS << std::endl;

  g = g.CopyPermuted();
  g.Dump(OS);
  for (gi.Init(g); gi.More(); gi.Next())
    gi.Dump(OS);
  OS << std::endl;
}

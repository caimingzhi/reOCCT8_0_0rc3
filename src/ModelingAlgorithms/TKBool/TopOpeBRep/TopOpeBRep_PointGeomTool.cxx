#include <BRep_Tool.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRep_FaceEdgeIntersector.hpp>
#include <TopOpeBRep_Point2d.hpp>
#include <TopOpeBRep_PointGeomTool.hpp>
#include <TopOpeBRep_VPointInter.hpp>
#include <TopOpeBRepDS_Point.hpp>

//=================================================================================================

TopOpeBRepDS_Point TopOpeBRep_PointGeomTool::MakePoint(const TopOpeBRep_VPointInter& IP)
{
  double tolip  = IP.Tolerance();
  double tolout = tolip;
  int    si     = IP.ShapeIndex();
  if (si == 0)
  {
    tolout = tolip;
  }
  else if (si == 1)
  {
    const TopoDS_Edge& E = TopoDS::Edge(IP.Edge(si));
    tolout               = BRep_Tool::Tolerance(E);
  }
  else if (si == 2)
  {
    const TopoDS_Edge& E = TopoDS::Edge(IP.Edge(si));
    tolout               = BRep_Tool::Tolerance(E);
  }
  else if (si == 3)
  {
    const TopoDS_Edge& E1 = TopoDS::Edge(IP.Edge(1));
    const TopoDS_Edge& E2 = TopoDS::Edge(IP.Edge(2));
    double             t1 = BRep_Tool::Tolerance(E1);
    double             t2 = BRep_Tool::Tolerance(E2);
    //    tolout = std::max(t1,t2);
    if (t1 > 0.9)
      t1 = 0.9;
    if (t1 > 0.9)
      t1 = 0.9;
    tolout = 2.5 * (t1 + t2);
  }
  tolout = std::max(tolout, tolip);
  return TopOpeBRepDS_Point(IP.Value(), tolout);
}

//=================================================================================================

TopOpeBRepDS_Point TopOpeBRep_PointGeomTool::MakePoint(const TopOpeBRep_Point2d& P2D)
{
  double tol = P2D.Tolerance();
  return TopOpeBRepDS_Point(P2D.Value(), tol);
}

//=================================================================================================

TopOpeBRepDS_Point TopOpeBRep_PointGeomTool::MakePoint(const TopOpeBRep_FaceEdgeIntersector& FEI)
{
  double tol = FEI.Tolerance();
  return TopOpeBRepDS_Point(FEI.Value(), tol);
}

//=================================================================================================

TopOpeBRepDS_Point TopOpeBRep_PointGeomTool::MakePoint(const TopoDS_Shape& S)
{
  return TopOpeBRepDS_Point(S);
}

//=================================================================================================

bool TopOpeBRep_PointGeomTool::IsEqual(const TopOpeBRepDS_Point& DSP1,
                                       const TopOpeBRepDS_Point& DSP2)
{
  bool b = DSP1.IsEqual(DSP2);
  return b;
}

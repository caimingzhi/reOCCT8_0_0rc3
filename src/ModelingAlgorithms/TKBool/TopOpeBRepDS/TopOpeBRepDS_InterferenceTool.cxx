#include <Geom2d_Curve.hpp>
#include <TopOpeBRepDS_define.hpp>
#include <TopOpeBRepDS_EdgeVertexInterference.hpp>
#include <TopOpeBRepDS_FaceEdgeInterference.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_InterferenceTool.hpp>
#include <TopOpeBRepDS_SolidSurfaceInterference.hpp>
#include <TopOpeBRepDS_SurfaceCurveInterference.hpp>
#include <TopOpeBRepDS_Transition.hpp>

occ::handle<TopOpeBRepDS_Interference> TopOpeBRepDS_InterferenceTool::MakeEdgeInterference(
  const TopOpeBRepDS_Transition& T,
  const TopOpeBRepDS_Kind        SK,
  const int                      SI,
  const TopOpeBRepDS_Kind        GK,
  const int                      GI,
  const double                   P)
{
  return new TopOpeBRepDS_CurvePointInterference(T, SK, SI, GK, GI, P);
}

occ::handle<TopOpeBRepDS_Interference> TopOpeBRepDS_InterferenceTool::MakeCurveInterference(
  const TopOpeBRepDS_Transition& T,
  const TopOpeBRepDS_Kind        SK,
  const int                      SI,
  const TopOpeBRepDS_Kind        GK,
  const int                      GI,
  const double                   P)
{
  return new TopOpeBRepDS_CurvePointInterference(T, SK, SI, GK, GI, P);
}

occ::handle<TopOpeBRepDS_Interference> TopOpeBRepDS_InterferenceTool::
  DuplicateCurvePointInterference(const occ::handle<TopOpeBRepDS_Interference>& I)
{
  return new TopOpeBRepDS_CurvePointInterference(I->Transition().Complement(),
                                                 I->SupportType(),
                                                 I->Support(),
                                                 I->GeometryType(),
                                                 I->Geometry(),
                                                 TopOpeBRepDS_InterferenceTool::Parameter(I));
}

occ::handle<TopOpeBRepDS_Interference> TopOpeBRepDS_InterferenceTool::MakeFaceCurveInterference(
  const TopOpeBRepDS_Transition&   Transition,
  const int                        FaceI,
  const int                        CurveI,
  const occ::handle<Geom2d_Curve>& PC)
{
  return new TopOpeBRepDS_SurfaceCurveInterference(Transition,
                                                   TopOpeBRepDS_FACE,
                                                   FaceI,
                                                   TopOpeBRepDS_CURVE,
                                                   CurveI,
                                                   PC);
}

occ::handle<TopOpeBRepDS_Interference> TopOpeBRepDS_InterferenceTool::MakeSolidSurfaceInterference(
  const TopOpeBRepDS_Transition& Transition,
  const int                      SolidI,
  const int                      SurfaceI)
{
  return new TopOpeBRepDS_SolidSurfaceInterference(Transition,
                                                   TopOpeBRepDS_SOLID,
                                                   SolidI,
                                                   TopOpeBRepDS_SURFACE,
                                                   SurfaceI);
}

occ::handle<TopOpeBRepDS_Interference> TopOpeBRepDS_InterferenceTool::MakeEdgeVertexInterference(
  const TopOpeBRepDS_Transition& Transition,
  const int                      EdgeI,
  const int                      VertexI,
  const bool                     VertexIsBound,
  const TopOpeBRepDS_Config      C,
  const double                   param)
{

  return new TopOpeBRepDS_EdgeVertexInterference(Transition,
                                                 EdgeI,
                                                 VertexI,
                                                 VertexIsBound,
                                                 C,
                                                 param);
}

occ::handle<TopOpeBRepDS_Interference> TopOpeBRepDS_InterferenceTool::MakeFaceEdgeInterference(
  const TopOpeBRepDS_Transition& Transition,
  const int                      FaceI,
  const int                      EdgeI,
  const bool                     EdgeIsBound,
  const TopOpeBRepDS_Config      C)
{
  return new TopOpeBRepDS_FaceEdgeInterference(Transition, FaceI, EdgeI, EdgeIsBound, C);
}

double TopOpeBRepDS_InterferenceTool::Parameter(const occ::handle<TopOpeBRepDS_Interference>& I)
{
  return occ::down_cast<TopOpeBRepDS_CurvePointInterference>(I)->Parameter();
}

void TopOpeBRepDS_InterferenceTool::Parameter(const occ::handle<TopOpeBRepDS_Interference>& I,
                                              const double                                  Par)
{
  occ::down_cast<TopOpeBRepDS_CurvePointInterference>(I)->Parameter(Par);
}

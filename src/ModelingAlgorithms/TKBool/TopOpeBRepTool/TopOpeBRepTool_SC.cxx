#include <BRep_Tool.hpp>
#include <TopoDS.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_PShapeClassifier.hpp>
#include <TopOpeBRepTool_SC.hpp>

// ----------------------------------------------------------------------
static TopOpeBRepTool_PShapeClassifier TopOpeBRepTool_PSC = nullptr;

Standard_EXPORT TopOpeBRepTool_ShapeClassifier& FSC_GetPSC()
{
  if (TopOpeBRepTool_PSC == nullptr)
    TopOpeBRepTool_PSC = new TopOpeBRepTool_ShapeClassifier();
  return *TopOpeBRepTool_PSC;
}

// ----------------------------------------------------------------------
Standard_EXPORT TopOpeBRepTool_ShapeClassifier& FSC_GetPSC(const TopoDS_Shape& S)
{
  if (TopOpeBRepTool_PSC == nullptr)
    TopOpeBRepTool_PSC = new TopOpeBRepTool_ShapeClassifier();
  TopOpeBRepTool_PSC->SetReference(S);
  return *TopOpeBRepTool_PSC;
}

// ----------------------------------------------------------------------
Standard_EXPORT TopAbs_State FSC_StatePonFace(const gp_Pnt&                   P,
                                              const TopoDS_Shape&             F,
                                              TopOpeBRepTool_ShapeClassifier& PSC)
{
  // Projects <P> on the surface and classifies it in the face <F>
  occ::handle<Geom_Surface> S = BRep_Tool::Surface(TopoDS::Face(F));

  gp_Pnt2d UV;
  double   dist;
  bool     ok = FUN_tool_projPonS(P, S, UV, dist);
  if (!ok)
    return TopAbs_UNKNOWN;

  PSC.SetReference(TopoDS::Face(F));
  PSC.StateP2DReference(UV);
  TopAbs_State state = PSC.State();

  return state;
}

// ----------------------------------------------------------------------
Standard_EXPORT TopAbs_State FSC_StateEonFace(const TopoDS_Shape&             E,
                                              const double                    t,
                                              const TopoDS_Shape&             F,
                                              TopOpeBRepTool_ShapeClassifier& PSC)
{
  BRepAdaptor_Curve BAC(TopoDS::Edge(E));
  double            f, l;
  FUN_tool_bounds(TopoDS::Edge(E), f, l);
  double par = (1 - t) * f + t * l;
  gp_Pnt P;
  BAC.D0(par, P);
  TopAbs_State state = FSC_StatePonFace(P, F, PSC);
  return state;
}

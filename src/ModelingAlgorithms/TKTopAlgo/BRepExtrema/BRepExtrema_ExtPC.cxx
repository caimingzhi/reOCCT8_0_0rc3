#include <BRepExtrema_ExtPC.hpp>

#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>

//=================================================================================================

BRepExtrema_ExtPC::BRepExtrema_ExtPC(const TopoDS_Vertex& V, const TopoDS_Edge& E)
{
  Initialize(E);
  Perform(V);
}

//=================================================================================================

void BRepExtrema_ExtPC::Initialize(const TopoDS_Edge& E)
{
  if (!BRep_Tool::IsGeometric(E))
    return; // protect against non-geometric type (e.g. polygon)
  double U1, U2;
  myHC       = new BRepAdaptor_Curve(E);
  double Tol = std::min(BRep_Tool::Tolerance(E), Precision::Confusion());
  Tol        = std::max(myHC->Resolution(Tol), Precision::PConfusion());
  BRep_Tool::Range(E, U1, U2);
  myExtPC.Initialize(*myHC, U1, U2, Tol);
}

//=================================================================================================

void BRepExtrema_ExtPC::Perform(const TopoDS_Vertex& V)
{
  if (!myHC.IsNull())
  {
    gp_Pnt P = BRep_Tool::Pnt(V);
    myExtPC.Perform(P);
  }
}

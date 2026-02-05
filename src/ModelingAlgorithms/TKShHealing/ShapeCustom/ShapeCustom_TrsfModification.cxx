#include <BRep_TEdge.hpp>
#include <BRep_TFace.hpp>
#include <BRep_TVertex.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <ShapeCustom_TrsfModification.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeCustom_TrsfModification, BRepTools_TrsfModification)

//=================================================================================================

ShapeCustom_TrsfModification::ShapeCustom_TrsfModification(const gp_Trsf& T)
    : BRepTools_TrsfModification(T)
{
}

//=================================================================================================

bool ShapeCustom_TrsfModification::NewSurface(const TopoDS_Face&         F,
                                              occ::handle<Geom_Surface>& S,
                                              TopLoc_Location&           L,
                                              double&                    Tol,
                                              bool&                      RevWires,
                                              bool&                      RevFace)
{
  bool result = BRepTools_TrsfModification::NewSurface(F, S, L, Tol, RevWires, RevFace);
  Tol = (*((occ::handle<BRep_TFace>*)&F.TShape()))->Tolerance() * std::abs(Trsf().ScaleFactor());
  return result;
}

//=================================================================================================

bool ShapeCustom_TrsfModification::NewCurve(const TopoDS_Edge&       E,
                                            occ::handle<Geom_Curve>& C,
                                            TopLoc_Location&         L,
                                            double&                  Tol)
{
  bool result = BRepTools_TrsfModification::NewCurve(E, C, L, Tol);
  Tol = (*((occ::handle<BRep_TEdge>*)&E.TShape()))->Tolerance() * std::abs(Trsf().ScaleFactor());
  return result;
}

//=================================================================================================

bool ShapeCustom_TrsfModification::NewPoint(const TopoDS_Vertex& V, gp_Pnt& P, double& Tol)
{
  bool result = BRepTools_TrsfModification::NewPoint(V, P, Tol);
  Tol = (*((occ::handle<BRep_TVertex>*)&V.TShape()))->Tolerance() * std::abs(Trsf().ScaleFactor());
  return result;
}

//=================================================================================================

bool ShapeCustom_TrsfModification::NewCurve2d(const TopoDS_Edge&         E,
                                              const TopoDS_Face&         F,
                                              const TopoDS_Edge&         NewE,
                                              const TopoDS_Face&         NewF,
                                              occ::handle<Geom2d_Curve>& C,
                                              double&                    Tol)
{
  bool result = BRepTools_TrsfModification::NewCurve2d(E, F, NewE, NewF, C, Tol);
  Tol = (*((occ::handle<BRep_TEdge>*)&E.TShape()))->Tolerance() * std::abs(Trsf().ScaleFactor());
  return result;
}

//=================================================================================================

bool ShapeCustom_TrsfModification::NewParameter(const TopoDS_Vertex& V,
                                                const TopoDS_Edge&   E,
                                                double&              P,
                                                double&              Tol)
{
  bool result = BRepTools_TrsfModification::NewParameter(V, E, P, Tol);
  Tol = (*((occ::handle<BRep_TVertex>*)&V.TShape()))->Tolerance() * std::abs(Trsf().ScaleFactor());
  return result;
}

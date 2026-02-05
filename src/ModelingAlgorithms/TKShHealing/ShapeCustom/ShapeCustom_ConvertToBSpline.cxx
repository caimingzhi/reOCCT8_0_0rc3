#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepTools.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <gp_Pnt.hpp>
#include <Message_Msg.hpp>
#include <Precision.hpp>
#include <ShapeConstruct.hpp>
#include <ShapeCustom_ConvertToBSpline.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeCustom_ConvertToBSpline, ShapeCustom_Modification)

//=================================================================================================

ShapeCustom_ConvertToBSpline::ShapeCustom_ConvertToBSpline()
    : myExtrMode(true),
      myRevolMode(true),
      myOffsetMode(true),
      myPlaneMode(false)
{
}

//=================================================================================================

bool ShapeCustom_ConvertToBSpline::IsToConvert(const occ::handle<Geom_Surface>& S,
                                               occ::handle<Geom_Surface>&       SS) const
{
  SS = S;
  if (S->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
  {
    occ::handle<Geom_RectangularTrimmedSurface> RTS =
      occ::down_cast<Geom_RectangularTrimmedSurface>(S);
    SS = RTS->BasisSurface();
  }
  if (SS->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
  {
    if (myOffsetMode)
      return true;
    else
    {
      occ::handle<Geom_OffsetSurface> OS    = occ::down_cast<Geom_OffsetSurface>(SS);
      occ::handle<Geom_Surface>       basis = OS->BasisSurface();
      occ::handle<Geom_Surface>       tmp;
      return IsToConvert(basis, tmp);
    }
  }
  if (SS->IsKind(STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)))
    return myExtrMode;
  if (SS->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution)))
    return myRevolMode;
  if (SS->IsKind(STANDARD_TYPE(Geom_Plane)))
    return myPlaneMode;
  return false;
}

//=================================================================================================

bool ShapeCustom_ConvertToBSpline::NewSurface(const TopoDS_Face&         F,
                                              occ::handle<Geom_Surface>& S,
                                              TopLoc_Location&           L,
                                              double&                    Tol,
                                              bool&                      RevWires,
                                              bool&                      RevFace)
{
  S = BRep_Tool::Surface(F, L);
  double U1, U2, V1, V2;
  S->Bounds(U1, U2, V1, V2);
  double Umin, Umax, Vmin, Vmax;
  BRepTools::UVBounds(F, Umin, Umax, Vmin, Vmax);
  if (Precision::IsInfinite(U1) || Precision::IsInfinite(U2))
  {
    U1 = Umin;
    U2 = Umax;
  }
  if (Precision::IsInfinite(V1) || Precision::IsInfinite(V2))
  {
    V1 = Vmin;
    V2 = Vmax;
  }

  occ::handle<Geom_Surface> surf;
  if (!IsToConvert(S, surf))
    return false;

  occ::handle<Geom_Surface> res;
  if (surf->IsKind(STANDARD_TYPE(Geom_OffsetSurface)) && !myOffsetMode)
  {
    occ::handle<Geom_OffsetSurface>  OS     = occ::down_cast<Geom_OffsetSurface>(surf);
    occ::handle<Geom_Surface>        basis  = OS->BasisSurface();
    double                           offset = OS->Offset();
    occ::handle<Geom_BSplineSurface> bspl =
      ShapeConstruct::ConvertSurfaceToBSpline(basis,
                                              U1,
                                              U2,
                                              V1,
                                              V2,
                                              Precision::Approximation(),
                                              surf->Continuity(),
                                              10000,
                                              15);
    occ::handle<Geom_OffsetSurface> nOff = new Geom_OffsetSurface(bspl, offset);
    res                                  = nOff;
  }
  else
  {
    GeomAbs_Shape cnt = surf->Continuity();
    if (surf->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
      cnt = GeomAbs_C0; // pdn 30.06.99 because of hang-up in GeomConvert_ApproxSurface
    res = ShapeConstruct::ConvertSurfaceToBSpline(surf,
                                                  U1,
                                                  U2,
                                                  V1,
                                                  V2,
                                                  Precision::Approximation(),
                                                  cnt,
                                                  10000,
                                                  15);
  }
  if (S->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
  {
    occ::handle<Geom_RectangularTrimmedSurface> RTS =
      occ::down_cast<Geom_RectangularTrimmedSurface>(S);
    double UF, UL, VF, VL;
    RTS->Bounds(UF, UL, VF, VL);
    S = new Geom_RectangularTrimmedSurface(res, UF, UL, VF, VL);
  }
  else
    S = res;

  SendMsg(F, Message_Msg("ConvertToBSpline.NewSurface.MSG0"));

  Tol      = BRep_Tool::Tolerance(F);
  RevWires = false;
  RevFace  = false;
  return true;
}

//=================================================================================================

bool ShapeCustom_ConvertToBSpline::NewCurve(const TopoDS_Edge&       E,
                                            occ::handle<Geom_Curve>& C,
                                            TopLoc_Location&         L,
                                            double&                  Tol)
{
  //: p5 abv 26 Feb 99: force copying of edge if any its pcurve will be replaced
  occ::handle<BRep_TEdge>& TE = *((occ::handle<BRep_TEdge>*)&E.TShape());

  // iterate on pcurves
  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());
  for (; itcr.More(); itcr.Next())
  {
    occ::handle<BRep_GCurve> GC = occ::down_cast<BRep_GCurve>(itcr.Value());
    if (GC.IsNull() || !GC->IsCurveOnSurface())
      continue;
    occ::handle<Geom_Surface> S = GC->Surface();
    occ::handle<Geom_Surface> ES;
    if (!IsToConvert(S, ES))
      continue;
    double f, l;
    C = BRep_Tool::Curve(E, L, f, l);
    if (!C.IsNull())
      C = occ::down_cast<Geom_Curve>(C->Copy());
    Tol = BRep_Tool::Tolerance(E);
    SendMsg(E, Message_Msg("ConvertToBSpline.NewCurve.MSG0"));
    return true;
  }
  return false;
}

//=================================================================================================

bool ShapeCustom_ConvertToBSpline::NewPoint(const TopoDS_Vertex& /*V*/,
                                            gp_Pnt& /*P*/,
                                            double& /*Tol*/)
{
  return false;
}

//=================================================================================================

bool ShapeCustom_ConvertToBSpline::NewCurve2d(const TopoDS_Edge& E,
                                              const TopoDS_Face& F,
                                              const TopoDS_Edge& NewE,
                                              const TopoDS_Face& /*NewF*/,
                                              occ::handle<Geom2d_Curve>& C,
                                              double&                    Tol)
{
  TopLoc_Location           L;
  occ::handle<Geom_Surface> S = BRep_Tool::Surface(F, L);
  occ::handle<Geom_Surface> ES;

  // just copy pcurve if either its surface is changing or edge was copied
  if (!IsToConvert(S, ES) && E.IsSame(NewE))
    return false;

  double f, l;
  C = BRep_Tool::CurveOnSurface(E, F, f, l);
  if (!C.IsNull())
    C = occ::down_cast<Geom2d_Curve>(C->Copy());

  Tol = BRep_Tool::Tolerance(E);
  return true;
}

//=================================================================================================

bool ShapeCustom_ConvertToBSpline::NewParameter(const TopoDS_Vertex& /*V*/,
                                                const TopoDS_Edge& /*E*/,
                                                double& /*P*/,
                                                double& /*Tol*/)
{
  return false;
}

//=================================================================================================

GeomAbs_Shape ShapeCustom_ConvertToBSpline::Continuity(const TopoDS_Edge& E,
                                                       const TopoDS_Face& F1,
                                                       const TopoDS_Face& F2,
                                                       const TopoDS_Edge& /*NewE*/,
                                                       const TopoDS_Face& /*NewF1*/,
                                                       const TopoDS_Face& /*NewF2*/)
{
  return BRep_Tool::Continuity(E, F1, F2);
}

void ShapeCustom_ConvertToBSpline::SetExtrusionMode(const bool extrMode)
{
  myExtrMode = extrMode;
}

void ShapeCustom_ConvertToBSpline::SetRevolutionMode(const bool revolMode)
{
  myRevolMode = revolMode;
}

void ShapeCustom_ConvertToBSpline::SetOffsetMode(const bool offsetMode)
{
  myOffsetMode = offsetMode;
}

void ShapeCustom_ConvertToBSpline::SetPlaneMode(const bool planeMode)
{
  myPlaneMode = planeMode;
}

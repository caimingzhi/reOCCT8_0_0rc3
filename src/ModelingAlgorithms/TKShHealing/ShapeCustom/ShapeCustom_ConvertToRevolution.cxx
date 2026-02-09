

#include <BRep_Builder.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepTools.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_ElementarySurface.hpp>
#include <Geom_Line.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Pnt.hpp>
#include <Message_Msg.hpp>
#include <ShapeCustom_ConvertToRevolution.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeCustom_ConvertToRevolution, ShapeCustom_Modification)

ShapeCustom_ConvertToRevolution::ShapeCustom_ConvertToRevolution() = default;

static bool IsToConvert(const occ::handle<Geom_Surface>& S, occ::handle<Geom_ElementarySurface>& ES)
{
  ES = occ::down_cast<Geom_ElementarySurface>(S);
  if (ES.IsNull())
  {
    if (S->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
    {
      occ::handle<Geom_RectangularTrimmedSurface> RTS =
        occ::down_cast<Geom_RectangularTrimmedSurface>(S);
      ES = occ::down_cast<Geom_ElementarySurface>(RTS->BasisSurface());
    }
    else if (S->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
    {
      occ::handle<Geom_OffsetSurface> OS = occ::down_cast<Geom_OffsetSurface>(S);
      ES = occ::down_cast<Geom_ElementarySurface>(OS->BasisSurface());
    }
    if (ES.IsNull())
      return false;
  }

  return ES->IsKind(STANDARD_TYPE(Geom_SphericalSurface))
         || ES->IsKind(STANDARD_TYPE(Geom_ToroidalSurface))
         || ES->IsKind(STANDARD_TYPE(Geom_CylindricalSurface))
         || ES->IsKind(STANDARD_TYPE(Geom_ConicalSurface));
}

bool ShapeCustom_ConvertToRevolution::NewSurface(const TopoDS_Face&         F,
                                                 occ::handle<Geom_Surface>& S,
                                                 TopLoc_Location&           L,
                                                 double&                    Tol,
                                                 bool&                      RevWires,
                                                 bool&                      RevFace)
{
  S = BRep_Tool::Surface(F, L);

  occ::handle<Geom_ElementarySurface> ES;
  if (!IsToConvert(S, ES))
    return false;

  gp_Ax3 Ax3 = ES->Position();
  gp_Pnt pos = Ax3.Location();
  gp_Dir dir = Ax3.Direction();
  gp_Dir X   = Ax3.XDirection();

  occ::handle<Geom_Curve> BasisCurve;
  if (ES->IsKind(STANDARD_TYPE(Geom_SphericalSurface)))
  {
    occ::handle<Geom_SphericalSurface> SS = occ::down_cast<Geom_SphericalSurface>(ES);
    gp_Ax2                             Ax2(pos, X ^ dir, X);
    occ::handle<Geom_Circle>           Circ = new Geom_Circle(Ax2, SS->Radius());
    BasisCurve                              = new Geom_TrimmedCurve(Circ, -M_PI / 2., M_PI / 2.);
  }
  else if (ES->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))
  {
    occ::handle<Geom_ToroidalSurface> TS = occ::down_cast<Geom_ToroidalSurface>(ES);
    gp_Ax2                            Ax2(pos.XYZ() + X.XYZ() * TS->MajorRadius(), X ^ dir, X);
    BasisCurve = new Geom_Circle(Ax2, TS->MinorRadius());
  }
  else if (ES->IsKind(STANDARD_TYPE(Geom_CylindricalSurface)))
  {
    occ::handle<Geom_CylindricalSurface> CS = occ::down_cast<Geom_CylindricalSurface>(ES);
    gp_Ax1                               Ax1(pos.XYZ() + X.XYZ() * CS->Radius(), dir);
    BasisCurve = new Geom_Line(Ax1);
  }
  else if (ES->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))
  {
    occ::handle<Geom_ConicalSurface> CS = occ::down_cast<Geom_ConicalSurface>(ES);
    gp_Dir                           N  = dir.XYZ() + X.XYZ() * std::tan(CS->SemiAngle());
    gp_Ax1                           Ax1(pos.XYZ() + X.XYZ() * CS->RefRadius(), N);
    BasisCurve = new Geom_Line(Ax1);
  }

  gp_Ax1 Axis = Ax3.Axis();

  if (!Ax3.Direct())
    Axis.Reverse();

  occ::handle<Geom_SurfaceOfRevolution> Rev = new Geom_SurfaceOfRevolution(BasisCurve, Axis);

  if (ES == S)
    S = Rev;
  else
  {
    if (S->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
    {
      occ::handle<Geom_RectangularTrimmedSurface> RTS =
        occ::down_cast<Geom_RectangularTrimmedSurface>(S);
      double U1, U2, V1, V2;
      RTS->Bounds(U1, U2, V1, V2);
      S = new Geom_RectangularTrimmedSurface(Rev, U1, U2, V1, V2);
    }
    else if (S->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
    {
      occ::handle<Geom_OffsetSurface> OS = occ::down_cast<Geom_OffsetSurface>(S);
      S                                  = new Geom_OffsetSurface(Rev, OS->Offset());
    }
    else
      S = Rev;
  }
  SendMsg(F, Message_Msg("ConvertToRevolution.NewSurface.MSG0"));

  Tol      = BRep_Tool::Tolerance(F);
  RevWires = false;
  RevFace  = false;
  return true;
}

bool ShapeCustom_ConvertToRevolution::NewCurve(const TopoDS_Edge&       E,
                                               occ::handle<Geom_Curve>& C,
                                               TopLoc_Location&         L,
                                               double&                  Tol)
{

  occ::handle<BRep_TEdge>& TE = *((occ::handle<BRep_TEdge>*)&E.TShape());

  NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itcr(TE->Curves());
  for (; itcr.More(); itcr.Next())
  {
    occ::handle<BRep_GCurve> GC = occ::down_cast<BRep_GCurve>(itcr.Value());
    if (GC.IsNull() || !GC->IsCurveOnSurface())
      continue;
    occ::handle<Geom_Surface>           S = GC->Surface();
    occ::handle<Geom_ElementarySurface> ES;
    if (!IsToConvert(S, ES))
      continue;
    double f, l;
    C = BRep_Tool::Curve(E, L, f, l);
    if (!C.IsNull())
      C = occ::down_cast<Geom_Curve>(C->Copy());
    Tol = BRep_Tool::Tolerance(E);
    return true;
  }
  return false;
}

bool ShapeCustom_ConvertToRevolution::NewPoint(const TopoDS_Vertex&, gp_Pnt&, double&)
{

  return false;
}

bool ShapeCustom_ConvertToRevolution::NewCurve2d(const TopoDS_Edge& E,
                                                 const TopoDS_Face& F,
                                                 const TopoDS_Edge& NewE,
                                                 const TopoDS_Face&,
                                                 occ::handle<Geom2d_Curve>& C,
                                                 double&                    Tol)
{
  TopLoc_Location                     L;
  occ::handle<Geom_Surface>           S = BRep_Tool::Surface(F, L);
  occ::handle<Geom_ElementarySurface> ES;

  if (!IsToConvert(S, ES) && E.IsSame(NewE))
    return false;

  double f, l;
  C = BRep_Tool::CurveOnSurface(E, F, f, l);
  if (!C.IsNull())
  {
    C = occ::down_cast<Geom2d_Curve>(C->Copy());

    if (!ES.IsNull() && ES->IsKind(STANDARD_TYPE(Geom_SphericalSurface)))
    {
      gp_Vec2d shift(0., 2 * M_PI);
      C->Translate(shift);
    }
  }

  Tol = BRep_Tool::Tolerance(E);
  return true;
}

bool ShapeCustom_ConvertToRevolution::NewParameter(const TopoDS_Vertex&,
                                                   const TopoDS_Edge&,
                                                   double&,
                                                   double&)
{
  return false;
}

GeomAbs_Shape ShapeCustom_ConvertToRevolution::Continuity(const TopoDS_Edge& E,
                                                          const TopoDS_Face& F1,
                                                          const TopoDS_Face& F2,
                                                          const TopoDS_Edge&,
                                                          const TopoDS_Face&,
                                                          const TopoDS_Face&)
{
  return BRep_Tool::Continuity(E, F1, F2);
}

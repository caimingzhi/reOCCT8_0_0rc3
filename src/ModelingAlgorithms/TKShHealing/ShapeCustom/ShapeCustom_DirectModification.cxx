

#include <BRep_Builder.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepTools.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_ElementarySurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <gp_Mat.hpp>
#include <gp_Pnt.hpp>
#include <Message_Msg.hpp>
#include <ShapeCustom_DirectModification.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeCustom_DirectModification, ShapeCustom_Modification)

ShapeCustom_DirectModification::ShapeCustom_DirectModification() = default;

static int IsIndirectSurface(occ::handle<Geom_Surface>& S, TopLoc_Location& L)
{
  int result = 0;

  occ::handle<Geom_Surface> TS = S;
  while (TS->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
    TS = occ::down_cast<Geom_RectangularTrimmedSurface>(TS)->BasisSurface();

  occ::handle<Geom_ElementarySurface> ES = occ::down_cast<Geom_ElementarySurface>(TS);
  if (!ES.IsNull())
  {

    gp_Trsf t   = L.Transformation();
    bool    neg = t.IsNegative();
    bool    det = (t.VectorialPart().Determinant() < 0.0);
    bool    dir = ES->Position().Direct();
    if ((neg != det) == dir)
      result = 1;
    occ::handle<Geom_ConicalSurface> CS = occ::down_cast<Geom_ConicalSurface>(ES);
    if (!CS.IsNull())
    {

      if (CS->SemiAngle() < 0.0)
        result += 2;
    }
    if (result)
      S = TS;
  }

  return result;
}

bool ShapeCustom_DirectModification::NewSurface(const TopoDS_Face&         F,
                                                occ::handle<Geom_Surface>& S,
                                                TopLoc_Location&           L,
                                                double&                    Tol,
                                                bool&                      RevWires,
                                                bool&                      RevFace)
{
  S = BRep_Tool::Surface(F, L);

  switch (IsIndirectSurface(S, L))
  {
    case 1:
    {

      S        = S->UReversed();
      RevWires = true;
      RevFace  = true;
      break;
    }
    case 2:
    {

      S = S->VReversed();
      S->UReverse();
      RevWires = false;
      RevFace  = false;
      break;
    }
    case 3:
    {

      S        = S->VReversed();
      RevWires = true;
      RevFace  = true;
      break;
    }
    default:
      return false;
  }

  SendMsg(F, Message_Msg("DirectModification.NewSurface.MSG0"));

  Tol = BRep_Tool::Tolerance(F);

  return true;
}

bool ShapeCustom_DirectModification::NewCurve(const TopoDS_Edge&       E,
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
    occ::handle<Geom_Surface> S   = GC->Surface();
    TopLoc_Location           Loc = GC->Location();
    if (!IsIndirectSurface(S, Loc))
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

bool ShapeCustom_DirectModification::NewPoint(const TopoDS_Vertex&, gp_Pnt&, double&)
{

  return false;
}

bool ShapeCustom_DirectModification::NewCurve2d(const TopoDS_Edge&         E,
                                                const TopoDS_Face&         F,
                                                const TopoDS_Edge&         NewE,
                                                const TopoDS_Face&         NewF,
                                                occ::handle<Geom2d_Curve>& C,
                                                double&                    Tol)
{
  TopLoc_Location           L;
  occ::handle<Geom_Surface> S = BRep_Tool::Surface(F, L);

  int result = IsIndirectSurface(S, L);
  if (!result && E.IsSame(NewE))
    return false;

  double f, l;
  C   = BRep_Tool::CurveOnSurface(E, F, f, l);
  Tol = BRep_Tool::Tolerance(E);

  if (result)
  {

    gp_Trsf2d T;

    switch (result)
    {
      case 1:
      {

        T.SetMirror(gp::OY2d());
        C = occ::down_cast<Geom2d_Curve>(C->Transformed(T));
        break;
      }
      case 2:
      {

        T.SetMirror(gp::OX2d());
        C = occ::down_cast<Geom2d_Curve>(C->Transformed(T));
        T.SetMirror(gp::OY2d());
        C->Transform(T);
        break;
      }
      case 3:
      {

        T.SetMirror(gp::OX2d());
        C = occ::down_cast<Geom2d_Curve>(C->Transformed(T));
        break;
      }
    }

    if (BRepTools::IsReallyClosed(E, F))
    {

      TopoDS_Shape              sh  = NewE.Reversed();
      occ::handle<Geom2d_Curve> tmp = BRep_Tool::CurveOnSurface(TopoDS::Edge(sh), NewF, f, l);
      if (tmp.IsNull())
      {
        tmp = BRep_Tool::CurveOnSurface(E, F, f, l);
        BRep_Builder B;
        B.UpdateEdge(NewE, tmp, C, NewF, Tol);
        B.Range(NewE, NewF, f, l);
      }
    }
  }
  else
  {

    if (!C.IsNull())
      C = occ::down_cast<Geom2d_Curve>(C->Copy());
  }

  return true;
}

bool ShapeCustom_DirectModification::NewParameter(const TopoDS_Vertex&,
                                                  const TopoDS_Edge&,
                                                  double&,
                                                  double&)
{
  return false;
}

GeomAbs_Shape ShapeCustom_DirectModification::Continuity(const TopoDS_Edge& E,
                                                         const TopoDS_Face& F1,
                                                         const TopoDS_Face& F2,
                                                         const TopoDS_Edge&,
                                                         const TopoDS_Face&,
                                                         const TopoDS_Face&)
{
  return BRep_Tool::Continuity(E, F1, F2);
}

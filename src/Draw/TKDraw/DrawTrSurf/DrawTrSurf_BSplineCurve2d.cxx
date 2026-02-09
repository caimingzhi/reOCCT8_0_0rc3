

#include <DrawTrSurf_BSplineCurve2d.hpp>

#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <Draw_MarkerShape.hpp>
#include <DrawTrSurf.hpp>
#include <DrawTrSurf_Params.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <GeomTools_Curve2dSet.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawTrSurf_BSplineCurve2d, DrawTrSurf_Curve2d)

DrawTrSurf_BSplineCurve2d::DrawTrSurf_BSplineCurve2d(const occ::handle<Geom2d_BSplineCurve>& C)
    : DrawTrSurf_Curve2d(C, Draw_vert, 100)
{
  drawKnots = true;
  knotsForm = Draw_Losange;
  knotsLook = Draw_violet;
  knotsDim  = 5;
  drawPoles = true;
  polesLook = Draw_rouge;
}

DrawTrSurf_BSplineCurve2d::DrawTrSurf_BSplineCurve2d(const occ::handle<Geom2d_BSplineCurve>& C,
                                                     const Draw_Color&      CurvColor,
                                                     const Draw_Color&      PolesColor,
                                                     const Draw_Color&      KnotsColor,
                                                     const Draw_MarkerShape KnotsShape,
                                                     const int              KnotsSize,
                                                     const bool             ShowPoles,
                                                     const bool             ShowKnots,
                                                     const int              Discret)
    : DrawTrSurf_Curve2d(C, CurvColor, Discret)
{
  drawKnots = ShowKnots;
  knotsForm = KnotsShape;
  knotsLook = KnotsColor;
  knotsDim  = KnotsSize;
  drawPoles = ShowPoles;
  polesLook = PolesColor;
}

void DrawTrSurf_BSplineCurve2d::DrawOn(Draw_Display& dis) const
{
  occ::handle<Geom2d_BSplineCurve> C = occ::down_cast<Geom2d_BSplineCurve>(curv);

  if (drawPoles)
  {
    int NbPoles = C->NbPoles();
    dis.SetColor(polesLook);
    NCollection_Array1<gp_Pnt2d> CPoles(1, NbPoles);
    C->Poles(CPoles);
    dis.MoveTo(CPoles(1));
    for (int i = 2; i <= NbPoles; i++)
    {
      dis.DrawTo(CPoles(i));
    }
    if (C->IsPeriodic())
      dis.DrawTo(CPoles(1));
  }

  DrawTrSurf_Curve2d::DrawOn(dis);

  if (drawKnots)
  {
    int                        NbKnots = C->NbKnots();
    NCollection_Array1<double> CKnots(1, NbKnots);
    C->Knots(CKnots);
    dis.SetColor(knotsLook);
    for (int i = 1; i <= NbKnots; i++)
    {
      gp_Pnt2d P = C->Value(CKnots(i));
      dis.DrawMarker(P, knotsForm, knotsDim);
    }
  }
}

void DrawTrSurf_BSplineCurve2d::FindPole(const double        X,
                                         const double        Y,
                                         const Draw_Display& D,
                                         const double        XPrec,
                                         int&                Index) const
{
  occ::handle<Geom2d_BSplineCurve> bc   = occ::down_cast<Geom2d_BSplineCurve>(curv);
  double                           Prec = XPrec / D.Zoom();
  gp_Pnt2d                         p1(X / D.Zoom(), Y / D.Zoom());
  Index++;
  int      NbPoles = bc->NbPoles();
  gp_Pnt   P;
  gp_Pnt2d P2d;
  while (Index <= NbPoles)
  {
    P2d = bc->Pole(Index);
    P.SetCoord(P2d.X(), P2d.Y(), 0.0);
    if (D.Project(P).Distance(p1) <= Prec)
    {
      return;
    }
    Index++;
  }
  Index = 0;
}

void DrawTrSurf_BSplineCurve2d::FindKnot(const double        X,
                                         const double        Y,
                                         const Draw_Display& D,
                                         const double        Prec,
                                         int&                Index) const
{
  occ::handle<Geom2d_BSplineCurve> bc = occ::down_cast<Geom2d_BSplineCurve>(curv);
  gp_Pnt2d                         P2d;
  gp_Pnt                           P;
  gp_Pnt2d                         p1(X, Y);
  Index++;
  int NbKnots = bc->NbKnots();
  while (Index <= NbKnots)
  {
    P2d = bc->Value(bc->Knot(Index));
    P.SetCoord(P2d.X(), P2d.Y(), 0.0);
    if (D.Project(P).Distance(p1) <= Prec)
    {
      return;
    }
    Index++;
  }
  Index = 0;
}

occ::handle<Draw_Drawable3D> DrawTrSurf_BSplineCurve2d::Copy() const
{
  occ::handle<DrawTrSurf_BSplineCurve2d> DC =
    new DrawTrSurf_BSplineCurve2d(occ::down_cast<Geom2d_BSplineCurve>(curv->Copy()),
                                  look,
                                  polesLook,
                                  knotsLook,
                                  knotsForm,
                                  knotsDim,
                                  drawPoles,
                                  drawKnots,
                                  GetDiscretisation());

  return DC;
}

occ::handle<Draw_Drawable3D> DrawTrSurf_BSplineCurve2d::Restore(Standard_IStream& theStream)
{
  const DrawTrSurf_Params&         aParams = DrawTrSurf::Parameters();
  occ::handle<Geom2d_BSplineCurve> aGeomCurve =
    occ::down_cast<Geom2d_BSplineCurve>(GeomTools_Curve2dSet::ReadCurve2d(theStream));
  occ::handle<DrawTrSurf_BSplineCurve2d> aDrawCurve =
    new DrawTrSurf_BSplineCurve2d(aGeomCurve,
                                  aParams.CurvColor,
                                  aParams.PolesColor,
                                  aParams.KnotsColor,
                                  aParams.KnotsMarker,
                                  aParams.KnotsSize,
                                  aParams.IsShowPoles,
                                  aParams.IsShowKnots,
                                  aParams.Discret);
  return aDrawCurve;
}

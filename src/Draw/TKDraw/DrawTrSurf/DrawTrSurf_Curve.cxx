

#include <DrawTrSurf_Curve.hpp>

#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomLProp_CLProps.hpp>
#include <GeomTools_CurveSet.hpp>
#include <gp.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <DrawTrSurf.hpp>
#include <DrawTrSurf_Params.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawTrSurf_Curve, DrawTrSurf_Drawable)

double      DrawTrSurf_CurveLimit = 400;
extern bool Draw_Bounds;

DrawTrSurf_Curve::DrawTrSurf_Curve(const occ::handle<Geom_Curve>& C, const bool DispOrigin)
    : DrawTrSurf_Drawable(16, 0.01, 1),
      curv(C),
      look(Draw_vert),
      disporigin(DispOrigin),
      dispcurvradius(false),
      radiusmax(1.0e3),
      radiusratio(0.1)
{
}

DrawTrSurf_Curve::DrawTrSurf_Curve(const occ::handle<Geom_Curve>& C,
                                   const Draw_Color&              aColor,
                                   const int                      Discret,
                                   const double                   Deflection,
                                   const int                      DrawMode,
                                   const bool                     DispOrigin,
                                   const bool                     DispCurvRadius,
                                   const double                   RadiusMax,
                                   const double                   RadiusRatio)
    : DrawTrSurf_Drawable(Discret, Deflection, DrawMode),
      curv(C),
      look(aColor),
      disporigin(DispOrigin),
      dispcurvradius(DispCurvRadius),
      radiusmax(RadiusMax),
      radiusratio(RadiusRatio)
{
}

void DrawTrSurf_Curve::DrawOn(Draw_Display& dis) const
{
  double First    = curv->FirstParameter();
  double Last     = curv->LastParameter();
  bool   firstInf = Precision::IsNegativeInfinite(First);
  bool   lastInf  = Precision::IsPositiveInfinite(Last);

  if (firstInf || lastInf)
  {
    gp_Pnt P1, P2;
    double delta = 1;
    if (firstInf && lastInf)
    {
      do
      {
        delta *= 2;
        First = -delta;
        Last  = delta;
        curv->D0(First, P1);
        curv->D0(Last, P2);
      } while (P1.Distance(P2) < DrawTrSurf_CurveLimit);
    }
    else if (firstInf)
    {
      curv->D0(Last, P2);
      do
      {
        delta *= 2;
        First = Last - delta;
        curv->D0(First, P1);
      } while (P1.Distance(P2) < DrawTrSurf_CurveLimit);
    }
    else if (lastInf)
    {
      curv->D0(First, P1);
      do
      {
        delta *= 2;
        Last = First + delta;
        curv->D0(Last, P2);
      } while (P1.Distance(P2) < DrawTrSurf_CurveLimit);
    }
  }

  dis.SetColor(look);
  GeomAdaptor_Curve C(curv, First, Last);
  DrawCurveOn(C, dis);

  if (disporigin)
  {
    Draw_Bounds = false;
    gp_Pnt P;
    gp_Vec V;
    C.D1(Last, P, V);
    gp_Pnt2d p1, p2;
    dis.Project(P, p1);
    P.Translate(V);
    dis.Project(P, p2);
    gp_Vec2d v(p1, p2);
    if (v.Magnitude() > gp::Resolution())
    {
      double   L = 20 / dis.Zoom();
      double   H = 10 / dis.Zoom();
      gp_Dir2d d(v);
      p2.SetCoord(p1.X() - L * d.X() - H * d.Y(), p1.Y() - L * d.Y() + H * d.X());
      dis.MoveTo(p2);
      p2.SetCoord(p1.X() - L * d.X() + H * d.Y(), p1.Y() - L * d.Y() - H * d.X());
      dis.DrawTo(p1);
      dis.DrawTo(p2);
    }
    Draw_Bounds = true;
  }

  if (dispcurvradius && (C.GetType() != GeomAbs_Line))
  {
    int                        ii;
    int                        intrv, nbintv = C.NbIntervals(GeomAbs_CN);
    NCollection_Array1<double> TI(1, nbintv + 1);
    C.Intervals(TI, GeomAbs_CN);
    double            Resolution = 1.0e-9, Curvature;
    GeomLProp_CLProps LProp(curv, 2, Resolution);
    gp_Pnt            P1, P2;

    for (intrv = 1; intrv <= nbintv; intrv++)
    {
      double t    = TI(intrv);
      double step = (TI(intrv + 1) - t) / GetDiscretisation();
      double LRad, ratio;
      for (ii = 1; ii <= GetDiscretisation(); ii++)
      {
        LProp.SetParameter(t);
        if (LProp.IsTangentDefined())
        {
          Curvature = std::abs(LProp.Curvature());
          if (Curvature > Resolution)
          {
            curv->D0(t, P1);
            dis.MoveTo(P1);
            LRad  = 1. / Curvature;
            ratio = ((LRad > radiusmax) ? radiusmax / LRad : 1);
            ratio *= radiusratio;
            LProp.CentreOfCurvature(P2);
            gp_Vec V(P1, P2);
            dis.DrawTo(P1.Translated(ratio * V));
          }
        }
        t += step;
      }
    }
  }
}

occ::handle<Draw_Drawable3D> DrawTrSurf_Curve::Copy() const
{
  occ::handle<DrawTrSurf_Curve> DC = new DrawTrSurf_Curve(occ::down_cast<Geom_Curve>(curv->Copy()),
                                                          look,
                                                          GetDiscretisation(),
                                                          GetDeflection(),
                                                          GetDrawMode());

  return DC;
}

void DrawTrSurf_Curve::Dump(Standard_OStream& S) const
{
  GeomTools_CurveSet::PrintCurve(curv, S);
}

void DrawTrSurf_Curve::Save(Standard_OStream& theOs) const
{
  GeomTools_CurveSet::PrintCurve(GetCurve(), theOs, true);
}

occ::handle<Draw_Drawable3D> DrawTrSurf_Curve::Restore(Standard_IStream& theStream)
{
  const DrawTrSurf_Params&      aParams    = DrawTrSurf::Parameters();
  occ::handle<Geom_Curve>       aGeomCurve = GeomTools_CurveSet::ReadCurve(theStream);
  occ::handle<DrawTrSurf_Curve> aDrawCurve = new DrawTrSurf_Curve(aGeomCurve,
                                                                  aParams.CurvColor,
                                                                  aParams.Discret,
                                                                  aParams.Deflection,
                                                                  aParams.DrawMode);
  return aDrawCurve;
}

void DrawTrSurf_Curve::Whatis(Draw_Interpretor& S) const
{
  S << " a 3d curve";
}

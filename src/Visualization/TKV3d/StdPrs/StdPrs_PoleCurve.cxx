#include <Adaptor3d_Curve.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_ArrowAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <StdPrs_PoleCurve.hpp>
#include <NCollection_Array1.hpp>

void StdPrs_PoleCurve::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                           const Adaptor3d_Curve&                 aCurve,
                           const occ::handle<Prs3d_Drawer>&       aDrawer)
{
  aPresentation->CurrentGroup()->SetPrimitivesAspect(aDrawer->LineAspect()->Aspect());

  GeomAbs_CurveType CType = aCurve.GetType();
  if (CType == GeomAbs_BezierCurve || CType == GeomAbs_BSplineCurve)
  {
    int i, Nb;
    if (CType == GeomAbs_BezierCurve)
    {
      occ::handle<Geom_BezierCurve> Bz               = aCurve.Bezier();
      Nb                                             = Bz->NbPoles();
      occ::handle<Graphic3d_ArrayOfPolylines> aPrims = new Graphic3d_ArrayOfPolylines(Nb);
      for (i = 1; i <= Nb; i++)
        aPrims->AddVertex(Bz->Pole(i));
      aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
    }
    else if (CType == GeomAbs_BSplineCurve)
    {
      occ::handle<Geom_BSplineCurve> Bs              = aCurve.BSpline();
      Nb                                             = Bs->NbPoles();
      occ::handle<Graphic3d_ArrayOfPolylines> aPrims = new Graphic3d_ArrayOfPolylines(Nb);
      for (i = 1; i <= Nb; i++)
        aPrims->AddVertex(Bs->Pole(i));
      aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
    }
  }

  if (aDrawer->LineArrowDraw())
  {
    gp_Pnt Location;
    gp_Vec Direction;
    aCurve.D1(aCurve.LastParameter(), Location, Direction);
    Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                      Location,
                      gp_Dir(Direction),
                      aDrawer->ArrowAspect()->Angle(),
                      aDrawer->ArrowAspect()->Length());
  }
}

bool StdPrs_PoleCurve::Match(const double           X,
                             const double           Y,
                             const double           Z,
                             const double           aDistance,
                             const Adaptor3d_Curve& aCurve,
                             const occ::handle<Prs3d_Drawer>&)
{
  GeomAbs_CurveType CType = aCurve.GetType();
  int               i, Nb = 0;
  double            x, y, z;
  if (CType == GeomAbs_BezierCurve)
  {
    occ::handle<Geom_BezierCurve> Bz = aCurve.Bezier();
    Nb                               = Bz->NbPoles();
    for (i = 1; i <= Nb; i++)
    {
      Bz->Pole(i).Coord(x, y, z);
      if (std::abs(X - x) + std::abs(Y - y) + std::abs(Z - z) <= aDistance)
        return true;
    }
    return false;
  }
  else if (CType == GeomAbs_BSplineCurve)
  {
    occ::handle<Geom_BSplineCurve> Bs = aCurve.BSpline();
    Nb                                = Bs->NbPoles();
    for (i = 1; i <= Nb; i++)
    {
      Bs->Pole(i).Coord(x, y, z);
      if (std::abs(X - x) + std::abs(Y - y) + std::abs(Z - z) <= aDistance)
        return true;
    }
    return false;
  }
  return false;
}

int StdPrs_PoleCurve::Pick(const double           X,
                           const double           Y,
                           const double           Z,
                           const double           aDistance,
                           const Adaptor3d_Curve& aCurve,
                           const occ::handle<Prs3d_Drawer>&)
{
  double            x, y, z, DistMin = RealLast();
  int               num = 0, i, Nb = 0;
  double            dist;
  GeomAbs_CurveType CType = aCurve.GetType();

  if (CType == GeomAbs_BezierCurve)
  {
    occ::handle<Geom_BezierCurve> Bz = aCurve.Bezier();
    Nb                               = Bz->NbPoles();
    for (i = 1; i <= Nb; i++)
    {
      Bz->Pole(i).Coord(x, y, z);
      dist = std::abs(X - x) + std::abs(Y - y) + std::abs(Z - z);
      if (dist <= aDistance)
      {
        if (dist < DistMin)
        {
          DistMin = dist;
          num     = i;
        }
      }
    }
  }
  else if (CType == GeomAbs_BSplineCurve)
  {
    occ::handle<Geom_BSplineCurve> Bs = aCurve.BSpline();
    Nb                                = Bs->NbPoles();
    for (i = 1; i <= Nb; i++)
    {
      Bs->Pole(i).Coord(x, y, z);
      dist = std::abs(X - x) + std::abs(Y - y) + std::abs(Z - z);
      if (dist <= aDistance)
      {
        if (dist < DistMin)
        {
          DistMin = dist;
          num     = i;
        }
      }
    }
  }

  return num;
}

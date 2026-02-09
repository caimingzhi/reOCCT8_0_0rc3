

#include <gp_GTrsf.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <GProp_PGProps.hpp>
#include <GProp_PrincipalProps.hpp>
#include <ShapeAnalysis_Geom.hpp>
#include <Standard_ErrorHandler.hpp>

bool ShapeAnalysis_Geom::NearestPlane(const NCollection_Array1<gp_Pnt>& Pnts,
                                      gp_Pln&                           aPln,
                                      double&                           Dmax)
{

  GProp_PGProps Pmat(Pnts);
  gp_Pnt        g = Pmat.CentreOfMass();
  double        Xg, Yg, Zg;
  g.Coord(Xg, Yg, Zg);

  GProp_PrincipalProps Pp = Pmat.PrincipalProperties();
  gp_Vec               V1 = Pp.FirstAxisOfInertia();
  double               Xv1, Yv1, Zv1;
  V1.Coord(Xv1, Yv1, Zv1);
  gp_Vec V2 = Pp.SecondAxisOfInertia();
  double Xv2, Yv2, Zv2;
  V2.Coord(Xv2, Yv2, Zv2);
  gp_Vec V3 = Pp.ThirdAxisOfInertia();
  double Xv3, Yv3, Zv3;
  V3.Coord(Xv3, Yv3, Zv3);

  double D, X, Y, Z;
  double Dmx1 = RealFirst();
  double Dmn1 = RealLast();
  double Dmx2 = RealFirst();
  double Dmn2 = RealLast();
  double Dmx3 = RealFirst();
  double Dmn3 = RealLast();

  int ilow = Pnts.Lower(), iup = Pnts.Upper();
  int i;
  for (i = ilow; i <= iup; i++)
  {
    Pnts(i).Coord(X, Y, Z);
    D = (X - Xg) * Xv1 + (Y - Yg) * Yv1 + (Z - Zg) * Zv1;
    if (D > Dmx1)
      Dmx1 = D;
    if (D < Dmn1)
      Dmn1 = D;
    D = (X - Xg) * Xv2 + (Y - Yg) * Yv2 + (Z - Zg) * Zv2;
    if (D > Dmx2)
      Dmx2 = D;
    if (D < Dmn2)
      Dmn2 = D;
    D = (X - Xg) * Xv3 + (Y - Yg) * Yv3 + (Z - Zg) * Zv3;
    if (D > Dmx3)
      Dmx3 = D;
    if (D < Dmn3)
      Dmn3 = D;
  }

  double Dev1 = Dmx1 - Dmn1, Dev2 = Dmx2 - Dmn2, Dev3 = Dmx3 - Dmn3;
  int    It = (Dev1 < Dev2) ? ((Dev1 < Dev3) ? 1 : 3) : ((Dev2 < Dev3) ? 2 : 3);

  switch (It)
  {
    case 1:
    {

      if ((2. * Dev1 > Dev2) || (2. * Dev1 > Dev3))
        It = 0;
      else
        aPln = gp_Pln(g, V1);
      break;
    }
    case 2:
    {

      if ((2. * Dev2 > Dev1) || (2. * Dev2 > Dev3))
        It = 0;
      else
        aPln = gp_Pln(g, V2);
      break;
    }
    case 3:
    {

      if ((2. * Dev3 > Dev2) || (2. * Dev3 > Dev1))
        It = 0;
      else
        aPln = gp_Pln(g, V3);
      break;
    }
  }

  Dmax = RealFirst();
  if (It != 0)
    for (i = ilow; i <= iup; i++)
    {
      D = aPln.Distance(Pnts(i));
      if (Dmax < D)
        Dmax = D;
    }

  return (It != 0);
}

bool ShapeAnalysis_Geom::PositionTrsf(const occ::handle<NCollection_HArray2<double>>& coefs,
                                      gp_Trsf&                                        trsf,
                                      const double                                    unit,
                                      const double                                    prec)
{
  bool result = true;

  trsf = gp_Trsf();

  if (coefs.IsNull())
    return true;

  gp_GTrsf gtrsf;
  for (int i = 1; i <= 3; i++)
  {
    for (int j = 1; j <= 4; j++)
    {
      gtrsf.SetValue(i, j, coefs->Value(i, j));
    }
  }

  gp_XYZ v1(gtrsf.Value(1, 1), gtrsf.Value(2, 1), gtrsf.Value(3, 1));
  gp_XYZ v2(gtrsf.Value(1, 2), gtrsf.Value(2, 2), gtrsf.Value(3, 2));
  gp_XYZ v3(gtrsf.Value(1, 3), gtrsf.Value(2, 3), gtrsf.Value(3, 3));

  double m1 = v1.Modulus();
  double m2 = v2.Modulus();
  double m3 = v3.Modulus();

  if (m1 < prec || m2 < prec || m3 < prec)
    return false;
  double mm = (m1 + m2 + m3) / 3.;

  double pmm = prec * mm;
  if (std::abs(m1 - mm) > pmm || std::abs(m2 - mm) > pmm || std::abs(m3 - mm) > pmm)
    return false;

  v1.Divide(m1);
  v2.Divide(m2);
  v3.Divide(m3);

  if (std::abs(v1.Dot(v2)) > prec || std::abs(v2.Dot(v3)) > prec || std::abs(v3.Dot(v1)) > prec)
    return false;

  if (v1.X() != 1 || v1.Y() != 0 || v1.Z() != 0 || v2.X() != 0 || v2.Y() != 1 || v2.Z() != 0
      || v3.X() != 0 || v3.Y() != 0 || v3.Z() != 1)
  {

    gp_Dir d1(v1);
    gp_Dir d2(v2);
    gp_Dir d3(v3);
    gp_Ax3 axes(gp_Pnt(0, 0, 0), d3, d1);
    d3.Cross(d1);
    if (d3.Dot(d2) < 0)
      axes.YReverse();
    trsf.SetTransformation(axes);
  }

  if (std::abs(mm - 1.) > prec)
    trsf.SetScale(gp_Pnt(0, 0, 0), mm);
  gp_Vec tp(gtrsf.TranslationPart());
  if (unit != 1.)
    tp.Multiply(unit);
  if (tp.X() != 0 || tp.Y() != 0 || tp.Z() != 0)
    trsf.SetTranslationPart(tp);

  return result;
}

#include <GeomLProp.hpp>

#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomLProp_CLProps.hpp>
#include <gp_Dir.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>

static int GeomAbsToInteger(const GeomAbs_Shape gcont)
{
  int cont = 0;
  switch (gcont)
  {
    case GeomAbs_C0:
      cont = 0;
      break;
    case GeomAbs_G1:
      cont = 1;
      break;
    case GeomAbs_C1:
      cont = 2;
      break;
    case GeomAbs_G2:
      cont = 3;
      break;
    case GeomAbs_C2:
      cont = 4;
      break;
    case GeomAbs_C3:
      cont = 5;
      break;
    case GeomAbs_CN:
      cont = 6;
      break;
  }
  return cont;
}

GeomAbs_Shape GeomLProp::Continuity(const occ::handle<Geom_Curve>& C1,
                                    const occ::handle<Geom_Curve>& C2,
                                    const double                   u1,
                                    const double                   u2,
                                    const bool                     r1,
                                    const bool                     r2,
                                    const double                   tl,
                                    const double                   ta)
{
  GeomAbs_Shape cont = GeomAbs_C0;
  int           index1, index2;
  double        tolerance;
  bool          fini = false;
  gp_Vec        d1, d2;
  gp_Dir        dir1, dir2;
  int           cont1, cont2;
  GeomAbs_Shape gcont1 = C1->Continuity(), gcont2 = C2->Continuity();
  cont1 = GeomAbsToInteger(gcont1);
  cont2 = GeomAbsToInteger(gcont2);

  occ::handle<Geom_Curve> aCurve1 = C1;
  occ::handle<Geom_Curve> aCurve2 = C2;
  if (C1->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve> aTrimmed = occ::down_cast<Geom_TrimmedCurve>(aCurve1);
    aCurve1                                 = aTrimmed->BasisCurve();
  }
  if (C2->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve> aTrimmed = occ::down_cast<Geom_TrimmedCurve>(aCurve2);
    aCurve2                                 = aTrimmed->BasisCurve();
  }
  if (aCurve1->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    occ::handle<Geom_BSplineCurve> BSplineCurve = occ::down_cast<Geom_BSplineCurve>(aCurve1);
    BSplineCurve->Resolution(tl, tolerance);
    BSplineCurve->LocateU(u1, tolerance, index1, index2);

    if (index1 > 1 && index2 < BSplineCurve->NbKnots() && index1 == index2)
    {
      cont1 = BSplineCurve->Degree() - BSplineCurve->Multiplicity(index1);
    }
    else
    {
      cont1 = 5;
    }
  }
  if (aCurve2->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    occ::handle<Geom_BSplineCurve> BSplineCurve = occ::down_cast<Geom_BSplineCurve>(aCurve2);
    BSplineCurve->Resolution(tl, tolerance);
    BSplineCurve->LocateU(u2, tolerance, index1, index2);

    if (index1 > 1 && index2 < BSplineCurve->NbKnots() && index1 == index2)
    {
      cont2 = BSplineCurve->Degree() - BSplineCurve->Multiplicity(index1);
    }
    else
    {
      cont2 = 5;
    }
  }
  int n1 = 0, n2 = 0;
  if (cont1 >= 5)
    n1 = 3;
  else if (cont1 == 4)
    n1 = 2;
  else if (cont1 == 2)
    n1 = 1;
  if (cont2 >= 5)
    n2 = 3;
  else if (cont2 == 4)
    n2 = 2;
  else if (cont2 == 2)
    n2 = 1;
  GeomLProp_CLProps clp1(C1, u1, n1, tl);
  GeomLProp_CLProps clp2(C2, u2, n2, tl);
  if (!(clp1.Value().IsEqual(clp2.Value(), tl)))
  {
    throw Standard_Failure("Courbes non jointives");
  }
  int min = std::min(n1, n2);
  if (min >= 1)
  {
    d1 = clp1.D1();
    d2 = clp2.D1();
    if (r1)
      d1.Reverse();
    if (r2)
      d2.Reverse();
    if (d1.IsEqual(d2, tl, ta))
    {
      cont = GeomAbs_C1;
    }
    else if (clp1.IsTangentDefined() && clp2.IsTangentDefined())
    {
      clp1.Tangent(dir1);
      clp2.Tangent(dir2);
      if (r1)
        dir1.Reverse();
      if (r2)
        dir2.Reverse();
      if (dir1.IsEqual(dir2, ta))
      {
        cont = GeomAbs_G1;
      }
      fini = true;
    }
    else
    {
      fini = true;
    }
  }
  if (min >= 2 && !fini)
  {
    d1 = clp1.D2();
    d2 = clp2.D2();
    if (d1.IsEqual(d2, tl, ta))
    {
      cont = GeomAbs_C2;
    }
  }
  return cont;
}

GeomAbs_Shape GeomLProp::Continuity(const occ::handle<Geom_Curve>& C1,
                                    const occ::handle<Geom_Curve>& C2,
                                    const double                   u1,
                                    const double                   u2,
                                    const bool                     r1,
                                    const bool                     r2)
{
  return Continuity(C1, C2, u1, u2, r1, r2, Precision::Confusion(), Precision::Angular());
}

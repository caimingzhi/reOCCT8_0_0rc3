#include <Geom_BoundedCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomConvert.hpp>
#include <GeomConvert_CompCurveToBSplineCurve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

GeomConvert_CompCurveToBSplineCurve::GeomConvert_CompCurveToBSplineCurve(
  const Convert_ParameterisationType theParameterisation)
    : myTol(Precision::Confusion()),
      myType(theParameterisation)
{
}

GeomConvert_CompCurveToBSplineCurve::GeomConvert_CompCurveToBSplineCurve(
  const occ::handle<Geom_BoundedCurve>& BasisCurve,
  const Convert_ParameterisationType    Parameterisation)
    : myTol(Precision::Confusion()),
      myType(Parameterisation)
{
  occ::handle<Geom_BSplineCurve> Bs = occ::down_cast<Geom_BSplineCurve>(BasisCurve);
  if (!Bs.IsNull())
  {
    myCurve = occ::down_cast<Geom_BSplineCurve>(BasisCurve->Copy());
  }
  else
  {
    myCurve = GeomConvert::CurveToBSplineCurve(BasisCurve, myType);
  }
}

bool GeomConvert_CompCurveToBSplineCurve::Add(const occ::handle<Geom_BoundedCurve>& NewCurve,
                                              const double                          Tolerance,
                                              const bool                            After,
                                              const bool                            WithRatio,
                                              const int                             MinM)
{

  occ::handle<Geom_BSplineCurve> Bs = occ::down_cast<Geom_BSplineCurve>(NewCurve);
  if (!Bs.IsNull())
  {
    Bs = occ::down_cast<Geom_BSplineCurve>(NewCurve->Copy());
  }
  else
  {
    Bs = GeomConvert::CurveToBSplineCurve(NewCurve, myType);
  }
  if (myCurve.IsNull())
  {
    myCurve = Bs;
    return true;
  }

  bool avant, apres;
  myTol = Tolerance;

  const gp_Pnt aCurveStart = myCurve->StartPoint();
  const gp_Pnt aCurveEnd   = myCurve->EndPoint();
  const gp_Pnt aBsStart    = Bs->StartPoint();
  const gp_Pnt aBsEnd      = Bs->EndPoint();

  avant = ((aCurveStart.Distance(aBsStart) < myTol) || (aCurveStart.Distance(aBsEnd) < myTol));
  apres = ((aCurveEnd.Distance(aBsStart) < myTol) || (aCurveEnd.Distance(aBsEnd) < myTol));

  if (avant && apres)
  {
    if (After)
      avant = false;
    else
      apres = false;
  }

  if (apres)
  {
    if (aCurveEnd.Distance(aBsEnd) < myTol)
    {
      Bs->Reverse();
    }
    Add(myCurve, Bs, true, WithRatio, MinM);
    return true;
  }

  else if (avant)
  {
    if (aCurveStart.Distance(aBsStart) < myTol)
    {
      Bs->Reverse();
    }
    Add(Bs, myCurve, false, WithRatio, MinM);
    return true;
  }

  return false;
}

void GeomConvert_CompCurveToBSplineCurve::Add(occ::handle<Geom_BSplineCurve>& FirstCurve,
                                              occ::handle<Geom_BSplineCurve>& SecondCurve,
                                              const bool                      After,
                                              const bool                      WithRatio,
                                              const int                       MinM)
{

  int Deg = std::max(FirstCurve->Degree(), SecondCurve->Degree());
  if (FirstCurve->Degree() < Deg)
  {
    FirstCurve->IncreaseDegree(Deg);
  }
  if (SecondCurve->Degree() < Deg)
  {
    SecondCurve->IncreaseDegree(Deg);
  }

  double                     L1, L2;
  int                        ii, jj;
  double                     Ratio = 1, Ratio1, Ratio2, Delta1, Delta2;
  int                        NbP1 = FirstCurve->NbPoles(), NbP2 = SecondCurve->NbPoles();
  int                        NbK1 = FirstCurve->NbKnots(), NbK2 = SecondCurve->NbKnots();
  NCollection_Array1<double> Noeuds(1, NbK1 + NbK2 - 1);
  NCollection_Array1<gp_Pnt> Poles(1, NbP1 + NbP2 - 1);
  NCollection_Array1<double> Poids(1, NbP1 + NbP2 - 1);
  NCollection_Array1<int>    Mults(1, NbK1 + NbK2 - 1);

  if (WithRatio)
  {
    L1 = FirstCurve->DN(FirstCurve->LastParameter(), 1).Magnitude();
    L2 = SecondCurve->DN(SecondCurve->FirstParameter(), 1).Magnitude();

    if ((L1 > Precision::Confusion()) && (L2 > Precision::Confusion()))
    {
      Ratio = L1 / L2;
    }
    if ((Ratio < Precision::Confusion()) || (Ratio > 1 / Precision::Confusion()))
    {
      Ratio = 1;
    }
  }

  if (After)
  {

    Ratio1 = 1;
    Delta1 = 0;
    Ratio2 = 1 / Ratio;
    Delta2 = Ratio2 * SecondCurve->Knot(1) - FirstCurve->Knot(NbK1);
  }
  else
  {

    Ratio1 = Ratio;
    Delta1 = Ratio1 * FirstCurve->Knot(NbK1) - SecondCurve->Knot(1);
    Ratio2 = 1;
    Delta2 = 0;
  }

  double eps;
  for (ii = 1; ii <= NbK1; ii++)
  {
    Noeuds(ii) = Ratio1 * FirstCurve->Knot(ii) - Delta1;
    if (ii > 1)
    {
      eps = Epsilon(std::abs(Noeuds(ii - 1)));
      if (eps < 5.e-10)
        eps = 5.e-10;
      if (Noeuds(ii) - Noeuds(ii - 1) <= eps)
      {
        Noeuds(ii) += eps;
      }
    }
    Mults(ii) = FirstCurve->Multiplicity(ii);
  }
  Mults(NbK1) = FirstCurve->Degree();
  for (ii = 2, jj = NbK1 + 1; ii <= NbK2; ii++, jj++)
  {
    Noeuds(jj) = Ratio2 * SecondCurve->Knot(ii) - Delta2;
    eps        = Epsilon(std::abs(Noeuds(jj - 1)));
    if (eps < 5.e-10)
      eps = 5.e-10;
    if (Noeuds(jj) - Noeuds(jj - 1) <= eps)
    {
      Noeuds(jj) += eps;
    }
    Mults(jj) = SecondCurve->Multiplicity(ii);
  }

  Ratio = FirstCurve->Weight(NbP1);
  Ratio /= SecondCurve->Weight(1);

  for (ii = 1; ii < NbP1; ii++)
  {
    Poles(ii) = FirstCurve->Pole(ii);
    Poids(ii) = FirstCurve->Weight(ii);
  }
  for (ii = 1, jj = NbP1; ii <= NbP2; ii++, jj++)
  {
    Poles(jj) = SecondCurve->Pole(ii);

    Poids(jj) = Ratio * SecondCurve->Weight(ii);
  }

  myCurve = new (Geom_BSplineCurve)(Poles, Poids, Noeuds, Mults, Deg);

  bool Ok = true;
  int  M  = Mults(NbK1);
  while ((M > MinM) && Ok)
  {
    M--;
    Ok = myCurve->RemoveKnot(NbK1, M, myTol);
  }
}

occ::handle<Geom_BSplineCurve> GeomConvert_CompCurveToBSplineCurve::BSplineCurve() const
{
  return myCurve;
}

void GeomConvert_CompCurveToBSplineCurve::Clear()
{
  myCurve.Nullify();
}

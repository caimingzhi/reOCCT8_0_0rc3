

#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

#include <BSplCLib.hpp>
#include <FairCurve_DistributionOfTension.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>

FairCurve_DistributionOfTension::FairCurve_DistributionOfTension(
  const int                                         BSplOrder,
  const occ::handle<NCollection_HArray1<double>>&   FlatKnots,
  const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
  const int                                         DerivativeOrder,
  const double                                      LengthSliding,
  const FairCurve_BattenLaw&                        Law,
  const int                                         NbValAux,
  const bool                                        Uniform)
    : FairCurve_DistributionOfEnergy(BSplOrder, FlatKnots, Poles, DerivativeOrder, NbValAux),
      MyLengthSliding(LengthSliding),
      MyLaw(Law)
{
  if (Uniform)
  {
    MyLaw.Value(0.5, MyHeight);
  }
  else
  {
    MyHeight = 0;
  }
}

bool FairCurve_DistributionOfTension::Value(const math_Vector& TParam, math_Vector& FTension)
{
  bool  Ok = true;
  int   ier, ii, jj, kk;
  gp_XY CPrim(0., 0.);
  int   LastGradientIndex, FirstNonZero, LastZero;

  FTension.Init(0.0);
  math_Matrix Base(1, 3, 1, MyBSplOrder);

  ier = BSplCLib::EvalBsplineBasis(1,
                                   MyBSplOrder,
                                   MyFlatKnots->Array1(),
                                   TParam(TParam.Lower()),
                                   FirstNonZero,
                                   Base);
  if (ier != 0)
    return false;
  LastZero     = FirstNonZero - 1;
  FirstNonZero = 2 * LastZero + 1;

  for (ii = 1; ii <= MyBSplOrder; ii++)
  {
    CPrim += Base(2, ii) * MyPoles->Value(ii + LastZero).Coord();
  }

  double NormeCPrim = CPrim.Modulus();
  double Hauteur, Difference;

  if (MyHeight > 0)
  {
    Hauteur = MyHeight;
  }
  else
  {
    Ok = MyLaw.Value(TParam(TParam.Lower()), Hauteur);
    if (!Ok)
      return Ok;
  }
  Difference = NormeCPrim - MyLengthSliding;

  FTension(FTension.Lower()) = Hauteur * pow(Difference, 2) / MyLengthSliding;

  if (MyDerivativeOrder >= 1)
  {

    math_Vector GradDifference(1, 2 * MyBSplOrder + MyNbValAux);
    double      Xaux, Yaux, Facteur;

    Xaux    = CPrim.X() / NormeCPrim;
    Yaux    = CPrim.Y() / NormeCPrim;
    Facteur = 2 * Hauteur * Difference / MyLengthSliding;

    kk = FTension.Lower() + FirstNonZero;
    jj = 1;
    for (ii = 1; ii <= MyBSplOrder; ii++)
    {
      GradDifference(jj) = Base(2, ii) * Xaux;
      FTension(kk)       = Facteur * GradDifference(jj);
      jj += 1;
      GradDifference(jj) = Base(2, ii) * Yaux;
      FTension(kk + 1)   = Facteur * GradDifference(jj);
      jj += 1;
      kk += 2;
    }
    if (MyNbValAux == 1)
    {
      LastGradientIndex                      = FTension.Lower() + 2 * MyPoles->Length() + 1;
      GradDifference(GradDifference.Upper()) = (1 - pow(NormeCPrim / MyLengthSliding, 2));
      FTension(LastGradientIndex)            = Hauteur * GradDifference(GradDifference.Upper());
    }

    else
    {
      LastGradientIndex = FTension.Lower() + 2 * MyPoles->Length();
    }

    if (MyDerivativeOrder >= 2)
    {

      double FacteurX  = Difference * (1 - pow(Xaux, 2)) / NormeCPrim;
      double FacteurY  = Difference * (1 - pow(Yaux, 2)) / NormeCPrim;
      double FacteurXY = -Difference * Xaux * Yaux / NormeCPrim;
      double Produit;
      int    k1, k2;

      Facteur = 2 * Hauteur / MyLengthSliding;

      kk = FirstNonZero;
      k2 = LastGradientIndex + (kk - 1) * kk / 2;

      for (ii = 2; ii <= 2 * MyBSplOrder; ii += 2)
      {
        k1 = k2 + FirstNonZero;
        k2 = k1 + kk;
        kk += 2;
        for (jj = 2; jj < ii; jj += 2)
        {
          Produit = Base(2, ii / 2) * Base(2, jj / 2);

          FTension(k1) =
            Facteur * (GradDifference(ii - 1) * GradDifference(jj - 1) + FacteurX * Produit);
          k1++;
          FTension(k1) =
            Facteur * (GradDifference(ii) * GradDifference(jj - 1) + FacteurXY * Produit);
          k1++;
          FTension(k2) =
            Facteur * (GradDifference(ii - 1) * GradDifference(jj) + FacteurXY * Produit);
          k2++;
          FTension(k2) = Facteur * (GradDifference(ii) * GradDifference(jj) + FacteurY * Produit);
          k2++;
        }

        Produit = pow(Base(2, ii / 2), 2);

        FTension(k1) =
          Facteur * (GradDifference(ii - 1) * GradDifference(ii - 1) + FacteurX * Produit);
        FTension(k2) =
          Facteur * (GradDifference(ii) * GradDifference(ii - 1) + FacteurXY * Produit);
        k2++;
        FTension(k2) = Facteur * (GradDifference(ii) * GradDifference(ii) + FacteurY * Produit);
      }
      if (MyNbValAux == 1)
      {
        FacteurX = -2 * CPrim.X() * Hauteur / pow(MyLengthSliding, 2);
        FacteurY = -2 * CPrim.Y() * Hauteur / pow(MyLengthSliding, 2);

        ii = LastGradientIndex - FTension.Lower();
        kk = LastGradientIndex + (ii - 1) * ii / 2 + FirstNonZero;
        for (ii = 1; ii <= MyBSplOrder; ii++)
        {
          FTension(kk) = FacteurX * Base(2, ii);
          kk++;
          FTension(kk) = FacteurY * Base(2, ii);
          kk++;
        }
        FTension(FTension.Upper()) =
          2 * Hauteur * pow(NormeCPrim / MyLengthSliding, 2) / MyLengthSliding;
      }
    }
  }

  return Ok;
}



#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

#include <BSplCLib.hpp>
#include <FairCurve_DistributionOfSagging.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>

FairCurve_DistributionOfSagging::FairCurve_DistributionOfSagging(
  const int                                         BSplOrder,
  const occ::handle<NCollection_HArray1<double>>&   FlatKnots,
  const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
  const int                                         DerivativeOrder,
  const FairCurve_BattenLaw&                        Law,
  const int                                         NbValAux)
    : FairCurve_DistributionOfEnergy(BSplOrder, FlatKnots, Poles, DerivativeOrder, NbValAux),
      MyLaw(Law)
{
}

bool FairCurve_DistributionOfSagging::Value(const math_Vector& TParam, math_Vector& Flexion)
{
  bool  Ok = true;
  int   ier, ii, jj, kk;
  gp_XY CPrim(0., 0.), CSecn(0., 0.);
  int   LastGradientIndex, FirstNonZero, LastZero;

  Flexion.Init(0.0);
  math_Matrix Base(1, 4, 1, MyBSplOrder);

  ier = BSplCLib::EvalBsplineBasis(2,
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
    CSecn += Base(3, ii) * MyPoles->Value(ii + LastZero).Coord();
  }

  double NormeCPrim    = CPrim.Modulus();
  double InvNormeCPrim = 1 / NormeCPrim;
  double Hauteur, WVal, Mesure;
  double Numerateur   = CPrim ^ CSecn;
  double Denominateur = pow(NormeCPrim, 2.5);

  Ok = MyLaw.Value(TParam(TParam.Lower()), Hauteur);
  if (!Ok)
    return Ok;

  Mesure                   = pow(Hauteur, 3) / 12;
  WVal                     = Numerateur / Denominateur;
  Flexion(Flexion.Lower()) = Mesure * pow(WVal, 2);

  if (MyDerivativeOrder >= 1)
  {

    math_Vector WGrad(1, 2 * MyBSplOrder + MyNbValAux), NumGrad(1, 2 * MyBSplOrder + MyNbValAux),
      GradNormeCPrim(1, 2 * MyBSplOrder + MyNbValAux), NumduGrad(1, 2 * MyBSplOrder + MyNbValAux);
    double Facteur;
    double XPrim           = CPrim.X();
    double YPrim           = CPrim.Y();
    double XSecn           = CSecn.X();
    double YSecn           = CSecn.Y();
    double InvDenominateur = 1 / Denominateur;
    double Aux;

    Facteur = 2 * Mesure * WVal;
    Aux     = 2.5 * Numerateur * InvNormeCPrim;
    kk      = Flexion.Lower() + FirstNonZero;

    jj = 1;
    for (ii = 1; ii <= MyBSplOrder; ii++)
    {

      NumGrad(jj)        = YSecn * Base(2, ii) - YPrim * Base(3, ii);
      GradNormeCPrim(jj) = XPrim * Base(2, ii) * InvNormeCPrim;
      NumduGrad(jj)      = NumGrad(jj) - Aux * GradNormeCPrim(jj);
      WGrad(jj)          = InvDenominateur * NumduGrad(jj);
      Flexion(kk)        = Facteur * WGrad(jj);
      jj += 1;

      NumGrad(jj)        = -XSecn * Base(2, ii) + XPrim * Base(3, ii);
      GradNormeCPrim(jj) = YPrim * Base(2, ii) * InvNormeCPrim;
      NumduGrad(jj)      = NumGrad(jj) - Aux * GradNormeCPrim(jj);
      WGrad(jj)          = InvDenominateur * NumduGrad(jj);
      Flexion(kk + 1)    = Facteur * WGrad(jj);
      jj += 1;
      kk += 2;
    }
    if (MyNbValAux == 1)
    {

      LastGradientIndex    = Flexion.Lower() + 2 * MyPoles->Length() + 1;
      WGrad(WGrad.Upper()) = 0.0;
    }

    else
    {
      LastGradientIndex = Flexion.Lower() + 2 * MyPoles->Length();
    }

    if (MyDerivativeOrder >= 2)
    {

      double FacteurX  = (1 - std::pow(XPrim * InvNormeCPrim, 2)) * InvNormeCPrim;
      double FacteurY  = (1 - std::pow(YPrim * InvNormeCPrim, 2)) * InvNormeCPrim;
      double FacteurXY = -(XPrim * InvNormeCPrim) * (YPrim * InvNormeCPrim) * InvNormeCPrim;
      double FacteurW  = WVal * InvNormeCPrim;

      double Produit, DSeconde, NSeconde;
      double VIntermed;
      int    k1, k2, II, JJ;

      Facteur = 2 * Mesure;

      kk = FirstNonZero;
      k2 = LastGradientIndex + (kk - 1) * kk / 2;

      for (ii = 2; ii <= 2 * MyBSplOrder; ii += 2)
      {
        II = ii / 2;
        k1 = k2 + FirstNonZero;
        k2 = k1 + kk;
        kk += 2;
        for (jj = 2; jj < ii; jj += 2)
        {
          JJ       = jj / 2;
          Produit  = Base(2, II) * Base(2, JJ);
          NSeconde = Base(2, II) * Base(3, JJ) - Base(3, II) * Base(2, JJ);

          DSeconde = FacteurX * Produit;
          Aux      = NumGrad(ii - 1) * GradNormeCPrim(jj - 1)
                - 2.5 * (NumGrad(jj - 1) * GradNormeCPrim(ii - 1) + DSeconde * Numerateur);
          VIntermed = InvDenominateur * (Aux - 3.5 * GradNormeCPrim(jj - 1) * NumduGrad(ii - 1));

          Flexion(k1) = Facteur * (WGrad(ii - 1) * WGrad(jj - 1) + FacteurW * VIntermed);
          k1++;

          DSeconde = FacteurXY * Produit;
          Aux      = NormeCPrim * NSeconde + NumGrad(ii - 1) * GradNormeCPrim(jj)
                - 2.5 * (NumGrad(jj) * GradNormeCPrim(ii - 1) + DSeconde * Numerateur);
          VIntermed   = InvDenominateur * (Aux - 3.5 * GradNormeCPrim(jj) * NumduGrad(ii - 1));
          Flexion(k1) = Facteur * (WGrad(ii - 1) * WGrad(jj) + FacteurW * VIntermed);
          k1++;

          Aux = -NormeCPrim * NSeconde + NumGrad(ii) * GradNormeCPrim(jj - 1)
                - 2.5 * (NumGrad(jj - 1) * GradNormeCPrim(ii) + DSeconde * Numerateur);
          VIntermed = InvDenominateur * (Aux - 3.5 * GradNormeCPrim(jj - 1) * NumduGrad(ii));

          Flexion(k2) = Facteur * (WGrad(ii) * WGrad(jj - 1) + FacteurW * VIntermed);
          k2++;

          DSeconde = FacteurY * Produit;
          Aux      = NumGrad(ii) * GradNormeCPrim(jj)
                - 2.5 * (NumGrad(jj) * GradNormeCPrim(ii) + DSeconde * Numerateur);
          VIntermed   = InvDenominateur * (Aux - 3.5 * GradNormeCPrim(jj) * NumduGrad(ii));
          Flexion(k2) = Facteur * (WGrad(ii) * WGrad(jj) + FacteurW * VIntermed);
          k2++;
        }

        Produit = pow(Base(2, II), 2);

        DSeconde    = FacteurX * Produit;
        Aux         = -1.5 * NumGrad(ii - 1) * GradNormeCPrim(ii - 1) - 2.5 * DSeconde * Numerateur;
        VIntermed   = InvDenominateur * (Aux - 3.5 * GradNormeCPrim(ii - 1) * NumduGrad(ii - 1));
        Flexion(k1) = Facteur * (WGrad(ii - 1) * WGrad(ii - 1) + FacteurW * VIntermed);

        DSeconde = FacteurXY * Produit;
        Aux      = NumGrad(ii - 1) * GradNormeCPrim(ii)
              - 2.5 * (NumGrad(ii) * GradNormeCPrim(ii - 1) + DSeconde * Numerateur);
        VIntermed   = InvDenominateur * (Aux - 3.5 * GradNormeCPrim(ii) * NumduGrad(ii - 1));
        Flexion(k2) = Facteur * (WGrad(ii) * WGrad(ii - 1) + FacteurW * VIntermed);
        k2++;

        DSeconde    = FacteurY * Produit;
        Aux         = -1.5 * NumGrad(ii) * GradNormeCPrim(ii) - 2.5 * DSeconde * Numerateur;
        VIntermed   = InvDenominateur * (Aux - 3.5 * GradNormeCPrim(ii) * NumduGrad(ii));
        Flexion(k2) = Facteur * (WGrad(ii) * WGrad(ii) + FacteurW * VIntermed);
      }
    }
  }

  return Ok;
}

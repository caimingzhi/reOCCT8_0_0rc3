#include <AdvApprox_ApproxAFunction.hpp>
#include <AdvApprox_DichoCutting.hpp>
#include <AdvApprox_EvaluatorFunction.hpp>
#include <AdvApprox_SimpleApprox.hpp>
#include <BSplCLib.hpp>
#include <Convert_CompPolynomialToPoles.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <math_Vector.hpp>
#include <PLib.hpp>
#include <PLib_JacobiPolynomial.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_OutOfRange.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_HArray1.hpp>

#ifdef OCCT_DEBUG

static bool AdvApprox_Debug = 0;

static void MAPDBN(const int                    dimension,
                   const double                 Debut,
                   const double                 Fin,
                   AdvApprox_EvaluatorFunction& Evaluator,
                   const int                    Iordre)

{
  int         derive, OrdreDer, ier, NDIMEN = dimension;
  double*     Ptr;
  double      h = 1.e-4 * (Fin - Debut + 1.e-3), eps = 1.e-3, t, ab[2];
  math_Vector V1(1, NDIMEN), V2(1, NDIMEN), Diff(1, NDIMEN), Der(1, NDIMEN);

  if (h < 100 * RealEpsilon())
  {
    h = 100 * RealEpsilon();
  }
  ab[0] = Debut;
  ab[1] = Fin;

  for (OrdreDer = 1, derive = 0; OrdreDer <= Iordre; OrdreDer++, derive++)
  {

    Ptr = (double*)&V1.Value(1);
    t   = Debut + h;
    Evaluator(&NDIMEN, ab, &t, &derive, Ptr, &ier);

    Ptr = (double*)&V2.Value(1);
    t   = Debut;
    Evaluator(&NDIMEN, ab, &t, &derive, Ptr, &ier);

    Diff = (V1 - V2) / h;

    Ptr = (double*)&Der.Value(1);
    t   = Debut;
    Evaluator(&NDIMEN, ab, &t, &OrdreDer, Ptr, &ier);

    if ((Diff - Der).Norm() > eps * (Der.Norm() + 1))
    {
      std::cout << " Debug Ft au parametre t+ = " << t << std::endl;
      std::cout << " Positionement sur la derive " << OrdreDer << " : " << Der << std::endl;
      std::cout << " Erreur estime : " << (Der - Diff) << std::endl;
    }

    Ptr = (double*)&V1.Value(1);
    t   = Fin - h;
    Evaluator(&NDIMEN, ab, &t, &derive, Ptr, &ier);

    Ptr = (double*)&V2.Value(1);
    t   = Fin;
    Evaluator(&NDIMEN, ab, &t, &derive, Ptr, &ier);

    Diff = (V2 - V1) / h;

    Ptr = (double*)&Der.Value(1);
    t   = Fin;
    Evaluator(&NDIMEN, ab, &t, &OrdreDer, Ptr, &ier);

    if ((Diff - Der).Norm() > eps * (Der.Norm() + 1))
    {
      std::cout << " Debug Ft au parametre t- = " << t << std::endl;
      std::cout << " Positionement sur la derive " << OrdreDer << " : " << Der << std::endl;
      std::cout << " Erreur estime : " << (Der - Diff) << std::endl;
    }
  }
}
#endif

static void PrepareConvert(const int                         NumCurves,
                           const int                         MaxDegree,
                           const int                         ContinuityOrder,
                           const int                         Num1DSS,
                           const int                         Num2DSS,
                           const int                         Num3DSS,
                           const NCollection_Array1<int>&    NumCoeffPerCurve,
                           NCollection_Array1<double>&       Coefficients,
                           const NCollection_Array2<double>& PolynomialIntervals,
                           const NCollection_Array1<double>& TrueIntervals,
                           const NCollection_Array1<double>& LocalTolerance,
                           NCollection_Array1<double>&       ErrorMax,
                           NCollection_Array1<int>&          Continuity)

{

  bool isCi;
  int  icurve, idim, iordre, ii, Dimension = Num1DSS + 2 * Num2DSS + 3 * Num3DSS,
                                NbSpace = Num1DSS + Num2DSS + Num3DSS;
  double  diff, moy, facteur1, facteur2, normal1, normal2, eps;
  double *Res1, *Res2, *Val1, *Val2;
  double *Coef1, *Coef2;
  int     RealDegree = std::max(MaxDegree + 1, 2 * ContinuityOrder + 2);

  gp_Vec   V1, V2;
  gp_Vec2d v1, v2;

  NCollection_Array1<double> Result(1, 2 * (ContinuityOrder + 1) * Dimension);
  NCollection_Array1<double> Prec(1, NbSpace), Suivant(1, NbSpace);

  Res1 = (double*)&(Result.ChangeValue(1));
  Res2 = (double*)&(Result.ChangeValue((ContinuityOrder + 1) * Dimension + 1));

  Continuity.Init(0);
  if (ContinuityOrder == 0)
    return;

  for (icurve = 1; icurve < NumCurves; icurve++)
  {

    isCi = true;
    Coef1 =
      (double*)&(Coefficients.Value((icurve - 1) * Dimension * RealDegree + Coefficients.Lower()));
    Coef2    = Coef1 + Dimension * RealDegree;
    int Deg1 = NumCoeffPerCurve(NumCoeffPerCurve.Lower() + icurve - 1) - 1;
    PLib::EvalPolynomial(PolynomialIntervals(icurve, 2),
                         ContinuityOrder,
                         Deg1,
                         Dimension,
                         Coef1[0],
                         Res1[0]);
    int Deg2 = NumCoeffPerCurve(NumCoeffPerCurve.Lower() + icurve) - 1;
    PLib::EvalPolynomial(PolynomialIntervals(icurve + 1, 1),
                         ContinuityOrder,
                         Deg2,
                         Dimension,
                         Coef2[0],
                         Res2[0]);

    for (iordre = 1; iordre <= ContinuityOrder && isCi; iordre++)
    {

      double Toler = 1.0e-5;

      double f1_dividend = PolynomialIntervals(icurve, 2) - PolynomialIntervals(icurve, 1);
      double f2_dividend = PolynomialIntervals(icurve + 1, 2) - PolynomialIntervals(icurve + 1, 1);
      double f1_divizor  = TrueIntervals(icurve + 1) - TrueIntervals(icurve);
      double f2_divizor  = TrueIntervals(icurve + 2) - TrueIntervals(icurve + 1);
      double fract1, fract2;

      if (std::abs(f1_divizor) < Toler)

        facteur1 = 0.0;
      else
      {
        fract1   = f1_dividend / f1_divizor;
        facteur1 = std::pow(fract1, iordre);
      }
      if (std::abs(f2_divizor) < Toler)

        facteur2 = 0.0;
      else
      {
        fract2   = f2_dividend / f2_divizor;
        facteur2 = std::pow(fract2, iordre);
      }
      normal1 = std::pow(f1_divizor, iordre);
      normal2 = std::pow(f2_divizor, iordre);

      idim = 1;
      Val1 = Res1 + iordre * Dimension - 1;
      Val2 = Res2 + iordre * Dimension - 1;

      for (ii = 1; ii <= Num1DSS && isCi; ii++, idim++)
      {
        eps  = LocalTolerance(idim) * 0.01;
        diff = std::abs(Val1[ii] * facteur1 - Val2[ii] * facteur2);
        moy  = std::abs(Val1[ii] * facteur1 + Val2[ii] * facteur2);

        if (diff > moy * 1.e-9)
        {
          Prec(idim)    = diff * normal1;
          Suivant(idim) = diff * normal2;

          if (Prec(idim) > eps || Suivant(idim) > eps)
            isCi = false;
        }
        else
        {
          Prec(idim)    = 0;
          Suivant(idim) = 0;
        }
      }

      Val1 += Num1DSS;
      Val2 += Num1DSS;
      for (ii = 1; ii <= Num2DSS && isCi; ii++, idim++, Val1 += 2, Val2 += 2)
      {
        eps = LocalTolerance(idim) * 0.01;
        v1.SetCoord(Val1[1], Val1[2]);
        v2.SetCoord(Val2[1], Val2[2]);
        v1 *= facteur1;
        v2 *= facteur2;
        diff = std::abs(v1.X() - v2.X()) + std::abs(v1.Y() - v2.Y());
        moy  = std::abs(v1.X() + v2.X()) + std::abs(v1.Y() + v2.Y());
        if (diff > moy * 1.e-9)
        {
          Prec(idim)    = diff * normal1;
          Suivant(idim) = diff * normal2;
          if (Prec(idim) > eps || Suivant(idim) > eps)
            isCi = false;
        }
        else
        {
          Prec(idim)    = 0;
          Suivant(idim) = 0;
        }
      }

      for (ii = 1; ii <= Num3DSS && isCi; ii++, idim++, Val1 += 3, Val2 += 3)
      {
        eps = LocalTolerance(idim) * 0.01;
        V1.SetCoord(Val1[1], Val1[2], Val1[3]);
        V2.SetCoord(Val2[1], Val2[2], Val2[3]);
        V1 *= facteur1;
        V2 *= facteur2;
        diff = std::abs(V1.X() - V2.X()) + std::abs(V1.Y() - V2.Y()) + std::abs(V1.Z() - V2.Z());
        moy  = std::abs(V1.X() + V2.X()) + std::abs(V1.Y() + V2.Y()) + std::abs(V1.Z() + V2.Z());
        if (diff > moy * 1.e-9)
        {
          Prec(idim)    = diff * normal1;
          Suivant(idim) = diff * normal2;
          if (Prec(idim) > eps || Suivant(idim) > eps)
            isCi = false;
        }
        else
        {
          Prec(idim)    = 0;
          Suivant(idim) = 0;
        }
      }

      if (isCi)
      {
        Continuity(icurve + 1) = iordre;
        int index              = (icurve - 1) * NbSpace + 1;
        for (ii = index, idim = 1; idim <= NbSpace; ii++, idim++)
        {
          ErrorMax(ii) += Prec(idim);
          ErrorMax(ii + NbSpace) += Suivant(idim);
        }
      }
    }
  }
}

void AdvApprox_ApproxAFunction::Approximation(
  const int TotalDimension,

  const int                      TotalNumSS,
  const NCollection_Array1<int>& LocalDimension,
  const double                   First,
  const double                   Last,

  AdvApprox_EvaluatorFunction& Evaluator,

  const AdvApprox_Cutting& CutTool,

  const int ContinuityOrder,

  const int NumMaxCoeffs,

  const int MaxSegments,

  const NCollection_Array1<double>& LocalTolerancesArray,

  const int code_precis,

  int&                        NumCurves,
  NCollection_Array1<int>&    NumCoeffPerCurveArray,
  NCollection_Array1<double>& CoefficientArray,
  NCollection_Array1<double>& IntervalsArray,
  NCollection_Array1<double>& ErrorMaxArray,
  NCollection_Array1<double>& AverageErrorArray,
  int&                        ErrorCode)
{

  int NUPIL, TheDeg;
#ifdef OCCT_DEBUG
  int NDIMEN = TotalDimension;
#endif
  bool isCut = false;

  double* TABINT = (double*)&IntervalsArray(1);

  ErrorCode = 0;
  CoefficientArray.Init(0);

  if ((MaxSegments < 1) || (std::abs(Last - First) < 1.e-9))
  {
    ErrorCode = 1;
    return;
  }

  int IDIM = 0;
  for (int I = 1; I <= TotalNumSS; I++)
  {
    IDIM += LocalDimension(I);
  }
  if (IDIM != TotalDimension)
  {
    ErrorCode = 1;
    return;
  }
  GeomAbs_Shape Continuity = GeomAbs_C0;
  switch (ContinuityOrder)
  {
    case 0:
      Continuity = GeomAbs_C0;
      break;
    case 1:
      Continuity = GeomAbs_C1;
      break;
    case 2:
      Continuity = GeomAbs_C2;
      break;
    default:
      throw Standard_ConstructionError();
  }

  int NbGaussPoints, WorkDegree;

  PLib::JacobiParameters(Continuity, NumMaxCoeffs - 1, code_precis, NbGaussPoints, WorkDegree);

  TABINT[0] = First;
  TABINT[1] = Last;
  NUPIL     = 1;
  NumCurves = 0;

  PLib_JacobiPolynomial JacobiBase(WorkDegree, Continuity);

  int                    IS;
  bool                   goto_fin_de_boucle;
  int                    MaxDegree = NumMaxCoeffs - 1;
  AdvApprox_SimpleApprox Approx(TotalDimension,
                                TotalNumSS,
                                Continuity,
                                WorkDegree,
                                NbGaussPoints,
                                JacobiBase,
                                Evaluator);
  while ((NUPIL - NumCurves) != 0)
  {

    goto_fin_de_boucle = false;

    Approx.Perform(LocalDimension,
                   LocalTolerancesArray,
                   TABINT[NumCurves],
                   TABINT[NumCurves + 1],
                   MaxDegree);
    if (!Approx.IsDone())
    {
      ErrorCode = 1;
      return;
    }

    NumCoeffPerCurveArray(NumCurves + 1) = 0;

    bool MaxMaxErr = true;
    for (IS = 1; IS <= TotalNumSS; IS++)
    {
      if (Approx.MaxError(IS) > LocalTolerancesArray(IS))
      {
        MaxMaxErr = false;
        break;
      }
    }

    if (MaxMaxErr)
    {
      NumCurves++;
    }
    else
    {

      double TMIL;
      bool   Large;

      Large = CutTool.Value(TABINT[NumCurves], TABINT[NumCurves + 1], TMIL);

      if (NUPIL < MaxSegments && Large)
      {

        isCut         = true;
        double* IDEB  = TABINT + NumCurves + 1;
        double* IDEB1 = IDEB + 1;
        int     ILONG = NUPIL - NumCurves - 1;
        for (int iI = ILONG; iI >= 0; iI--)
        {
          IDEB1[iI] = IDEB[iI];
        }
        IDEB[0] = TMIL;
        NUPIL++;

        goto_fin_de_boucle = true;
      }
      else
      {

        NumCurves++;
      }
    }

    if (goto_fin_de_boucle)
      continue;
    for (IS = 1; IS <= TotalNumSS; IS++)
    {
      ErrorMaxArray.SetValue(IS + (NumCurves - 1) * TotalNumSS, Approx.MaxError(IS));

      AverageErrorArray.SetValue(IS + (NumCurves - 1) * TotalNumSS, Approx.AverageError(IS));
    }

    occ::handle<NCollection_HArray1<double>> HJacCoeff = Approx.Coefficients();
    TheDeg                                             = Approx.Degree();
    if (isCut && (TheDeg < 2 * ContinuityOrder + 1))

      TheDeg = 2 * ContinuityOrder + 1;

    NumCoeffPerCurveArray(NumCurves) = TheDeg + 1;
    NCollection_Array1<double> Coefficients(0, (TheDeg + 1) * TotalDimension - 1);
    JacobiBase.ToCoefficients(TotalDimension, TheDeg, HJacCoeff->Array1(), Coefficients);
    int i, j, f = (TheDeg + 1) * TotalDimension;
    for (i = 0, j = (NumCurves - 1) * TotalDimension * NumMaxCoeffs + 1; i < f; i++, j++)
    {
      CoefficientArray.SetValue(j, Coefficients.Value(i));
    }

#ifdef OCCT_DEBUG

    int IORDRE = ContinuityOrder;

    if (IORDRE > 0 && AdvApprox_Debug)
    {
      MAPDBN(NDIMEN, TABINT[NumCurves - 1], TABINT[NumCurves], Evaluator, IORDRE);
    }
#endif
  }
  return;
}

AdvApprox_ApproxAFunction::AdvApprox_ApproxAFunction(
  const int                                       Num1DSS,
  const int                                       Num2DSS,
  const int                                       Num3DSS,
  const occ::handle<NCollection_HArray1<double>>& OneDTol,
  const occ::handle<NCollection_HArray1<double>>& TwoDTol,
  const occ::handle<NCollection_HArray1<double>>& ThreeDTol,
  const double                                    First,
  const double                                    Last,
  const GeomAbs_Shape                             Continuity,
  const int                                       MaxDeg,
  const int                                       MaxSeg,
  const AdvApprox_EvaluatorFunction&              Func)
    : my1DTolerances(OneDTol),
      my2DTolerances(TwoDTol),
      my3DTolerances(ThreeDTol),
      myFirst(First),
      myLast(Last),
      myContinuity(Continuity),
      myMaxDegree(MaxDeg),
      myMaxSegments(MaxSeg),
      myDone(false),
      myHasResult(false),
      myEvaluator((void*)&Func)
{
  AdvApprox_DichoCutting Cut;
  Perform(Num1DSS, Num2DSS, Num3DSS, Cut);
}

AdvApprox_ApproxAFunction::AdvApprox_ApproxAFunction(
  const int                                       Num1DSS,
  const int                                       Num2DSS,
  const int                                       Num3DSS,
  const occ::handle<NCollection_HArray1<double>>& OneDTol,
  const occ::handle<NCollection_HArray1<double>>& TwoDTol,
  const occ::handle<NCollection_HArray1<double>>& ThreeDTol,
  const double                                    First,
  const double                                    Last,
  const GeomAbs_Shape                             Continuity,
  const int                                       MaxDeg,
  const int                                       MaxSeg,
  const AdvApprox_EvaluatorFunction&              Func,
  const AdvApprox_Cutting&                        CutTool)
    : my1DTolerances(OneDTol),
      my2DTolerances(TwoDTol),
      my3DTolerances(ThreeDTol),
      myFirst(First),
      myLast(Last),
      myContinuity(Continuity),
      myMaxDegree(MaxDeg),
      myMaxSegments(MaxSeg),
      myDone(false),
      myHasResult(false),
      myEvaluator((void*)&Func)
{
  Perform(Num1DSS, Num2DSS, Num3DSS, CutTool);
}

void AdvApprox_ApproxAFunction::Perform(const int                Num1DSS,
                                        const int                Num2DSS,
                                        const int                Num3DSS,
                                        const AdvApprox_Cutting& CutTool)
{
  if (Num1DSS < 0 || Num2DSS < 0 || Num3DSS < 0 || Num1DSS + Num2DSS + Num3DSS <= 0
      || myLast < myFirst || myMaxDegree < 1 || myMaxSegments < 0)
    throw Standard_ConstructionError();
  if (myMaxDegree > 14)
  {
    myMaxDegree = 14;
  }

  myNumSubSpaces[0]     = Num1DSS;
  myNumSubSpaces[1]     = Num2DSS;
  myNumSubSpaces[2]     = Num3DSS;
  int    TotalNumSS     = Num1DSS + Num2DSS + Num3DSS, ii, jj, kk, index, dim_index, local_index;
  int    TotalDimension = myNumSubSpaces[0] + 2 * myNumSubSpaces[1] + 3 * myNumSubSpaces[2];
  double error_value;

  int ContinuityOrder = 0;
  switch (myContinuity)
  {
    case GeomAbs_C0:
      ContinuityOrder = 0;
      break;
    case GeomAbs_C1:
      ContinuityOrder = 1;
      break;
    case GeomAbs_C2:
      ContinuityOrder = 2;
      break;
    default:
      throw Standard_ConstructionError();
  }
  double ApproxStartEnd[2];
  int    NumMaxCoeffs = std::max(myMaxDegree + 1, 2 * ContinuityOrder + 2);
  myMaxDegree         = NumMaxCoeffs - 1;
  int code_precis     = 1;

  ApproxStartEnd[0] = -1.0e0;
  ApproxStartEnd[1] = 1.0e0;

  NCollection_Array1<int> LocalDimension(1, TotalNumSS);

  index = 1;
  NCollection_Array1<double> LocalTolerances(1, TotalNumSS);

  for (jj = 1; jj <= myNumSubSpaces[0]; jj++)
  {
    LocalTolerances.SetValue(index, my1DTolerances->Value(jj));
    LocalDimension.SetValue(index, 1);
    index += 1;
  }
  for (jj = 1; jj <= myNumSubSpaces[1]; jj++)
  {
    LocalTolerances.SetValue(index, my2DTolerances->Value(jj));
    LocalDimension.SetValue(index, 2);
    index += 1;
  }
  for (jj = 1; jj <= myNumSubSpaces[2]; jj++)
  {
    LocalTolerances.SetValue(index, my3DTolerances->Value(jj));
    LocalDimension.SetValue(index, 3);
    index += 1;
  }

  int ErrorCode = 0, NumCurves, size = myMaxSegments * NumMaxCoeffs * TotalDimension;
  occ::handle<NCollection_HArray1<int>> NumCoeffPerCurvePtr =
    new NCollection_HArray1<int>(1, myMaxSegments);

  occ::handle<NCollection_HArray1<double>> LocalCoefficientsPtr =
    new NCollection_HArray1<double>(1, size);

  occ::handle<NCollection_HArray1<double>> IntervalsPtr =
    new NCollection_HArray1<double>(1, myMaxSegments + 1);

  NCollection_Array1<double> ErrorMax(1, myMaxSegments * TotalNumSS);

  NCollection_Array1<double> AverageError(1, myMaxSegments * TotalNumSS);

  Approximation(TotalDimension,
                TotalNumSS,
                LocalDimension,
                myFirst,
                myLast,
                *(AdvApprox_EvaluatorFunction*)myEvaluator,
                CutTool,
                ContinuityOrder,
                NumMaxCoeffs,
                myMaxSegments,
                LocalTolerances,
                code_precis,
                NumCurves,
                NumCoeffPerCurvePtr->ChangeArray1(),
                LocalCoefficientsPtr->ChangeArray1(),
                IntervalsPtr->ChangeArray1(),
                ErrorMax,
                AverageError,
                ErrorCode);

  if (ErrorCode == 0 || ErrorCode == -1)
  {

    NCollection_Array1<int>    TabContinuity(1, NumCurves);
    NCollection_Array2<double> PolynomialIntervalsPtr(1, NumCurves, 1, 2);
    for (ii = PolynomialIntervalsPtr.LowerRow(); ii <= PolynomialIntervalsPtr.UpperRow(); ii++)
    {

      NumCoeffPerCurvePtr->ChangeValue(ii) = std::max(2, NumCoeffPerCurvePtr->Value(ii));
      PolynomialIntervalsPtr.SetValue(ii, 1, ApproxStartEnd[0]);
      PolynomialIntervalsPtr.SetValue(ii, 2, ApproxStartEnd[1]);
    }

    PrepareConvert(NumCurves,
                   myMaxDegree,
                   ContinuityOrder,
                   Num1DSS,
                   Num2DSS,
                   Num3DSS,
                   NumCoeffPerCurvePtr->Array1(),
                   LocalCoefficientsPtr->ChangeArray1(),
                   PolynomialIntervalsPtr,
                   IntervalsPtr->Array1(),
                   LocalTolerances,
                   ErrorMax,
                   TabContinuity);

    Convert_CompPolynomialToPoles AConverter(NumCurves,
                                             TotalDimension,
                                             myMaxDegree,
                                             TabContinuity,
                                             NumCoeffPerCurvePtr->Array1(),
                                             LocalCoefficientsPtr->Array1(),
                                             PolynomialIntervalsPtr,
                                             IntervalsPtr->Array1());

    if (AConverter.IsDone())
    {
      occ::handle<NCollection_HArray2<double>> PolesPtr;
      AConverter.Poles(PolesPtr);
      AConverter.Knots(myKnots);
      AConverter.Multiplicities(myMults);
      myDegree = AConverter.Degree();
      index    = 0;
      if (myNumSubSpaces[0] > 0)
      {
        my1DPoles = new NCollection_HArray2<double>(1, PolesPtr->ColLength(), 1, myNumSubSpaces[0]);
        my1DMaxError     = new NCollection_HArray1<double>(1, myNumSubSpaces[0]);
        my1DAverageError = new NCollection_HArray1<double>(1, myNumSubSpaces[0]);
        for (ii = 1; ii <= PolesPtr->ColLength(); ii++)
        {
          for (jj = 1; jj <= myNumSubSpaces[0]; jj++)
          {
            my1DPoles->SetValue(ii, jj, PolesPtr->Value(ii, jj));
          }
        }

        for (jj = 1; jj <= myNumSubSpaces[0]; jj++)
        {
          error_value = 0.0e0;
          for (ii = 1; ii <= NumCurves; ii++)
          {
            local_index = (ii - 1) * TotalNumSS;
            error_value = std::max(ErrorMax(local_index + jj), error_value);
          }
          my1DMaxError->SetValue(jj, error_value);
        }
        for (jj = 1; jj <= myNumSubSpaces[0]; jj++)
        {
          error_value = 0.0e0;
          for (ii = 1; ii <= NumCurves; ii++)
          {
            local_index = (ii - 1) * TotalNumSS;
            error_value += AverageError(local_index + jj);
          }
          error_value /= (double)NumCurves;
          my1DAverageError->SetValue(jj, error_value);
        }
        index += myNumSubSpaces[0];
      }

      dim_index = index;

      if (myNumSubSpaces[1] > 0)
      {
        gp_Pnt2d Point2d;
        my2DPoles =
          new NCollection_HArray2<gp_Pnt2d>(1, PolesPtr->ColLength(), 1, myNumSubSpaces[1]);
        my2DMaxError     = new NCollection_HArray1<double>(1, myNumSubSpaces[1]);
        my2DAverageError = new NCollection_HArray1<double>(1, myNumSubSpaces[1]);
        for (ii = 1; ii <= PolesPtr->ColLength(); ii++)
        {
          for (jj = 1; jj <= myNumSubSpaces[1]; jj++)
          {
            local_index = index + (jj - 1) * 2;
            for (kk = 1; kk <= 2; kk++)
            {
              Point2d.SetCoord(kk, PolesPtr->Value(ii, local_index + kk));
            }
            my2DPoles->SetValue(ii, jj, Point2d);
          }
        }

        for (jj = 1; jj <= myNumSubSpaces[1]; jj++)
        {
          error_value = 0.0e0;
          for (ii = 1; ii <= NumCurves; ii++)
          {
            local_index = (ii - 1) * TotalNumSS + index;
            error_value = std::max(ErrorMax(local_index + jj), error_value);
          }
          my2DMaxError->SetValue(jj, error_value);
        }
        for (jj = 1; jj <= myNumSubSpaces[1]; jj++)
        {
          error_value = 0.0e0;
          for (ii = 1; ii <= NumCurves; ii++)
          {
            local_index = (ii - 1) * TotalNumSS + index;
            error_value += AverageError(local_index + jj);
          }
          error_value /= (double)NumCurves;
          my2DAverageError->SetValue(jj, error_value);
        }
        index += myNumSubSpaces[1];

        dim_index = index + myNumSubSpaces[1];
      }

      if (myNumSubSpaces[2] > 0)
      {
        gp_Pnt Point;
        my3DPoles = new NCollection_HArray2<gp_Pnt>(1, PolesPtr->ColLength(), 1, myNumSubSpaces[2]);
        my3DMaxError     = new NCollection_HArray1<double>(1, myNumSubSpaces[2]);
        my3DAverageError = new NCollection_HArray1<double>(1, myNumSubSpaces[2]);
        for (ii = 1; ii <= PolesPtr->ColLength(); ii++)
        {
          for (jj = 1; jj <= myNumSubSpaces[2]; jj++)
          {
            local_index = dim_index + (jj - 1) * 3;
            for (kk = 1; kk <= 3; kk++)
            {
              Point.SetCoord(kk, PolesPtr->Value(ii, local_index + kk));
            }
            my3DPoles->SetValue(ii, jj, Point);
          }
        }

        for (jj = 1; jj <= myNumSubSpaces[2]; jj++)
        {
          error_value = 0.0e0;
          for (ii = 1; ii <= NumCurves; ii++)
          {
            local_index = (ii - 1) * TotalNumSS + index;
            error_value = std::max(ErrorMax(local_index + jj), error_value);
          }
          my3DMaxError->SetValue(jj, error_value);
        }
        for (jj = 1; jj <= myNumSubSpaces[2]; jj++)
        {
          error_value = 0.0e0;
          for (ii = 1; ii <= NumCurves; ii++)
          {
            local_index = (ii - 1) * TotalNumSS + index;
            error_value += AverageError(local_index + jj);
          }
          error_value /= (double)NumCurves;
          my3DAverageError->SetValue(jj, error_value);
        }
      }
      if (ErrorCode == 0)
      {
        myDone      = true;
        myHasResult = true;
      }
      else if (ErrorCode == -1)
      {
        myHasResult = true;
      }
    }
  }
}

void AdvApprox_ApproxAFunction::Poles(const int Index, NCollection_Array1<gp_Pnt>& P) const
{
  int ii;
  for (ii = P.Lower(); ii <= P.Upper(); ii++)
  {
    P.SetValue(ii, my3DPoles->Value(ii, Index));
  }
}

int AdvApprox_ApproxAFunction::NbPoles() const
{
  if (myDone || myHasResult)
    return BSplCLib::NbPoles(myDegree, false, myMults->Array1());
  return 0;
}

void AdvApprox_ApproxAFunction::Poles2d(const int Index, NCollection_Array1<gp_Pnt2d>& P) const
{
  int ii;
  for (ii = P.Lower(); ii <= P.Upper(); ii++)
  {
    P.SetValue(ii, my2DPoles->Value(ii, Index));
  }
}

void AdvApprox_ApproxAFunction::Poles1d(const int Index, NCollection_Array1<double>& P) const
{
  int ii;
  for (ii = P.Lower(); ii <= P.Upper(); ii++)
  {
    P.SetValue(ii, my1DPoles->Value(ii, Index));
  }
}

occ::handle<NCollection_HArray1<double>> AdvApprox_ApproxAFunction::MaxError(const int D) const

{
  occ::handle<NCollection_HArray1<double>> EPtr;
  if (D <= 0 || D > 3)
  {

    throw Standard_OutOfRange();
  }
  switch (D)
  {
    case 1:
      EPtr = my1DMaxError;
      break;
    case 2:
      EPtr = my2DMaxError;
      break;
    case 3:
      EPtr = my3DMaxError;
      break;
  }
  return EPtr;
}

double AdvApprox_ApproxAFunction::MaxError(const int D, const int Index) const
{
  occ::handle<NCollection_HArray1<double>> EPtr = MaxError(D);

  return EPtr->Value(Index);
}

occ::handle<NCollection_HArray1<double>> AdvApprox_ApproxAFunction::AverageError(const int D) const

{
  occ::handle<NCollection_HArray1<double>> EPtr;
  if (D <= 0 || D > 3)
  {

    throw Standard_OutOfRange();
  }
  switch (D)
  {
    case 1:
      EPtr = my1DAverageError;
      break;
    case 2:
      EPtr = my2DAverageError;
      break;
    case 3:
      EPtr = my3DAverageError;
      break;
  }
  return EPtr;
}

double AdvApprox_ApproxAFunction::AverageError(const int D, const int Index) const

{
  occ::handle<NCollection_HArray1<double>> EPtr = AverageError(D);
  return EPtr->Value(Index);
}

void AdvApprox_ApproxAFunction::Dump(Standard_OStream& o) const
{
  int ii;
  o << "Dump of ApproxAFunction" << std::endl;
  if (myNumSubSpaces[0] > 0)
  {
    o << "Error(s) 1d = " << std::endl;
    for (ii = 1; ii <= myNumSubSpaces[0]; ii++)
    {
      o << "   " << MaxError(1, ii) << std::endl;
    }
  }

  if (myNumSubSpaces[1] > 0)
  {
    o << "Error(s) 2d = " << std::endl;
    for (ii = 1; ii <= myNumSubSpaces[1]; ii++)
    {
      o << "   " << MaxError(2, ii) << std::endl;
    }
  }

  if (myNumSubSpaces[2] > 0)
  {
    o << "Error(s) 3d = " << std::endl;
    for (ii = 1; ii <= myNumSubSpaces[2]; ii++)
    {
      o << "   " << MaxError(3, ii) << std::endl;
    }
  }
}

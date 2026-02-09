#include <BSplCLib.hpp>
#include <Convert_CompBezierCurves2dToBSplineCurve2d.hpp>
#include <gp.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <PLib.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

Convert_CompBezierCurves2dToBSplineCurve2d::Convert_CompBezierCurves2dToBSplineCurve2d(
  const double AngularTolerance)
    : myDegree(0),
      myAngular(AngularTolerance),
      myDone(false)
{
}

void Convert_CompBezierCurves2dToBSplineCurve2d::AddCurve(const NCollection_Array1<gp_Pnt2d>& Poles)
{
  if (!mySequence.IsEmpty())
  {
    gp_Pnt2d P1, P2;
    P1 = mySequence.Last()->Value(mySequence.Last()->Upper());
    P2 = Poles(Poles.Lower());
  }
  myDone = false;
  occ::handle<NCollection_HArray1<gp_Pnt2d>> HPoles =
    new NCollection_HArray1<gp_Pnt2d>(Poles.Lower(), Poles.Upper());
  HPoles->ChangeArray1() = Poles;
  mySequence.Append(HPoles);
}

int Convert_CompBezierCurves2dToBSplineCurve2d::Degree() const
{
  return myDegree;
}

int Convert_CompBezierCurves2dToBSplineCurve2d::NbPoles() const
{
  return CurvePoles.Length();
}

void Convert_CompBezierCurves2dToBSplineCurve2d::Poles(NCollection_Array1<gp_Pnt2d>& Poles) const
{
  int i, Lower = Poles.Lower(), Upper = Poles.Upper();
  int k = 1;
  for (i = Lower; i <= Upper; i++)
  {
    Poles(i) = CurvePoles(k++);
  }
}

int Convert_CompBezierCurves2dToBSplineCurve2d::NbKnots() const
{
  return CurveKnots.Length();
}

void Convert_CompBezierCurves2dToBSplineCurve2d::KnotsAndMults(NCollection_Array1<double>& Knots,
                                                               NCollection_Array1<int>& Mults) const
{
  int i, LowerK = Knots.Lower(), UpperK = Knots.Upper();
  int LowerM = Mults.Lower(), UpperM = Mults.Upper();
  int k = 1;
  for (i = LowerK; i <= UpperK; i++)
  {
    Knots(i) = CurveKnots(k++);
  }
  k = 1;
  for (i = LowerM; i <= UpperM; i++)
  {
    Mults(i) = KnotsMultiplicities(k++);
  }
}

void Convert_CompBezierCurves2dToBSplineCurve2d::Perform()
{
  myDone = true;
  CurvePoles.Clear();
  CurveKnots.Clear();
  KnotsMultiplicities.Clear();
  int LowerI  = 1;
  int UpperI  = mySequence.Length();
  int NbrCurv = UpperI - LowerI + 1;

  NCollection_Array1<double> CurveKnVals(1, NbrCurv);

  int i;
  myDegree = 0;
  for (i = 1; i <= mySequence.Length(); i++)
  {
    myDegree = std::max(myDegree, (mySequence(i))->Length() - 1);
  }

  double                       Det = 0;
  gp_Pnt2d                     P1, P2, P3;
  int                          Deg, Inc, MaxDegree = myDegree;
  NCollection_Array1<gp_Pnt2d> Points(1, myDegree + 1);

  for (i = LowerI; i <= UpperI; i++)
  {

    Deg = mySequence(i)->Length() - 1;
    Inc = myDegree - Deg;
    if (Inc > 0)
    {
      BSplCLib::IncreaseDegree(myDegree,
                               mySequence(i)->Array1(),
                               BSplCLib::NoWeights(),
                               Points,
                               BSplCLib::NoWeights());
    }
    else
    {
      Points = mySequence(i)->Array1();
    }

    if (i == LowerI)
    {

      for (int j = 1; j <= MaxDegree; j++)
      {
        CurvePoles.Append(Points(j));
      }
      CurveKnVals(1) = 1.;
      KnotsMultiplicities.Append(MaxDegree + 1);
      Det = 1.;
    }

    if (i != LowerI)
    {
      P2 = Points(1);
      P3 = Points(2);
      gp_Vec2d V1(P1, P2), V2(P2, P3);

      double D1 = V1.SquareMagnitude();
      double D2 = V2.SquareMagnitude();
      if (MaxDegree > 1 && D1 > gp::Resolution() && D2 > gp::Resolution()
          && V1.IsParallel(V2, myAngular))
      {
        double Lambda = std::sqrt(D2 / D1);
        KnotsMultiplicities.Append(MaxDegree - 1);
        CurveKnVals(i) = CurveKnVals(i - 1) * Lambda;
      }
      else
      {
        CurvePoles.Append(Points(1));
        KnotsMultiplicities.Append(MaxDegree);
        CurveKnVals(i) = 1.0;
      }
      Det += CurveKnVals(i);

      for (int j = 2; j <= MaxDegree; j++)
      {
        CurvePoles.Append(Points(j));
      }
    }

    if (i == UpperI)
    {

      CurvePoles.Append(Points(MaxDegree + 1));
      KnotsMultiplicities.Append(MaxDegree + 1);
    }
    P1 = Points(MaxDegree);
  }

  CurveKnots.Append(0.0);
  for (i = 2; i <= NbrCurv; i++)
  {
    CurveKnots.Append(CurveKnots(i - 1) + (CurveKnVals(i - 1) / Det));
  }
  CurveKnots.Append(1.0);
}

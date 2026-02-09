#include <math_Vector.hpp>
#include <math_FunctionSetRoot.hpp>
#include <math_NewtonFunctionSetRoot.hpp>
#include <gp_Vec2d.hpp>

IntCurve_ExactIntersectionPoint::IntCurve_ExactIntersectionPoint(const TheCurve& C1,
                                                                 const TheCurve& C2,
                                                                 const double    Tol)
    : done(false),
      nbroots(0),
      myTol(Tol * Tol),
      FctDist(C1, C2),
      ToleranceVector(1, 2),
      BInfVector(1, 2),
      BSupVector(1, 2),
      StartingPoint(1, 2),
      Root(1, 2),
      anErrorOccurred(false)
{
  ToleranceVector.Value(1) = TheCurveTool::EpsX(C1);
  ToleranceVector.Value(2) = TheCurveTool::EpsX(C2);
}

void IntCurve_ExactIntersectionPoint::Perform(const IntCurve_ThePolygon2d& Poly1,
                                              const IntCurve_ThePolygon2d& Poly2,
                                              int&                         NumSegOn1,
                                              int&                         NumSegOn2,
                                              double&                      ParamOnSeg1,
                                              double&                      ParamOnSeg2)
{

  if (NumSegOn1 >= Poly1.NbSegments() && ParamOnSeg1 == 0.0)
  {
    NumSegOn1--;
    ParamOnSeg1 = 1.0;
  }
  if (NumSegOn2 >= Poly2.NbSegments() && ParamOnSeg2 == 0.0)
  {
    NumSegOn2--;
    ParamOnSeg2 = 1.0;
  }
  if (NumSegOn1 <= 0)
  {
    NumSegOn1   = 1;
    ParamOnSeg1 = 0.0;
  }
  if (NumSegOn2 <= 0)
  {
    NumSegOn2   = 1;
    ParamOnSeg2 = 0.0;
  }

  StartingPoint.Value(1) = Poly1.ApproxParamOnCurve(NumSegOn1, ParamOnSeg1);
  if (NumSegOn1 <= 2)
    BInfVector.Value(1) = Poly1.InfParameter();
  else
    BInfVector.Value(1) = Poly1.ApproxParamOnCurve(NumSegOn1 - 1, (double)0.0);
  if (NumSegOn1 >= (Poly1.NbSegments() - 2))
    BSupVector.Value(1) = Poly1.SupParameter();
  else
    BSupVector.Value(1) = Poly1.ApproxParamOnCurve(NumSegOn1 + 2, (double)0.0);

  StartingPoint.Value(2) = Poly2.ApproxParamOnCurve(NumSegOn2, ParamOnSeg2);
  if (NumSegOn2 <= 2)
    BInfVector.Value(2) = Poly2.InfParameter();
  else
    BInfVector.Value(2) = Poly2.ApproxParamOnCurve(NumSegOn2 - 1, (double)0.0);
  if (NumSegOn2 >= (Poly2.NbSegments() - 2))
    BSupVector.Value(2) = Poly2.SupParameter();
  else
    BSupVector.Value(2) = Poly2.ApproxParamOnCurve(NumSegOn2 + 2, (double)0.0);

  IntCurve_ExactIntersectionPoint::MathPerform();
  if (nbroots == 0)
  {

    Poly1.DeflectionOverEstimation();

    Poly2.DeflectionOverEstimation();

    {

      int    diff         = 1;
      double AnBinfVector = BInfVector.Value(1);
      double AnBsupVector = BSupVector.Value(1);

      do
      {
        diff++;
        if ((NumSegOn1 - diff) <= 1)
        {
          BInfVector.Value(1) = Poly1.InfParameter();
          diff                = 0;
        }
        else
          BInfVector.Value(1) = Poly1.ApproxParamOnCurve(NumSegOn1 - diff, (double)0.0);
        IntCurve_ExactIntersectionPoint::MathPerform();

        if (diff > 3)
          diff += NumSegOn1 / 2;
      } while (nbroots == 0 && diff != 0);

      if (nbroots == 0)
      {
        BInfVector.Value(1) = AnBinfVector;
        diff                = 1;
        do
        {
          diff++;
          if ((NumSegOn1 + diff) >= (Poly1.NbSegments() - 1))
          {
            BSupVector.Value(1) = Poly1.SupParameter();
            diff                = 0;
          }
          else
            BSupVector.Value(1) = Poly1.ApproxParamOnCurve(NumSegOn1 + 1 + diff, (double)0.0);
          IntCurve_ExactIntersectionPoint::MathPerform();

          if (diff > 3)
            diff += 1 + (Poly1.NbSegments() - NumSegOn1) / 2;
        } while (nbroots == 0 && diff != 0);
      }
      BSupVector.Value(1) = AnBsupVector;
    }

    if (nbroots == 0)
    {

      int    diff         = 1;
      double AnBinfVector = BInfVector.Value(2);
      double AnBsupVector = BSupVector.Value(2);

      do
      {
        diff++;
        if ((NumSegOn2 - diff) <= 1)
        {
          BInfVector.Value(2) = Poly2.InfParameter();
          diff                = 0;
        }
        else
          BInfVector.Value(2) = Poly2.ApproxParamOnCurve(NumSegOn2 - diff, (double)0.0);
        IntCurve_ExactIntersectionPoint::MathPerform();

        if (diff > 3)
          diff += NumSegOn2 / 2;
      } while (nbroots == 0 && diff != 0);

      if (nbroots == 0)
      {
        BInfVector.Value(2) = AnBinfVector;
        diff                = 1;
        do
        {
          diff++;
          if ((NumSegOn2 + diff) >= (Poly2.NbSegments() - 1))
          {
            BSupVector.Value(2) = Poly2.SupParameter();
            diff                = 0;
          }
          else
            BSupVector.Value(2) = Poly2.ApproxParamOnCurve(NumSegOn2 + 1 + diff, (double)0.0);
          IntCurve_ExactIntersectionPoint::MathPerform();

          if (diff > 3)
            diff += 1 + (Poly2.NbSegments() - NumSegOn2) / 2;
        } while (nbroots == 0 && diff != 0);
      }
      BSupVector.Value(2) = AnBsupVector;
    }
  }
}

void IntCurve_ExactIntersectionPoint::Perform(const double Uo,
                                              const double Vo,
                                              const double UInf,
                                              const double VInf,
                                              const double USup,
                                              const double VSup)
{

  done = true;

  BInfVector.Value(1)    = UInf;
  BInfVector.Value(2)    = VInf;
  BSupVector.Value(1)    = USup;
  BSupVector.Value(2)    = VSup;
  StartingPoint.Value(1) = Uo;
  StartingPoint.Value(2) = Vo;

  IntCurve_ExactIntersectionPoint::MathPerform();
}

int IntCurve_ExactIntersectionPoint::NbRoots() const
{
  return (nbroots);
}

void IntCurve_ExactIntersectionPoint::Roots(double& U, double& V)
{
  U = Root.Value(1);
  V = Root.Value(2);
}

void IntCurve_ExactIntersectionPoint::MathPerform(void)
{
  math_FunctionSetRoot Fct(FctDist, ToleranceVector, 60);
  Fct.Perform(FctDist, StartingPoint, BInfVector, BSupVector);

  if (Fct.IsDone())
  {
    Fct.Root(Root);
    nbroots = 1;
    math_Vector XY(1, 2);
    FctDist.Value(Root, XY);
    double dist2 = ((XY(1) * XY(1) + XY(2) * XY(2)));

    if (dist2 > myTol)
    {
      nbroots = 0;
    }
  }
  else
  {
    anErrorOccurred = true;
    nbroots         = 0;
  }
}

bool IntCurve_ExactIntersectionPoint::AnErrorOccurred() const
{
  return anErrorOccurred;
}

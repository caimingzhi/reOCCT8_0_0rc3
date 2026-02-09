#include <LProp_Status.hpp>
#include <LProp_NotDefined.hpp>
#include <Standard_OutOfRange.hpp>

static const double MinStep = 1.0e-7;

LProp_CLProps::LProp_CLProps(const Curve& C, const double U, const int N, const double Resolution)
    : myCurve(C),
      myDerOrder(N),
      myCN(4),
      myLinTol(Resolution),
      myTangentStatus(LProp_Undecided)
{
  Standard_OutOfRange_Raise_if(N < 0 || N > 3, "LProp_CLProps::LProp_CLProps()");

  SetParameter(U);
}

LProp_CLProps::LProp_CLProps(const Curve& C, const int N, const double Resolution)
    : myCurve(C),
      myU(RealLast()),
      myDerOrder(N),
      myCN(4),
      myLinTol(Resolution),
      myTangentStatus(LProp_Undecided)
{
  Standard_OutOfRange_Raise_if(N < 0 || N > 3, "LProp_CLProps::LProp_CLProps()");
}

LProp_CLProps::LProp_CLProps(const int N, const double Resolution)
    : myU(RealLast()),
      myDerOrder(N),
      myCN(0),
      myLinTol(Resolution),
      myTangentStatus(LProp_Undecided)
{
  Standard_OutOfRange_Raise_if(N < 0 || N > 3, "LProp_CLProps() - invalid input");
}

void LProp_CLProps::SetParameter(const double U)
{
  myU = U;
  switch (myDerOrder)
  {
    case 0:
      Tool::Value(myCurve, myU, myPnt);
      break;
    case 1:
      Tool::D1(myCurve, myU, myPnt, myDerivArr[0]);
      break;
    case 2:
      Tool::D2(myCurve, myU, myPnt, myDerivArr[0], myDerivArr[1]);
      break;
    case 3:
      Tool::D3(myCurve, myU, myPnt, myDerivArr[0], myDerivArr[1], myDerivArr[2]);
      break;
  }

  myTangentStatus = LProp_Undecided;
}

void LProp_CLProps::SetCurve(const Curve& C)
{
  myCurve = C;
  myCN    = 4;
}

const Pnt& LProp_CLProps::Value() const
{
  return myPnt;
}

const Vec& LProp_CLProps::D1()
{
  if (myDerOrder < 1)
  {
    myDerOrder = 1;
    Tool::D1(myCurve, myU, myPnt, myDerivArr[0]);
  }

  return myDerivArr[0];
}

const Vec& LProp_CLProps::D2()
{
  if (myDerOrder < 2)
  {
    myDerOrder = 2;
    Tool::D2(myCurve, myU, myPnt, myDerivArr[0], myDerivArr[1]);
  }

  return myDerivArr[1];
}

const Vec& LProp_CLProps::D3()
{
  if (myDerOrder < 3)
  {
    myDerOrder = 3;
    Tool::D3(myCurve, myU, myPnt, myDerivArr[0], myDerivArr[1], myDerivArr[2]);
  }

  return myDerivArr[2];
}

bool LProp_CLProps::IsTangentDefined()
{
  if (myTangentStatus == LProp_Undefined)
    return false;
  else if (myTangentStatus >= LProp_Defined)
    return true;

  const double Tol = myLinTol * myLinTol;

  Vec V;

  int Order = 0;
  while (Order++ < 4)
  {
    if (myCN >= Order)
    {
      switch (Order)
      {
        case 1:
          V = D1();
          break;
        case 2:
          V = D2();
          break;
        case 3:
          V = D3();
          break;
      }

      if (V.SquareMagnitude() > Tol)
      {
        mySignificantFirstDerivativeOrder = Order;
        myTangentStatus                   = LProp_Defined;
        return true;
      }
    }
    else
    {
      myTangentStatus = LProp_Undefined;
      return false;
    }
  }

  return false;
}

void LProp_CLProps::Tangent(Dir& D)
{
  if (!IsTangentDefined())
    throw LProp_NotDefined();

  if (mySignificantFirstDerivativeOrder == 1)
    D = Dir(myDerivArr[0]);
  else if (mySignificantFirstDerivativeOrder > 1)
  {
    const double DivisionFactor = 1.e-3;
    const double anUsupremum    = Tool::LastParameter(myCurve),
                 anUinfium      = Tool::FirstParameter(myCurve);

    double du;
    if ((anUsupremum >= RealLast()) || (anUinfium <= RealFirst()))
      du = 0.0;
    else
      du = anUsupremum - anUinfium;

    const double aDelta = std::max(du * DivisionFactor, MinStep);

    Vec V = myDerivArr[mySignificantFirstDerivativeOrder - 1];

    double u;

    if (myU - anUinfium < aDelta)
      u = myU + aDelta;
    else
      u = myU - aDelta;

    Pnt P1, P2;
    Tool::Value(myCurve, std::min(myU, u), P1);
    Tool::Value(myCurve, std::max(myU, u), P2);

    Vec    V1(P1, P2);
    double aDirFactor = V.Dot(V1);

    if (aDirFactor < 0.0)
      V = -V;

    D = Dir(V);
  }
}

double LProp_CLProps::Curvature()
{
  bool isDefined = IsTangentDefined();
  (void)isDefined;

  LProp_NotDefined_Raise_if(!isDefined, "LProp_CLProps::CurvatureNotDefined()");

  if (mySignificantFirstDerivativeOrder > 1)
    return RealLast();

  double Tol = myLinTol * myLinTol;
  double DD1 = myDerivArr[0].SquareMagnitude();
  double DD2 = myDerivArr[1].SquareMagnitude();

  if (DD2 <= Tol)
  {
    myCurvature = 0.0;
  }
  else
  {
    double N = myDerivArr[0].CrossSquareMagnitude(myDerivArr[1]);

    double t = N / DD1 / DD2;
    if (t <= Tol)
    {
      myCurvature = 0.0;
    }
    else
    {
      myCurvature = sqrt(N) / DD1 / sqrt(DD1);
    }
  }

  return myCurvature;
}

void LProp_CLProps::Normal(Dir& D)
{
  double c = Curvature();
  if (c == RealLast() || std::abs(c) <= myLinTol)
  {
    throw LProp_NotDefined("LProp_CLProps::Normal(...):"
                           "Curvature is null or infinity");
  }

  Vec Norm = myDerivArr[1] * (myDerivArr[0] * myDerivArr[0])
             - myDerivArr[0] * (myDerivArr[0] * myDerivArr[1]);
  D = Dir(Norm);
}

void LProp_CLProps::CentreOfCurvature(Pnt& P)
{
  if (std::abs(Curvature()) <= myLinTol)
  {
    throw LProp_NotDefined();
  }

  Vec Norm = myDerivArr[1] * (myDerivArr[0] * myDerivArr[0])
             - myDerivArr[0] * (myDerivArr[0] * myDerivArr[1]);
  Norm.Normalize();
  Norm.Divide(myCurvature);
  P = myPnt.Translated(Norm);
}

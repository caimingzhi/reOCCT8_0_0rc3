

#include <math_BissecNewton.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <StdFail_NotDone.hpp>

math_BissecNewton::math_BissecNewton(const double theXTolerance)
    : TheStatus(math_NotBracketed),
      XTol(theXTolerance),
      x(0.0),
      dx(0.0),
      f(0.0),
      df(0.0),
      Done(false)
{
}

math_BissecNewton::~math_BissecNewton() = default;

void math_BissecNewton::Perform(math_FunctionWithDerivative& F,
                                const double                 Bound1,
                                const double                 Bound2,
                                const int                    NbIterations)
{
  bool   GOOD;
  int    j;
  double dxold, fh, fl;
  double temp, xh, xl;

  GOOD = F.Values(Bound1, fl, df);
  if (!GOOD)
  {
    Done      = false;
    TheStatus = math_FunctionError;
    return;
  }
  GOOD = F.Values(Bound2, fh, df);
  if (!GOOD)
  {
    Done      = false;
    TheStatus = math_FunctionError;
    return;
  }

  constexpr double aFTol = RealEpsilon();

  if (fl * fh > aFTol * aFTol)
  {
    Done      = false;
    TheStatus = math_NotBracketed;
    return;
  }

  if (fl < -aFTol || (fl < aFTol && fh < -aFTol))
  {
    xl = Bound1;
    xh = Bound2;
  }
  else
  {
    xl = Bound2;
    xh = Bound1;
  }

  x     = 0.5 * (Bound1 + Bound2);
  dxold = fabs(Bound2 - Bound1);
  dx    = dxold;
  GOOD  = F.Values(x, f, df);
  if (!GOOD)
  {
    Done      = false;
    TheStatus = math_FunctionError;
    return;
  }
  for (j = 1; j <= NbIterations; j++)
  {
    if ((((x - xh) * df - f) * ((x - xl) * df - f) >= 0.0) || (fabs(2.0 * f) > fabs(dxold * df)))
    {
      dxold = dx;
      dx    = 0.5 * (xh - xl);
      x     = xl + dx;
      if (std::abs(dx) < XTol)
      {
        TheStatus = math_OK;
        Done      = true;
        return;
      }
    }
    else
    {
      dxold = dx;
      dx    = f / df;
      temp  = x;
      x -= dx;
      if (temp == x)
      {
        TheStatus = math_OK;
        Done      = true;
        return;
      }
    }
    if (IsSolutionReached(F))
    {
      TheStatus = math_OK;
      Done      = true;
      return;
    }
    GOOD = F.Values(x, f, df);
    if (!GOOD)
    {
      Done      = false;
      TheStatus = math_FunctionError;
      return;
    }
    if (f < 0.0)
    {
      xl = x;
    }
    else if (f > 0.0)
    {
      xh = x;
    }
    else
    {
      TheStatus = math_OK;
      Done      = true;
      return;
    }
  }
  TheStatus = math_TooManyIterations;
  Done      = false;
  return;
}

void math_BissecNewton::Dump(Standard_OStream& o) const
{

  o << "math_BissecNewton ";
  if (Done)
  {
    o << " Status = Done \n";
    o << " The Root  is: " << x << std::endl;
    o << " The value at this Root is: " << f << std::endl;
  }
  else
  {
    o << " Status = not Done \n";
  }
}

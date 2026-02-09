

#include <math_BracketedRoot.hpp>
#include <math_Function.hpp>
#include <StdFail_NotDone.hpp>

math_BracketedRoot::math_BracketedRoot(math_Function& F,
                                       const double   Bound1,
                                       const double   Bound2,
                                       const double   Tolerance,
                                       const int      NbIterations,
                                       const double   ZEPS)
{

  double Fa, Fc, a, c = 0, d = 0, e = 0;
  double min1, min2, p, q, r, s, tol1, xm;

  a       = Bound1;
  TheRoot = Bound2;
  F.Value(a, Fa);
  F.Value(TheRoot, TheError);
  if (Fa * TheError > 0.)
  {
    Done = false;
  }
  else
  {
    Fc = TheError;
    for (NbIter = 1; NbIter <= NbIterations; NbIter++)
    {
      if (TheError * Fc > 0.)
      {
        c  = a;
        Fc = Fa;
        d  = TheRoot - a;
        e  = d;
      }
      if (std::abs(Fc) < std::abs(Fa))
      {
        a        = TheRoot;
        TheRoot  = c;
        c        = a;
        Fa       = TheError;
        TheError = Fc;
        Fc       = Fa;
      }
      tol1 = 2. * ZEPS * std::abs(TheRoot) + 0.5 * Tolerance;
      xm   = 0.5 * (c - TheRoot);
      if (std::abs(xm) <= tol1 || TheError == 0.)
      {
        Done = true;
        return;
      }
      if (std::abs(e) >= tol1 && std::abs(Fa) > std::abs(TheError))
      {
        s = TheError / Fa;
        if (a == c)
        {
          p = 2. * xm * s;
          q = 1. - s;
        }
        else
        {
          q = Fa / Fc;
          r = TheError / Fc;
          p = s * (2. * xm * q * (q - r) - (TheRoot - a) * (r - 1.));
          q = (q - 1.) * (r - 1.) * (s - 1.);
        }
        if (p > 0.)
        {
          q = -q;
        }
        p    = std::abs(p);
        min1 = 3. * xm * q - std::abs(tol1 * q);
        min2 = std::abs(e * q);
        if (2. * p < (min1 < min2 ? min1 : min2))
        {
          e = d;
          d = p / q;
        }
        else
        {
          d = xm;
          e = d;
        }
      }
      else
      {
        d = xm;
        e = d;
      }
      a  = TheRoot;
      Fa = TheError;
      if (std::abs(d) > tol1)
      {
        TheRoot += d;
      }
      else
      {
        TheRoot += (xm > 0. ? std::abs(tol1) : -std::abs(tol1));
      }
      F.Value(TheRoot, TheError);
    }
    Done = false;
  }
}

void math_BracketedRoot::Dump(Standard_OStream& o) const
{

  o << "math_BracketedRoot ";
  if (Done)
  {
    o << " Status = Done \n";
    o << " Number of iterations = " << NbIter << std::endl;
    o << " The Root is: " << TheRoot << std::endl;
    o << " The value at the root is: " << TheError << std::endl;
  }
  else
  {
    o << " Status = not Done \n";
  }
}



#include <math_FunctionWithDerivative.hpp>
#include <math_NewtonFunctionRoot.hpp>
#include <StdFail_NotDone.hpp>

math_NewtonFunctionRoot::math_NewtonFunctionRoot(math_FunctionWithDerivative& F,
                                                 const double                 Guess,
                                                 const double                 EpsX,
                                                 const double                 EpsF,
                                                 const double                 A,
                                                 const double                 B,
                                                 const int                    NbIterations)
{
  EpsilonX = EpsX;
  EpsilonF = EpsF;
  Binf     = A;
  Bsup     = B;
  Itermax  = NbIterations;
  Done     = false;
  X        = RealLast();
  DFx      = 0;
  Fx       = RealLast();
  It       = 0;
  Perform(F, Guess);
}

math_NewtonFunctionRoot::math_NewtonFunctionRoot(const double A,
                                                 const double B,
                                                 const double EpsX,
                                                 const double EpsF,
                                                 const int    NbIterations)
{

  Binf     = A;
  Bsup     = B;
  EpsilonX = EpsX;
  EpsilonF = EpsF;
  Itermax  = NbIterations;
  Done     = false;
  X        = RealLast();
  DFx      = 0;
  Fx       = RealLast();
  It       = 0;
}

math_NewtonFunctionRoot::math_NewtonFunctionRoot(math_FunctionWithDerivative& F,
                                                 const double                 Guess,
                                                 const double                 EpsX,
                                                 const double                 EpsF,
                                                 const int                    NbIterations)
{
  EpsilonX = EpsX;
  EpsilonF = EpsF;
  Itermax  = NbIterations;
  Binf     = RealFirst();
  Bsup     = RealLast();
  Done     = false;
  X        = RealLast();
  DFx      = 0;
  Fx       = RealLast();
  It       = 0;
  Perform(F, Guess);
}

void math_NewtonFunctionRoot::Perform(math_FunctionWithDerivative& F, const double Guess)
{

  double Dx;
  bool   Ok;
  double AA, BB;

  double BestX = X, BestFx = RealLast();

  if (Binf < Bsup)
  {
    AA = Binf;
    BB = Bsup;
  }
  else
  {
    AA = Bsup;
    BB = Binf;
  }

  Dx = RealLast();
  Fx = RealLast();
  X  = Guess;
  It = 1;
  while ((It <= Itermax) && ((std::abs(Dx) > EpsilonX) || (std::abs(Fx) > EpsilonF)))
  {
    Ok = F.Values(X, Fx, DFx);

    double AbsFx = Fx;
    if (AbsFx < 0)
      AbsFx = -AbsFx;
    if (AbsFx < BestFx)
    {
      BestFx = AbsFx;
      BestX  = X;
    }

    if (Ok)
    {
      if (DFx == 0.)
      {
        Done = false;
        It   = Itermax + 1;
      }
      else
      {
        Dx = Fx / DFx;
        X -= Dx;

        if (X <= AA)
          X = AA;
        if (X >= BB)
          X = BB;
        It++;
      }
    }
    else
    {
      Done = false;
      It   = Itermax + 1;
    }
  }
  X = BestX;

  Done = It <= Itermax;
}

void math_NewtonFunctionRoot::Dump(Standard_OStream& o) const
{

  o << "math_NewtonFunctionRoot ";
  if (Done)
  {
    o << " Status = Done \n";
    o << " Location found = " << X << "\n";
    o << " function value at this minimum = " << Fx << "\n";
    o << " Number of iterations = " << It << "\n";
  }
  else
  {
    o << "Status = not Done \n";
  }
}

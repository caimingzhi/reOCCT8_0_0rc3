#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <IntImp_ComputeTangence.hpp>
#include <math_FunctionSetRoot.hpp>
#include <Precision.hpp>

IntImp_IntCS::IntImp_IntCS(const double       U,
                           const double       V,
                           const double       W,
                           const TheFunction& F,
                           const double       TolTangency,
                           const double       MarginCoef)
    : done(true),
      empty(true),
      myFunction(F),
      w(0.0),
      u(0.0),
      v(0.0),
      tol(TolTangency * TolTangency)
{
  if (tol < 1e-13)
  {
    tol = 1e-13;
  }
  math_FunctionSetRoot Rsnld(myFunction);
  double               u0, u1, v0, v1, w0, w1;
  const ThePSurface&   S = myFunction.AuxillarSurface();
  const TheCurve&      C = myFunction.AuxillarCurve();

  w0 = TheCurveTool::FirstParameter(C);
  w1 = TheCurveTool::LastParameter(C);

  u0 = ThePSurfaceTool::FirstUParameter(S);
  v0 = ThePSurfaceTool::FirstVParameter(S);
  u1 = ThePSurfaceTool::LastUParameter(S);
  v1 = ThePSurfaceTool::LastVParameter(S);

  if (MarginCoef > 0.)
  {
    if (!Precision::IsInfinite(u0) && !Precision::IsInfinite(u1))
    {
      double marg = (u1 - u0) * MarginCoef;
      if (u0 > u1)
        marg = -marg;
      u0 -= marg;
      u1 += marg;
    }
    if (!Precision::IsInfinite(v0) && !Precision::IsInfinite(v1))
    {
      double marg = (v1 - v0) * MarginCoef;
      if (v0 > v1)
        marg = -marg;
      v0 -= marg;
      v1 += marg;
    }
  }

  Perform(U, V, W, Rsnld, u0, u1, v0, v1, w0, w1);
}

IntImp_IntCS::IntImp_IntCS(const TheFunction& F, const double TolTangency)
    : done(true),
      empty(true),
      myFunction(F),
      tol(TolTangency * TolTangency)
{
}

void IntImp_IntCS::Perform(const double          U,
                           const double          V,
                           const double          W,
                           math_FunctionSetRoot& Rsnld,
                           const double          u0,
                           const double          u1,
                           const double          v0,
                           const double          v1,
                           const double          w0,
                           const double          w1)
{
  done = true;
  double      BornInfBuf[3], BornSupBuf[3], ToleranceBuf[3], UVapBuf[3];
  math_Vector BornInf(BornInfBuf, 1, 3), BornSup(BornSupBuf, 1, 3), Tolerance(ToleranceBuf, 1, 3),
    UVap(UVapBuf, 1, 3);
  UVap(1)              = U;
  UVap(2)              = V;
  UVap(3)              = W;
  const ThePSurface& S = myFunction.AuxillarSurface();
  const TheCurve&    C = myFunction.AuxillarCurve();

  BornInf(1) = u0;
  BornInf(2) = v0;
  BornSup(1) = u1;
  BornSup(2) = v1;

  BornInf(3) = w0;
  BornSup(3) = w1;

  Tolerance(1) = ThePSurfaceTool::UResolution(S, Precision::Confusion());
  Tolerance(2) = ThePSurfaceTool::VResolution(S, Precision::Confusion());
  Tolerance(3) = TheCurveTool::Resolution(C, Precision::Confusion());
  Rsnld.SetTolerance(Tolerance);
  int autretentative = 0;
  done               = false;
  do
  {
    if (autretentative == 1)
    {
      UVap(3) = w0;
    }
    else if (autretentative == 2)
    {
      UVap(3) = w1;
    }
    autretentative++;
    Rsnld.Perform(myFunction, UVap, BornInf, BornSup);
    if (Rsnld.IsDone())
    {
      double AbsmyFunctionRoot = std::abs(myFunction.Root());
      if (AbsmyFunctionRoot <= tol)
      {
        Rsnld.Root(UVap);
        u     = UVap(1);
        v     = UVap(2);
        w     = UVap(3);
        empty = false;
        done  = true;
      }
    }
  } while (done == false && autretentative < 3);
}

bool IntImp_IntCS::IsDone() const
{
  return done;
}

bool IntImp_IntCS::IsEmpty() const
{
  if (!done)
    throw StdFail_NotDone();
  return empty;
}

const gp_Pnt& IntImp_IntCS::Point() const
{
  if (!done)
    throw StdFail_NotDone();
  if (empty)
    throw Standard_DomainError();
  return myFunction.Point();
}

void IntImp_IntCS::ParameterOnSurface(double& U, double& V) const
{
  if (!done)
    throw StdFail_NotDone();
  if (empty)
    throw Standard_DomainError();
  U = u;
  V = v;
}

double IntImp_IntCS::ParameterOnCurve() const
{
  if (!done)
    throw StdFail_NotDone();
  if (empty)
    throw Standard_DomainError();
  return w;
}

TheFunction& IntImp_IntCS::Function()
{
  return myFunction;
}

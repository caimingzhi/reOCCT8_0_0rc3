#include <StdFail_UndefinedDerivative.hpp>

inline void IntImp_ZerImpFunc::Set(const ThePSurface& PS)
{
  surf = (void*)(&PS);
}

inline void IntImp_ZerImpFunc::SetImplicitSurface(const TheISurface& IS)
{
  func = (void*)(&IS);
}

inline void IntImp_ZerImpFunc::Set(const double Tol)
{
  tol = Tol;
}

inline double IntImp_ZerImpFunc::Root() const
{
  return valf;
}

inline double IntImp_ZerImpFunc::Tolerance() const
{
  return tol;
}

inline const gp_Pnt& IntImp_ZerImpFunc::Point() const
{
  return pntsol;
}

inline const gp_Vec& IntImp_ZerImpFunc::Direction3d()
{
  if (IsTangent())
    throw StdFail_UndefinedDerivative();
  return d3d;
}

inline const gp_Dir2d& IntImp_ZerImpFunc::Direction2d()
{
  if (IsTangent())
    throw StdFail_UndefinedDerivative();
  return d2d;
}

inline const ThePSurface& IntImp_ZerImpFunc::PSurface() const
{
  return (*((ThePSurface*)(surf)));
}

inline const TheISurface& IntImp_ZerImpFunc::ISurface() const
{
  return (*((TheISurface*)(func)));
}

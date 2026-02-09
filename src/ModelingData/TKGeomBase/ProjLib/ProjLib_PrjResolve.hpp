#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt2d.hpp>

class Adaptor3d_Curve;
class Adaptor3d_Surface;

class ProjLib_PrjResolve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ProjLib_PrjResolve(const Adaptor3d_Curve&   C,
                                     const Adaptor3d_Surface& S,
                                     const int                Fix);

  Standard_EXPORT void Perform(const double    t,
                               const double    U,
                               const double    V,
                               const gp_Pnt2d& Tol,
                               const gp_Pnt2d& Inf,
                               const gp_Pnt2d& Sup,
                               const double    FTol         = -1,
                               const bool      StrictInside = false);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT gp_Pnt2d Solution() const;

private:
  const Adaptor3d_Curve*   myCurve;
  const Adaptor3d_Surface* mySurface;
  bool                     myDone;
  gp_Pnt2d                 mySolution;
  int                      myFix;
};

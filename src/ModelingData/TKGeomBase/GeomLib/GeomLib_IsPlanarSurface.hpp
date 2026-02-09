#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pln.hpp>
class Geom_Surface;

class GeomLib_IsPlanarSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_IsPlanarSurface(const occ::handle<Geom_Surface>& S,
                                          const double                     Tol = 1.0e-7);

  Standard_EXPORT bool IsPlanar() const;

  Standard_EXPORT const gp_Pln& Plan() const;

private:
  gp_Pln myPlan;
  bool   IsPlan;
};

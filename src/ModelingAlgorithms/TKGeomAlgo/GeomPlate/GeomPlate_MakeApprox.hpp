#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class GeomPlate_Surface;
class Geom_BSplineSurface;
class AdvApp2Var_Criterion;

class GeomPlate_MakeApprox
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomPlate_MakeApprox(const occ::handle<GeomPlate_Surface>& SurfPlate,
                                       const AdvApp2Var_Criterion&           PlateCrit,
                                       const double                          Tol3d,
                                       const int                             Nbmax,
                                       const int                             dgmax,
                                       const GeomAbs_Shape Continuity   = GeomAbs_C1,
                                       const double        EnlargeCoeff = 1.1);

  Standard_EXPORT GeomPlate_MakeApprox(const occ::handle<GeomPlate_Surface>& SurfPlate,
                                       const double                          Tol3d,
                                       const int                             Nbmax,
                                       const int                             dgmax,
                                       const double                          dmax,
                                       const int                             CritOrder = 0,
                                       const GeomAbs_Shape Continuity                  = GeomAbs_C1,
                                       const double        EnlargeCoeff                = 1.1);

  Standard_EXPORT occ::handle<Geom_BSplineSurface> Surface() const;

  Standard_EXPORT double ApproxError() const;

  Standard_EXPORT double CriterionError() const;

private:
  occ::handle<GeomPlate_Surface>   myPlate;
  occ::handle<Geom_BSplineSurface> mySurface;
  double                           myAppError;
  double                           myCritError;
};

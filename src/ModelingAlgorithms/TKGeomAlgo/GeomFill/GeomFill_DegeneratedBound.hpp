#pragma once

#include <Standard.hpp>

#include <gp_Pnt.hpp>
#include <Standard_Real.hpp>
#include <GeomFill_Boundary.hpp>
class gp_Vec;

class GeomFill_DegeneratedBound : public GeomFill_Boundary
{

public:
  Standard_EXPORT GeomFill_DegeneratedBound(const gp_Pnt& Point,
                                            const double  First,
                                            const double  Last,
                                            const double  Tol3d,
                                            const double  Tolang);

  Standard_EXPORT gp_Pnt Value(const double U) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V) const override;

  Standard_EXPORT void Reparametrize(const double First,
                                     const double Last,
                                     const bool   HasDF,
                                     const bool   HasDL,
                                     const double DF,
                                     const double DL,
                                     const bool   Rev) override;

  Standard_EXPORT void Bounds(double& First, double& Last) const override;

  Standard_EXPORT bool IsDegenerated() const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_DegeneratedBound, GeomFill_Boundary)

private:
  gp_Pnt myPoint;
  double myFirst;
  double myLast;
};

#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomFill_Boundary.hpp>

class Law_Function;
class gp_Pnt;
class gp_Vec;

class GeomFill_SimpleBound : public GeomFill_Boundary
{

public:
  Standard_EXPORT GeomFill_SimpleBound(const occ::handle<Adaptor3d_Curve>& Curve,
                                       const double                        Tol3d,
                                       const double                        Tolang);

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

  DEFINE_STANDARD_RTTIEXT(GeomFill_SimpleBound, GeomFill_Boundary)

private:
  occ::handle<Adaptor3d_Curve> myC3d;
  occ::handle<Law_Function>    myPar;
};

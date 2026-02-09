#pragma once

#include <Standard.hpp>

#include <Adaptor3d_CurveOnSurface.hpp>
#include <GeomFill_Boundary.hpp>
#include <Standard_Real.hpp>
class Law_Function;
class gp_Pnt;
class gp_Vec;

class GeomFill_BoundWithSurf : public GeomFill_Boundary
{

public:
  Standard_EXPORT GeomFill_BoundWithSurf(const Adaptor3d_CurveOnSurface& CurveOnSurf,
                                         const double                    Tol3d,
                                         const double                    Tolang);

  Standard_EXPORT gp_Pnt Value(const double U) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V) const override;

  Standard_EXPORT bool HasNormals() const override;

  Standard_EXPORT gp_Vec Norm(const double U) const override;

  Standard_EXPORT void D1Norm(const double U, gp_Vec& N, gp_Vec& DN) const override;

  Standard_EXPORT void Reparametrize(const double First,
                                     const double Last,
                                     const bool   HasDF,
                                     const bool   HasDL,
                                     const double DF,
                                     const double DL,
                                     const bool   Rev) override;

  Standard_EXPORT void Bounds(double& First, double& Last) const override;

  Standard_EXPORT bool IsDegenerated() const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_BoundWithSurf, GeomFill_Boundary)

private:
  Adaptor3d_CurveOnSurface  myConS;
  occ::handle<Law_Function> myPar;
};

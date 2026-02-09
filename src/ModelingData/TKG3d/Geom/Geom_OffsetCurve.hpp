#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Dir.hpp>
#include <GeomAbs_Shape.hpp>
#include <Geom_Curve.hpp>
#include <Standard_Integer.hpp>

class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class Geom_Geometry;

class Geom_OffsetCurve : public Geom_Curve
{

public:
  Standard_EXPORT Geom_OffsetCurve(const occ::handle<Geom_Curve>& C,
                                   const double                   Offset,
                                   const gp_Dir&                  V,
                                   const bool                     isNotCheckC0 = false);

  Standard_EXPORT Geom_OffsetCurve(const Geom_OffsetCurve& theOther);

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT void SetBasisCurve(const occ::handle<Geom_Curve>& C,
                                     const bool                     isNotCheckC0 = false);

  Standard_EXPORT void SetDirection(const gp_Dir& V);

  Standard_EXPORT void SetOffsetValue(const double D);

  Standard_EXPORT occ::handle<Geom_Curve> BasisCurve() const;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT const gp_Dir& Direction() const;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT double Offset() const;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT double TransformedParameter(const double U, const gp_Trsf& T) const override;

  Standard_EXPORT double ParametricTransformation(const gp_Trsf& T) const override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT GeomAbs_Shape GetBasisCurveContinuity() const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_OffsetCurve, Geom_Curve)

private:
  occ::handle<Geom_Curve> basisCurve;
  gp_Dir                  direction;
  double                  offsetValue;
  GeomAbs_Shape           myBasisCurveContinuity;
};

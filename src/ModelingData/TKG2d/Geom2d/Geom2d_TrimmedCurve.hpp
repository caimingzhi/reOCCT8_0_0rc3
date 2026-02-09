#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_BoundedCurve.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
class Geom2d_Curve;
class gp_Pnt2d;
class gp_Vec2d;
class gp_Trsf2d;
class Geom2d_Geometry;

class Geom2d_TrimmedCurve : public Geom2d_BoundedCurve
{

public:
  Standard_EXPORT Geom2d_TrimmedCurve(const occ::handle<Geom2d_Curve>& C,
                                      const double                     U1,
                                      const double                     U2,
                                      const bool                       Sense             = true,
                                      const bool                       theAdjustPeriodic = true);

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT void SetTrim(const double U1,
                               const double U2,
                               const bool   Sense             = true,
                               const bool   theAdjustPeriodic = true);

  Standard_EXPORT occ::handle<Geom2d_Curve> BasisCurve() const;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT gp_Pnt2d EndPoint() const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT double Period() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT gp_Pnt2d StartPoint() const override;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT double TransformedParameter(const double U, const gp_Trsf2d& T) const override;

  Standard_EXPORT double ParametricTransformation(const gp_Trsf2d& T) const override;

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_TrimmedCurve, Geom2d_BoundedCurve)

private:
  occ::handle<Geom2d_Curve> basisCurve;
  double                    uTrim1;
  double                    uTrim2;
};

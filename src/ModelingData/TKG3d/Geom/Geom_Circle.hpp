#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Conic.hpp>
#include <Standard_Integer.hpp>
class gp_Circ;
class gp_Ax2;
class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class Geom_Geometry;

class Geom_Circle : public Geom_Conic
{

public:
  Standard_EXPORT Geom_Circle(const gp_Circ& C);

  Standard_EXPORT Geom_Circle(const gp_Ax2& A2, const double Radius);

  Standard_EXPORT void SetCirc(const gp_Circ& C);

  Standard_EXPORT void SetRadius(const double R);

  Standard_EXPORT gp_Circ Circ() const;

  Standard_EXPORT double Radius() const;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT double Eccentricity() const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_Circle, Geom_Conic)

private:
  double radius;
};

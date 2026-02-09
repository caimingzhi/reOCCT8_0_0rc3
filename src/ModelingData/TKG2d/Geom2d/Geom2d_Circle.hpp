#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Conic.hpp>
#include <Standard_Integer.hpp>
class gp_Circ2d;
class gp_Ax2d;
class gp_Ax22d;
class gp_Pnt2d;
class gp_Vec2d;
class gp_Trsf2d;
class Geom2d_Geometry;

class Geom2d_Circle : public Geom2d_Conic
{

public:
  Standard_EXPORT Geom2d_Circle(const gp_Circ2d& C);

  Standard_EXPORT Geom2d_Circle(const gp_Ax2d& A, const double Radius, const bool Sense = true);

  Standard_EXPORT Geom2d_Circle(const gp_Ax22d& A, const double Radius);

  Standard_EXPORT void SetCirc2d(const gp_Circ2d& C);

  Standard_EXPORT void SetRadius(const double R);

  Standard_EXPORT gp_Circ2d Circ2d() const;

  Standard_EXPORT double Radius() const;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT double Eccentricity() const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

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

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Circle, Geom2d_Conic)

private:
  double radius;
};

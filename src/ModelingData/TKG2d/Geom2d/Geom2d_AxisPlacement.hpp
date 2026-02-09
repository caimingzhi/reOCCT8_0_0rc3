#pragma once

#include <Standard.hpp>

#include <gp_Ax2d.hpp>
#include <Geom2d_Geometry.hpp>
#include <Standard_Real.hpp>
class gp_Pnt2d;
class gp_Dir2d;
class gp_Trsf2d;

class Geom2d_AxisPlacement : public Geom2d_Geometry
{

public:
  Standard_EXPORT Geom2d_AxisPlacement(const gp_Ax2d& A);

  Standard_EXPORT Geom2d_AxisPlacement(const gp_Pnt2d& P, const gp_Dir2d& V);

  Standard_EXPORT void Reverse();

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_AxisPlacement> Reversed() const;

  Standard_EXPORT void SetAxis(const gp_Ax2d& A);

  Standard_EXPORT void SetDirection(const gp_Dir2d& V);

  Standard_EXPORT void SetLocation(const gp_Pnt2d& P);

  Standard_EXPORT double Angle(const occ::handle<Geom2d_AxisPlacement>& Other) const;

  Standard_EXPORT gp_Ax2d Ax2d() const;

  Standard_EXPORT gp_Dir2d Direction() const;

  Standard_EXPORT gp_Pnt2d Location() const;

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_AxisPlacement, Geom2d_Geometry)

private:
  gp_Ax2d axis;
};

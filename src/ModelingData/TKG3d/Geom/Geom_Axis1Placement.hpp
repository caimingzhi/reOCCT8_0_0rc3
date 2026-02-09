#pragma once

#include <Standard.hpp>

#include <Geom_AxisPlacement.hpp>
class gp_Ax1;
class gp_Pnt;
class gp_Dir;
class gp_Trsf;
class Geom_Geometry;

class Geom_Axis1Placement : public Geom_AxisPlacement
{

public:
  Standard_EXPORT Geom_Axis1Placement(const gp_Ax1& A1);

  Standard_EXPORT Geom_Axis1Placement(const gp_Pnt& P, const gp_Dir& V);

  Standard_EXPORT const gp_Ax1& Ax1() const;

  Standard_EXPORT void Reverse();

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Axis1Placement> Reversed() const;

  Standard_EXPORT void SetDirection(const gp_Dir& V) override;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom_Axis1Placement, Geom_AxisPlacement)
};

#pragma once

#include <Standard.hpp>

#include <Geom_AxisPlacement.hpp>
class gp_Ax2;
class gp_Pnt;
class gp_Trsf;
class Geom_Geometry;

class Geom_Axis2Placement : public Geom_AxisPlacement
{

public:
  Standard_EXPORT Geom_Axis2Placement(const gp_Ax2& A2);

  Standard_EXPORT Geom_Axis2Placement(const gp_Pnt& P, const gp_Dir& N, const gp_Dir& Vx);

  Standard_EXPORT void SetAx2(const gp_Ax2& A2);

  Standard_EXPORT void SetDirection(const gp_Dir& V) override;

  Standard_EXPORT void SetXDirection(const gp_Dir& Vx);

  Standard_EXPORT void SetYDirection(const gp_Dir& Vy);

  Standard_EXPORT gp_Ax2 Ax2() const;

  Standard_EXPORT const gp_Dir& XDirection() const;

  Standard_EXPORT const gp_Dir& YDirection() const;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom_Axis2Placement, Geom_AxisPlacement)

private:
  Standard_EXPORT Geom_Axis2Placement(const gp_Pnt& P,
                                      const gp_Dir& Vz,
                                      const gp_Dir& Vx,
                                      const gp_Dir& Vy);

  gp_Dir vxdir;
  gp_Dir vydir;
};

#pragma once

#include <Standard.hpp>

#include <gp_Ax1.hpp>
#include <Geom_Geometry.hpp>
#include <Standard_Real.hpp>
class gp_Dir;
class gp_Pnt;

class Geom_AxisPlacement : public Geom_Geometry
{

public:
  Standard_EXPORT void SetAxis(const gp_Ax1& A1);

  Standard_EXPORT virtual void SetDirection(const gp_Dir& V) = 0;

  Standard_EXPORT void SetLocation(const gp_Pnt& P);

  Standard_EXPORT double Angle(const occ::handle<Geom_AxisPlacement>& Other) const;

  Standard_EXPORT const gp_Ax1& Axis() const;

  Standard_EXPORT gp_Dir Direction() const;

  Standard_EXPORT gp_Pnt Location() const;

  DEFINE_STANDARD_RTTIEXT(Geom_AxisPlacement, Geom_Geometry)

protected:
  gp_Ax1 axis;
};

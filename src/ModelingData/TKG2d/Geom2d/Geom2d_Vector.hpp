#pragma once

#include <Standard.hpp>

#include <gp_Vec2d.hpp>
#include <Geom2d_Geometry.hpp>
#include <Standard_Real.hpp>

class Geom2d_Vector : public Geom2d_Geometry
{

public:
  Standard_EXPORT void Reverse();

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Vector> Reversed() const;

  Standard_EXPORT double Angle(const occ::handle<Geom2d_Vector>& Other) const;

  Standard_EXPORT void Coord(double& X, double& Y) const;

  Standard_EXPORT virtual double Magnitude() const = 0;

  Standard_EXPORT virtual double SquareMagnitude() const = 0;

  Standard_EXPORT double X() const;

  Standard_EXPORT double Y() const;

  Standard_EXPORT virtual double Crossed(const occ::handle<Geom2d_Vector>& Other) const = 0;

  Standard_EXPORT double Dot(const occ::handle<Geom2d_Vector>& Other) const;

  Standard_EXPORT gp_Vec2d Vec2d() const;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Vector, Geom2d_Geometry)

protected:
  gp_Vec2d gpVec2d;
};

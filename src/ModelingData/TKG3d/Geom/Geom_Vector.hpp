#pragma once

#include <Standard.hpp>

#include <gp_Vec.hpp>
#include <Geom_Geometry.hpp>
#include <Standard_Real.hpp>

class Geom_Vector : public Geom_Geometry
{

public:
  Standard_EXPORT void Reverse();

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_Vector> Reversed() const;

  Standard_EXPORT double Angle(const occ::handle<Geom_Vector>& Other) const;

  Standard_EXPORT double AngleWithRef(const occ::handle<Geom_Vector>& Other,
                                      const occ::handle<Geom_Vector>& VRef) const;

  Standard_EXPORT void Coord(double& X, double& Y, double& Z) const;

  Standard_EXPORT virtual double Magnitude() const = 0;

  Standard_EXPORT virtual double SquareMagnitude() const = 0;

  Standard_EXPORT double X() const;

  Standard_EXPORT double Y() const;

  Standard_EXPORT double Z() const;

  Standard_EXPORT virtual void Cross(const occ::handle<Geom_Vector>& Other) = 0;

  Standard_EXPORT virtual occ::handle<Geom_Vector> Crossed(
    const occ::handle<Geom_Vector>& Other) const = 0;

  Standard_EXPORT virtual void CrossCross(const occ::handle<Geom_Vector>& V1,
                                          const occ::handle<Geom_Vector>& V2) = 0;

  Standard_EXPORT virtual occ::handle<Geom_Vector> CrossCrossed(
    const occ::handle<Geom_Vector>& V1,
    const occ::handle<Geom_Vector>& V2) const = 0;

  Standard_EXPORT double Dot(const occ::handle<Geom_Vector>& Other) const;

  Standard_EXPORT double DotCross(const occ::handle<Geom_Vector>& V1,
                                  const occ::handle<Geom_Vector>& V2) const;

  Standard_EXPORT const gp_Vec& Vec() const;

  DEFINE_STANDARD_RTTIEXT(Geom_Vector, Geom_Geometry)

protected:
  gp_Vec gpVec;
};

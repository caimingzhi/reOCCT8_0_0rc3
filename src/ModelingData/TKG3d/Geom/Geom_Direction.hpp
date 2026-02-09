#pragma once

#include <Standard.hpp>

#include <Geom_Vector.hpp>
#include <Standard_Real.hpp>
class gp_Dir;
class gp_Trsf;
class Geom_Geometry;

class Geom_Direction : public Geom_Vector
{

public:
  Standard_EXPORT Geom_Direction(const double X, const double Y, const double Z);

  Standard_EXPORT Geom_Direction(const gp_Dir& V);

  Standard_EXPORT void SetCoord(const double X, const double Y, const double Z);

  Standard_EXPORT void SetDir(const gp_Dir& V);

  Standard_EXPORT void SetX(const double X);

  Standard_EXPORT void SetY(const double Y);

  Standard_EXPORT void SetZ(const double Z);

  Standard_EXPORT gp_Dir Dir() const;

  Standard_EXPORT double Magnitude() const override;

  Standard_EXPORT double SquareMagnitude() const override;

  Standard_EXPORT void Cross(const occ::handle<Geom_Vector>& Other) override;

  Standard_EXPORT void CrossCross(const occ::handle<Geom_Vector>& V1,
                                  const occ::handle<Geom_Vector>& V2) override;

  Standard_EXPORT occ::handle<Geom_Vector> Crossed(
    const occ::handle<Geom_Vector>& Other) const override;

  Standard_EXPORT occ::handle<Geom_Vector> CrossCrossed(
    const occ::handle<Geom_Vector>& V1,
    const occ::handle<Geom_Vector>& V2) const override;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom_Direction, Geom_Vector)
};

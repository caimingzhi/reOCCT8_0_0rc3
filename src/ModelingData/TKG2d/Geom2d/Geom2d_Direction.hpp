#pragma once

#include <Standard.hpp>

#include <Geom2d_Vector.hpp>
#include <Standard_Real.hpp>
class gp_Dir2d;
class gp_Trsf2d;
class Geom2d_Geometry;

class Geom2d_Direction : public Geom2d_Vector
{

public:
  Standard_EXPORT Geom2d_Direction(const double X, const double Y);

  Standard_EXPORT Geom2d_Direction(const gp_Dir2d& V);

  Standard_EXPORT void SetCoord(const double X, const double Y);

  Standard_EXPORT void SetDir2d(const gp_Dir2d& V);

  Standard_EXPORT void SetX(const double X);

  Standard_EXPORT void SetY(const double Y);

  Standard_EXPORT gp_Dir2d Dir2d() const;

  Standard_EXPORT double Magnitude() const override;

  Standard_EXPORT double SquareMagnitude() const override;

  Standard_EXPORT double Crossed(const occ::handle<Geom2d_Vector>& Other) const override;

  double operator^(const occ::handle<Geom2d_Vector>& Other) const { return Crossed(Other); }

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Direction, Geom2d_Vector)
};

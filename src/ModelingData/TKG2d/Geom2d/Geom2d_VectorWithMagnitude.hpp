#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Vector.hpp>
class gp_Vec2d;
class gp_Pnt2d;
class gp_Trsf2d;
class Geom2d_Geometry;

class Geom2d_VectorWithMagnitude : public Geom2d_Vector
{

public:
  Standard_EXPORT Geom2d_VectorWithMagnitude(const gp_Vec2d& V);

  Standard_EXPORT Geom2d_VectorWithMagnitude(const double X, const double Y);

  Standard_EXPORT Geom2d_VectorWithMagnitude(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  Standard_EXPORT void SetCoord(const double X, const double Y);

  Standard_EXPORT void SetVec2d(const gp_Vec2d& V);

  Standard_EXPORT void SetX(const double X);

  Standard_EXPORT void SetY(const double Y);

  Standard_EXPORT double Magnitude() const override;

  Standard_EXPORT double SquareMagnitude() const override;

  Standard_EXPORT void Add(const occ::handle<Geom2d_Vector>& Other);

  void operator+=(const occ::handle<Geom2d_Vector>& Other) { Add(Other); }

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Added(
    const occ::handle<Geom2d_Vector>& Other) const;

  [[nodiscard]] occ::handle<Geom2d_VectorWithMagnitude> operator+(
    const occ::handle<Geom2d_Vector>& Other) const
  {
    return Added(Other);
  }

  Standard_EXPORT double Crossed(const occ::handle<Geom2d_Vector>& Other) const override;

  double operator^(const occ::handle<Geom2d_Vector>& Other) const { return Crossed(Other); }

  Standard_EXPORT void Divide(const double Scalar);

  void operator/=(const double Scalar) { Divide(Scalar); }

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Divided(
    const double Scalar) const;

  [[nodiscard]] occ::handle<Geom2d_VectorWithMagnitude> operator/(const double Scalar) const
  {
    return Divided(Scalar);
  }

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Multiplied(
    const double Scalar) const;

  Standard_EXPORT void Multiply(const double Scalar);

  void operator*=(const double Scalar) { Multiply(Scalar); }

  Standard_EXPORT void Normalize();

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Normalized() const;

  Standard_EXPORT void Subtract(const occ::handle<Geom2d_Vector>& Other);

  void operator-=(const occ::handle<Geom2d_Vector>& Other) { Subtract(Other); }

  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Subtracted(
    const occ::handle<Geom2d_Vector>& Other) const;

  [[nodiscard]] occ::handle<Geom2d_VectorWithMagnitude> operator-(
    const occ::handle<Geom2d_Vector>& Other) const
  {
    return Subtracted(Other);
  }

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_VectorWithMagnitude, Geom2d_Vector)
};

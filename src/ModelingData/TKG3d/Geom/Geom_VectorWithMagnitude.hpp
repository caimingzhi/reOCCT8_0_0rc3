#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Vector.hpp>
class gp_Vec;
class gp_Pnt;
class gp_Trsf;
class Geom_Geometry;

class Geom_VectorWithMagnitude : public Geom_Vector
{

public:
  Standard_EXPORT Geom_VectorWithMagnitude(const gp_Vec& V);

  Standard_EXPORT Geom_VectorWithMagnitude(const double X, const double Y, const double Z);

  Standard_EXPORT Geom_VectorWithMagnitude(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT void SetCoord(const double X, const double Y, const double Z);

  Standard_EXPORT void SetVec(const gp_Vec& V);

  Standard_EXPORT void SetX(const double X);

  Standard_EXPORT void SetY(const double Y);

  Standard_EXPORT void SetZ(const double Z);

  Standard_EXPORT double Magnitude() const override;

  Standard_EXPORT double SquareMagnitude() const override;

  Standard_EXPORT void Add(const occ::handle<Geom_Vector>& Other);

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_VectorWithMagnitude> Added(
    const occ::handle<Geom_Vector>& Other) const;

  Standard_EXPORT void Cross(const occ::handle<Geom_Vector>& Other) override;

  Standard_EXPORT occ::handle<Geom_Vector> Crossed(
    const occ::handle<Geom_Vector>& Other) const override;

  Standard_EXPORT void CrossCross(const occ::handle<Geom_Vector>& V1,
                                  const occ::handle<Geom_Vector>& V2) override;

  Standard_EXPORT occ::handle<Geom_Vector> CrossCrossed(
    const occ::handle<Geom_Vector>& V1,
    const occ::handle<Geom_Vector>& V2) const override;

  Standard_EXPORT void Divide(const double Scalar);

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_VectorWithMagnitude> Divided(
    const double Scalar) const;

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_VectorWithMagnitude> Multiplied(
    const double Scalar) const;

  Standard_EXPORT void Multiply(const double Scalar);

  Standard_EXPORT void Normalize();

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_VectorWithMagnitude> Normalized() const;

  Standard_EXPORT void Subtract(const occ::handle<Geom_Vector>& Other);

  [[nodiscard]] Standard_EXPORT occ::handle<Geom_VectorWithMagnitude> Subtracted(
    const occ::handle<Geom_Vector>& Other) const;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom_VectorWithMagnitude, Geom_Vector)
};

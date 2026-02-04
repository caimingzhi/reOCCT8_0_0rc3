#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Vector.hpp>
class gp_Vec2d;
class gp_Pnt2d;
class gp_Trsf2d;
class Geom2d_Geometry;

//! Defines a vector with magnitude.
//! A vector with magnitude can have a zero length.
class Geom2d_VectorWithMagnitude : public Geom2d_Vector
{

public:
  //! Creates a persistent copy of V.
  Standard_EXPORT Geom2d_VectorWithMagnitude(const gp_Vec2d& V);

  //! Creates a vector with two cartesian coordinates.
  Standard_EXPORT Geom2d_VectorWithMagnitude(const double X, const double Y);

  //! Creates a vector from the point P1 to the point P2.
  //! The magnitude of the vector is the distance between P1 and P2
  Standard_EXPORT Geom2d_VectorWithMagnitude(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  //! Set <me> to X, Y coordinates.
  Standard_EXPORT void SetCoord(const double X, const double Y);

  Standard_EXPORT void SetVec2d(const gp_Vec2d& V);

  //! Changes the X coordinate of <me>.
  Standard_EXPORT void SetX(const double X);

  //! Changes the Y coordinate of <me>
  Standard_EXPORT void SetY(const double Y);

  //! Returns the magnitude of <me>.
  Standard_EXPORT double Magnitude() const override;

  //! Returns the square magnitude of <me>.
  Standard_EXPORT double SquareMagnitude() const override;

  //! Adds the Vector Other to <me>.
  Standard_EXPORT void Add(const occ::handle<Geom2d_Vector>& Other);

  void operator+=(const occ::handle<Geom2d_Vector>& Other) { Add(Other); }

  //! Adds the vector Other to <me>.
  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Added(
    const occ::handle<Geom2d_Vector>& Other) const;

  [[nodiscard]] occ::handle<Geom2d_VectorWithMagnitude> operator+(
    const occ::handle<Geom2d_Vector>& Other) const
  {
    return Added(Other);
  }

  //! Computes the cross product between <me> and Other
  //! <me> ^ Other. A new vector is returned.
  Standard_EXPORT double Crossed(const occ::handle<Geom2d_Vector>& Other) const override;

  double operator^(const occ::handle<Geom2d_Vector>& Other) const { return Crossed(Other); }

  //! Divides <me> by a scalar.
  Standard_EXPORT void Divide(const double Scalar);

  void operator/=(const double Scalar) { Divide(Scalar); }

  //! Divides <me> by a scalar. A new vector is returned.
  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Divided(
    const double Scalar) const;

  [[nodiscard]] occ::handle<Geom2d_VectorWithMagnitude> operator/(const double Scalar) const
  {
    return Divided(Scalar);
  }

  //! Computes the product of the vector <me> by a scalar.
  //! A new vector is returned.
  //!
  //! -C++: alias operator *
  //! Collision with same operator defined for the class Vector!
  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Multiplied(
    const double Scalar) const;

  //! Computes the product of the vector <me> by a scalar.
  Standard_EXPORT void Multiply(const double Scalar);

  void operator*=(const double Scalar) { Multiply(Scalar); }

  //! Normalizes <me>.
  //!
  //! Raised if the magnitude of the vector is lower or equal to
  //! Resolution from package gp.
  Standard_EXPORT void Normalize();

  //! Returns a copy of <me> Normalized.
  //!
  //! Raised if the magnitude of the vector is lower or equal to
  //! Resolution from package gp.
  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Normalized() const;

  //! Subtracts the Vector Other to <me>.
  Standard_EXPORT void Subtract(const occ::handle<Geom2d_Vector>& Other);

  void operator-=(const occ::handle<Geom2d_Vector>& Other) { Subtract(Other); }

  //! Subtracts the vector Other to <me>. A new vector is returned.
  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_VectorWithMagnitude> Subtracted(
    const occ::handle<Geom2d_Vector>& Other) const;

  [[nodiscard]] occ::handle<Geom2d_VectorWithMagnitude> operator-(
    const occ::handle<Geom2d_Vector>& Other) const
  {
    return Subtracted(Other);
  }

  //! Applies the transformation T to this vector.
  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  //! Creates a new object which is a copy of this vector.
  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_VectorWithMagnitude, Geom2d_Vector)
};


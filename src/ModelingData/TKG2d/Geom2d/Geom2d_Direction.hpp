#pragma once


#include <Standard.hpp>

#include <Geom2d_Vector.hpp>
#include <Standard_Real.hpp>
class gp_Dir2d;
class gp_Trsf2d;
class Geom2d_Geometry;

//! The class Direction specifies a vector that is never null.
//! It is a unit vector.
class Geom2d_Direction : public Geom2d_Vector
{

public:
  //! Creates a unit vector with it 2 cartesian coordinates.
  //!
  //! Raised if std::sqrt( X*X + Y*Y) <= Resolution from gp.
  Standard_EXPORT Geom2d_Direction(const double X, const double Y);

  //! Creates a persistent copy of <me>.
  Standard_EXPORT Geom2d_Direction(const gp_Dir2d& V);

  //! Assigns the coordinates X and Y to this unit vector,
  //! then normalizes it.
  //! Exceptions
  //! Standard_ConstructionError if std::sqrt(X*X + Y*Y) is less than or equal to gp::Resolution().
  Standard_EXPORT void SetCoord(const double X, const double Y);

  //! Converts the gp_Dir2d unit vector V into this unit vector.
  Standard_EXPORT void SetDir2d(const gp_Dir2d& V);

  //! Assigns a value to the X coordinate of this unit vector, then normalizes it.
  //! Exceptions
  //! Standard_ConstructionError if the value assigned
  //! causes the magnitude of the vector to become less
  //! than or equal to gp::Resolution().
  Standard_EXPORT void SetX(const double X);

  //! Assigns a value to the Y coordinate of this unit vector, then normalizes it.
  //! Exceptions
  //! Standard_ConstructionError if the value assigned
  //! causes the magnitude of the vector to become less
  //! than or equal to gp::Resolution().
  Standard_EXPORT void SetY(const double Y);

  //! Converts this unit vector into a gp_Dir2d unit vector.
  Standard_EXPORT gp_Dir2d Dir2d() const;

  //! returns 1.0
  Standard_EXPORT double Magnitude() const override;

  //! returns 1.0
  Standard_EXPORT double SquareMagnitude() const override;

  //! Computes the cross product between <me> and <Other>.
  Standard_EXPORT double Crossed(const occ::handle<Geom2d_Vector>& Other) const override;

  double operator^(const occ::handle<Geom2d_Vector>& Other) const { return Crossed(Other); }

  //! Applies the transformation T to this unit vector, then normalizes it.
  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  //! Creates a new object which is a copy of this unit vector.
  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Direction, Geom2d_Vector)
};


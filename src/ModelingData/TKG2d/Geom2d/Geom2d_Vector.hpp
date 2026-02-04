#pragma once


#include <Standard.hpp>

#include <gp_Vec2d.hpp>
#include <Geom2d_Geometry.hpp>
#include <Standard_Real.hpp>

//! The abstract class Vector describes the common
//! behavior of vectors in 2D space.
//! The Geom2d package provides two concrete
//! classes of vectors: Geom2d_Direction (unit vector)
//! and Geom2d_VectorWithMagnitude.
class Geom2d_Vector : public Geom2d_Geometry
{

public:
  //! Reverses the vector <me>.
  Standard_EXPORT void Reverse();

  //! Returns a copy of <me> reversed.
  [[nodiscard]] Standard_EXPORT occ::handle<Geom2d_Vector> Reversed() const;

  //! Computes the angular value, in radians, between this
  //! vector and vector Other. The result is a value
  //! between -Pi and Pi. The orientation is from this
  //! vector to vector Other.
  //! Raises VectorWithNullMagnitude if one of the two vectors is a vector with
  //! null magnitude because the angular value is indefinite.
  Standard_EXPORT double Angle(const occ::handle<Geom2d_Vector>& Other) const;

  //! Returns the coordinates of <me>.
  Standard_EXPORT void Coord(double& X, double& Y) const;

  //! Returns the Magnitude of <me>.
  Standard_EXPORT virtual double Magnitude() const = 0;

  //! Returns the square magnitude of <me>.
  Standard_EXPORT virtual double SquareMagnitude() const = 0;

  //! Returns the X coordinate of <me>.
  Standard_EXPORT double X() const;

  //! Returns the Y coordinate of <me>.
  Standard_EXPORT double Y() const;

  //! Cross product of <me> with the vector <Other>.
  Standard_EXPORT virtual double Crossed(const occ::handle<Geom2d_Vector>& Other) const = 0;

  //! Returns the scalar product of 2 Vectors.
  Standard_EXPORT double Dot(const occ::handle<Geom2d_Vector>& Other) const;

  //! Returns a non persistent copy of <me>.
  Standard_EXPORT gp_Vec2d Vec2d() const;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Vector, Geom2d_Geometry)

protected:
  gp_Vec2d gpVec2d;
};


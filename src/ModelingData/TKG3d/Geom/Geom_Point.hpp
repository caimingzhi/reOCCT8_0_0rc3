#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Geometry.hpp>
#include <Standard_Real.hpp>
class gp_Pnt;

//! The abstract class Point describes the common
//! behavior of geometric points in 3D space.
//! The Geom package also provides the concrete class
//! Geom_CartesianPoint.
class Geom_Point : public Geom_Geometry
{

public:
  //! returns the Coordinates of <me>.
  Standard_EXPORT virtual void Coord(double& X, double& Y, double& Z) const = 0;

  //! returns a non transient copy of <me>
  Standard_EXPORT virtual gp_Pnt Pnt() const = 0;

  //! returns the X coordinate of <me>.
  Standard_EXPORT virtual double X() const = 0;

  //! returns the Y coordinate of <me>.
  Standard_EXPORT virtual double Y() const = 0;

  //! returns the Z coordinate of <me>.
  Standard_EXPORT virtual double Z() const = 0;

  //! Computes the distance between <me> and <Other>.
  Standard_EXPORT double Distance(const occ::handle<Geom_Point>& Other) const;

  //! Computes the square distance between <me> and <Other>.
  Standard_EXPORT double SquareDistance(const occ::handle<Geom_Point>& Other) const;

  DEFINE_STANDARD_RTTIEXT(Geom_Point, Geom_Geometry)
};

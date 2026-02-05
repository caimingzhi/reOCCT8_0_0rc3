#pragma once

#include <Standard.hpp>

#include <gp_Pnt.hpp>
#include <Geom_Point.hpp>
#include <Standard_Real.hpp>
class gp_Trsf;
class Geom_Geometry;

//! Describes a point in 3D space. A
//! Geom_CartesianPoint is defined by a gp_Pnt point,
//! with its three Cartesian coordinates X, Y and Z.
class Geom_CartesianPoint : public Geom_Point
{

public:
  //! Returns a transient copy of P.
  Standard_EXPORT Geom_CartesianPoint(const gp_Pnt& P);

  //! Constructs a point defined by its three Cartesian coordinates X, Y and Z.
  Standard_EXPORT Geom_CartesianPoint(const double X, const double Y, const double Z);

  //! Assigns the coordinates X, Y and Z to this point.
  Standard_EXPORT void SetCoord(const double X, const double Y, const double Z);

  //! Set <me> to P.X(), P.Y(), P.Z() coordinates.
  Standard_EXPORT void SetPnt(const gp_Pnt& P);

  //! Changes the X coordinate of <me>.
  Standard_EXPORT void SetX(const double X);

  //! Changes the Y coordinate of <me>.
  Standard_EXPORT void SetY(const double Y);

  //! Changes the Z coordinate of <me>.
  Standard_EXPORT void SetZ(const double Z);

  //! Returns the coordinates of <me>.
  Standard_EXPORT void Coord(double& X, double& Y, double& Z) const override;

  //! Returns a non transient cartesian point with
  //! the same coordinates as <me>.
  Standard_EXPORT gp_Pnt Pnt() const override;

  //! Returns the X coordinate of <me>.
  Standard_EXPORT double X() const override;

  //! Returns the Y coordinate of <me>.
  Standard_EXPORT double Y() const override;

  //! Returns the Z coordinate of <me>.
  Standard_EXPORT double Z() const override;

  //! Applies the transformation T to this point.
  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  //! Creates a new object which is a copy of this point.
  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  DEFINE_STANDARD_RTTIEXT(Geom_CartesianPoint, Geom_Point)

private:
  gp_Pnt gpPnt;
};

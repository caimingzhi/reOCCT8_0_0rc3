#pragma once


#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <Geom2d_Point.hpp>
#include <Standard_Real.hpp>
class gp_Trsf2d;
class Geom2d_Geometry;

//! Describes a point in 2D space. A
//! Geom2d_CartesianPoint is defined by a gp_Pnt2d
//! point, with its two Cartesian coordinates X and Y.
class Geom2d_CartesianPoint : public Geom2d_Point
{

public:
  //! Returns a persistent copy of P.
  Standard_EXPORT Geom2d_CartesianPoint(const gp_Pnt2d& P);

  Standard_EXPORT Geom2d_CartesianPoint(const double X, const double Y);

  //! Set <me> to X, Y coordinates.
  Standard_EXPORT void SetCoord(const double X, const double Y);

  //! Set <me> to P.X(), P.Y() coordinates.
  Standard_EXPORT void SetPnt2d(const gp_Pnt2d& P);

  //! Changes the X coordinate of me.
  Standard_EXPORT void SetX(const double X);

  //! Changes the Y coordinate of me.
  Standard_EXPORT void SetY(const double Y);

  //! Returns the coordinates of <me>.
  Standard_EXPORT void Coord(double& X, double& Y) const override;

  //! Returns a non persistent cartesian point with
  //! the same coordinates as <me>.
  //! -C++: return const&
  Standard_EXPORT gp_Pnt2d Pnt2d() const override;

  //! Returns the X coordinate of <me>.
  Standard_EXPORT double X() const override;

  //! Returns the Y coordinate of <me>.
  Standard_EXPORT double Y() const override;

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_CartesianPoint, Geom2d_Point)

private:
  gp_Pnt2d gpPnt2d;
};


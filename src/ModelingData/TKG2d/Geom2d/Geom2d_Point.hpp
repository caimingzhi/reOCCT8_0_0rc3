#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Geometry.hpp>
#include <Standard_Real.hpp>
class gp_Pnt2d;

//! The abstract class Point describes the common
//! behavior of geometric points in 2D space.
//! The Geom2d package also provides the concrete
//! class Geom2d_CartesianPoint.
class Geom2d_Point : public Geom2d_Geometry
{

public:
  //! returns the Coordinates of <me>.
  Standard_EXPORT virtual void Coord(double& X, double& Y) const = 0;

  //! returns a non persistent copy of <me>
  Standard_EXPORT virtual gp_Pnt2d Pnt2d() const = 0;

  //! returns the X coordinate of <me>.
  Standard_EXPORT virtual double X() const = 0;

  //! returns the Y coordinate of <me>.
  Standard_EXPORT virtual double Y() const = 0;

  //! computes the distance between <me> and <Other>.
  Standard_EXPORT double Distance(const occ::handle<Geom2d_Point>& Other) const;

  //! computes the square distance between <me> and <Other>.
  Standard_EXPORT double SquareDistance(const occ::handle<Geom2d_Point>& Other) const;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_Point, Geom2d_Geometry)
};


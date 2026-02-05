#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GC_Root.hpp>
#include <Geom_Plane.hpp>

class gp_Pln;
class gp_Pnt;
class gp_Dir;
class gp_Ax1;

//! This class implements the following algorithms used
//! to create a Plane from gp.
//! * Create a Plane parallel to another and passing
//! through a point.
//! * Create a Plane passing through 3 points.
//! * Create a Plane by its normal
//! A MakePlane object provides a framework for:
//! -   defining the construction of the plane,
//! -   implementing the construction algorithm, and
//! -   consulting the results. In particular, the Value
//! function returns the constructed plane.
class GC_MakePlane : public GC_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a plane from a non persistent plane from package gp.
  Standard_EXPORT GC_MakePlane(const gp_Pln& Pl);

  //! P is the "Location" point or origin of the plane.
  //! V is the direction normal to the plane.
  Standard_EXPORT GC_MakePlane(const gp_Pnt& P, const gp_Dir& V);

  //! Creates a plane from its cartesian equation :
  //! Ax + By + Cz + D = 0.0
  //! Status is "BadEquation" if std::sqrt(A*A + B*B + C*C)
  //! <= Resolution from gp
  Standard_EXPORT GC_MakePlane(const double A, const double B, const double C, const double D);

  //! Make a Plane from Geom <ThePlane> parallel to another
  //! Pln <Pln> and passing through a Pnt <Point>.
  Standard_EXPORT GC_MakePlane(const gp_Pln& Pln, const gp_Pnt& Point);

  //! Make a Plane from Geom <ThePlane> parallel to another
  //! Pln <Pln> at the distance <Dist> which can be greater
  //! or lower than zero.
  //! In the first case the result is at the distance
  //! <Dist> to the plane <Pln> in the direction of the
  //! normal to <Pln>.
  //! Otherwise it is in the opposite direction.
  Standard_EXPORT GC_MakePlane(const gp_Pln& Pln, const double Dist);

  //! Make a Plane from Geom <ThePlane> passing through 3
  //! Pnt <P1>,<P2>,<P3>.
  //! It returns false if <P1> <P2> <P3> are confused.
  Standard_EXPORT GC_MakePlane(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3);

  //! Make a Plane passing through the location of <Axis>and
  //! normal to the Direction of <Axis>.
  Standard_EXPORT GC_MakePlane(const gp_Ax1& Axis);

  //! Returns the constructed plane.
  //! Exceptions StdFail_NotDone if no plane is constructed.
  Standard_EXPORT const occ::handle<Geom_Plane>& Value() const;

  operator const occ::handle<Geom_Plane>&() const { return Value(); }

private:
  occ::handle<Geom_Plane> ThePlane;
};

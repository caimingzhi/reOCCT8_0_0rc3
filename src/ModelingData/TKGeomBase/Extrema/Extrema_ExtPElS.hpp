#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_POnSurf.hpp>
class gp_Pnt;
class gp_Cylinder;
class gp_Pln;
class gp_Cone;
class gp_Torus;
class gp_Sphere;

//! It calculates all the extremum distances
//! between a point and a surface.
//! These distances can be minimum or maximum.
class Extrema_ExtPElS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtPElS();

  //! It calculates all the distances between a point
  //! and a cylinder from gp.
  //! Tol is used to test if the point is on the axis.
  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Cylinder& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Cylinder& S, const double Tol);

  //! It calculates all the distances between a point
  //! and a plane from gp.
  //! Tol is used to test if the point is on the plane.
  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Pln& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Pln& S, const double Tol);

  //! It calculates all the distances between a point
  //! and a cone from gp.
  //! Tol is used to test if the point is at the apex or
  //! on the axis.
  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Cone& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Cone& S, const double Tol);

  //! It calculates all the distances between a point
  //! and a torus from gp.
  //! Tol is used to test if the point is on the axis.
  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Torus& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Torus& S, const double Tol);

  //! It calculates all the distances between a point
  //! and a sphere from gp.
  //! Tol is used to test if the point is at the center.
  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Sphere& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Sphere& S, const double Tol);

  //! Returns True if the distances are found.
  Standard_EXPORT bool IsDone() const;

  //! Returns the number of extremum distances.
  Standard_EXPORT int NbExt() const;

  //! Returns the value of the Nth resulting square distance.
  Standard_EXPORT double SquareDistance(const int N) const;

  //! Returns the point of the Nth resulting distance.
  Standard_EXPORT const Extrema_POnSurf& Point(const int N) const;

private:
  bool            myDone;
  int             myNbExt;
  double          mySqDist[4];
  Extrema_POnSurf myPoint[4];
};


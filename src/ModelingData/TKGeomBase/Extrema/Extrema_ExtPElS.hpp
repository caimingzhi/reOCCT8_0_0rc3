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

class Extrema_ExtPElS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtPElS();

  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Cylinder& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Cylinder& S, const double Tol);

  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Pln& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Pln& S, const double Tol);

  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Cone& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Cone& S, const double Tol);

  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Torus& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Torus& S, const double Tol);

  Standard_EXPORT Extrema_ExtPElS(const gp_Pnt& P, const gp_Sphere& S, const double Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const gp_Sphere& S, const double Tol);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& Point(const int N) const;

private:
  bool            myDone;
  int             myNbExt;
  double          mySqDist[4];
  Extrema_POnSurf myPoint[4];
};

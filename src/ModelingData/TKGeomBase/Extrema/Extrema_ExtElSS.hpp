#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Extrema_POnSurf.hpp>
#include <Standard_Real.hpp>

class gp_Pln;
class gp_Sphere;
class gp_Cylinder;
class gp_Cone;
class gp_Torus;
class Extrema_POnSurf;

//! It calculates all the distances between 2 elementary
//! surfaces.
//! These distances can be maximum or minimum.
class Extrema_ExtElSS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtElSS();

  //! Calculates the distances between 2 planes.
  //! These planes can be parallel.
  Standard_EXPORT Extrema_ExtElSS(const gp_Pln& S1, const gp_Pln& S2);

  Standard_EXPORT void Perform(const gp_Pln& S1, const gp_Pln& S2);

  //! Calculates the distances between a plane
  //! and a sphere.
  Standard_EXPORT Extrema_ExtElSS(const gp_Pln& S1, const gp_Sphere& S2);

  Standard_EXPORT void Perform(const gp_Pln& S1, const gp_Sphere& S2);

  //! Calculates the distances between 2 spheres.
  //! These spheres can be parallel.
  Standard_EXPORT Extrema_ExtElSS(const gp_Sphere& S1, const gp_Sphere& S2);

  Standard_EXPORT void Perform(const gp_Sphere& S1, const gp_Sphere& S2);

  //! Calculates the distances between a sphere
  //! and a cylinder.
  Standard_EXPORT Extrema_ExtElSS(const gp_Sphere& S1, const gp_Cylinder& S2);

  Standard_EXPORT void Perform(const gp_Sphere& S1, const gp_Cylinder& S2);

  //! Calculates the distances between a sphere
  //! and a cone.
  Standard_EXPORT Extrema_ExtElSS(const gp_Sphere& S1, const gp_Cone& S2);

  Standard_EXPORT void Perform(const gp_Sphere& S1, const gp_Cone& S2);

  //! Calculates the distances between a sphere
  //! and a torus.
  Standard_EXPORT Extrema_ExtElSS(const gp_Sphere& S1, const gp_Torus& S2);

  Standard_EXPORT void Perform(const gp_Sphere& S1, const gp_Torus& S2);

  //! Returns True if the distances are found.
  Standard_EXPORT bool IsDone() const;

  //! Returns True if the two surfaces are parallel.
  Standard_EXPORT bool IsParallel() const;

  //! Returns the number of extremum distances.
  Standard_EXPORT int NbExt() const;

  //! Returns the value of the Nth extremum square distance.
  Standard_EXPORT double SquareDistance(const int N = 1) const;

  //! Returns the points for the Nth resulting distance.
  //! P1 is on the first surface, P2 on the second one.
  Standard_EXPORT void Points(const int N, Extrema_POnSurf& P1, Extrema_POnSurf& P2) const;

private:
  bool                                              myDone;
  bool                                              myIsPar;
  int                                               myNbExt;
  occ::handle<NCollection_HArray1<double>>          mySqDist;
  occ::handle<NCollection_HArray1<Extrema_POnSurf>> myPOnS1;
  occ::handle<NCollection_HArray1<Extrema_POnSurf>> myPOnS2;
};


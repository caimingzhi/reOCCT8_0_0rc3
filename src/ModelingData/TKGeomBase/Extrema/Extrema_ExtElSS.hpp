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

class Extrema_ExtElSS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtElSS();

  Standard_EXPORT Extrema_ExtElSS(const gp_Pln& S1, const gp_Pln& S2);

  Standard_EXPORT void Perform(const gp_Pln& S1, const gp_Pln& S2);

  Standard_EXPORT Extrema_ExtElSS(const gp_Pln& S1, const gp_Sphere& S2);

  Standard_EXPORT void Perform(const gp_Pln& S1, const gp_Sphere& S2);

  Standard_EXPORT Extrema_ExtElSS(const gp_Sphere& S1, const gp_Sphere& S2);

  Standard_EXPORT void Perform(const gp_Sphere& S1, const gp_Sphere& S2);

  Standard_EXPORT Extrema_ExtElSS(const gp_Sphere& S1, const gp_Cylinder& S2);

  Standard_EXPORT void Perform(const gp_Sphere& S1, const gp_Cylinder& S2);

  Standard_EXPORT Extrema_ExtElSS(const gp_Sphere& S1, const gp_Cone& S2);

  Standard_EXPORT void Perform(const gp_Sphere& S1, const gp_Cone& S2);

  Standard_EXPORT Extrema_ExtElSS(const gp_Sphere& S1, const gp_Torus& S2);

  Standard_EXPORT void Perform(const gp_Sphere& S1, const gp_Torus& S2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool IsParallel() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N = 1) const;

  Standard_EXPORT void Points(const int N, Extrema_POnSurf& P1, Extrema_POnSurf& P2) const;

private:
  bool                                              myDone;
  bool                                              myIsPar;
  int                                               myNbExt;
  occ::handle<NCollection_HArray1<double>>          mySqDist;
  occ::handle<NCollection_HArray1<Extrema_POnSurf>> myPOnS1;
  occ::handle<NCollection_HArray1<Extrema_POnSurf>> myPOnS2;
};

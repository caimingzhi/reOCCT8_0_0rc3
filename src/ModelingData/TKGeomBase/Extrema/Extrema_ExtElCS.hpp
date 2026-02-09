#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Extrema_POnCurv.hpp>
#include <Extrema_POnSurf.hpp>

class gp_Lin;
class gp_Pln;
class gp_Cylinder;
class gp_Cone;
class gp_Sphere;
class gp_Torus;
class gp_Circ;
class gp_Hypr;
class Extrema_POnCurv;
class Extrema_POnSurf;

class Extrema_ExtElCS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtElCS();

  Standard_EXPORT Extrema_ExtElCS(const gp_Lin& C, const gp_Pln& S);

  Standard_EXPORT void Perform(const gp_Lin& C, const gp_Pln& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Lin& C, const gp_Cylinder& S);

  Standard_EXPORT void Perform(const gp_Lin& C, const gp_Cylinder& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Lin& C, const gp_Cone& S);

  Standard_EXPORT void Perform(const gp_Lin& C, const gp_Cone& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Lin& C, const gp_Sphere& S);

  Standard_EXPORT void Perform(const gp_Lin& C, const gp_Sphere& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Lin& C, const gp_Torus& S);

  Standard_EXPORT void Perform(const gp_Lin& C, const gp_Torus& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Circ& C, const gp_Pln& S);

  Standard_EXPORT void Perform(const gp_Circ& C, const gp_Pln& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Circ& C, const gp_Cylinder& S);

  Standard_EXPORT void Perform(const gp_Circ& C, const gp_Cylinder& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Circ& C, const gp_Cone& S);

  Standard_EXPORT void Perform(const gp_Circ& C, const gp_Cone& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Circ& C, const gp_Sphere& S);

  Standard_EXPORT void Perform(const gp_Circ& C, const gp_Sphere& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Circ& C, const gp_Torus& S);

  Standard_EXPORT void Perform(const gp_Circ& C, const gp_Torus& S);

  Standard_EXPORT Extrema_ExtElCS(const gp_Hypr& C, const gp_Pln& S);

  Standard_EXPORT void Perform(const gp_Hypr& C, const gp_Pln& S);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool IsParallel() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N = 1) const;

  Standard_EXPORT void Points(const int N, Extrema_POnCurv& P1, Extrema_POnSurf& P2) const;

private:
  bool                                              myDone;
  int                                               myNbExt;
  bool                                              myIsPar;
  occ::handle<NCollection_HArray1<double>>          mySqDist;
  occ::handle<NCollection_HArray1<Extrema_POnCurv>> myPoint1;
  occ::handle<NCollection_HArray1<Extrema_POnSurf>> myPoint2;
};

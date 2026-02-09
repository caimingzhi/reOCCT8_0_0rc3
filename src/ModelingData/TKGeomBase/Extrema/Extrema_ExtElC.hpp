#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_POnCurv.hpp>

class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Hypr;
class gp_Parab;

class Extrema_ExtElC
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtElC();

  Standard_EXPORT Extrema_ExtElC(const gp_Lin& C1, const gp_Lin& C2, const double AngTol);

  Standard_EXPORT Extrema_ExtElC(const gp_Lin& C1, const gp_Circ& C2, const double Tol);

  Standard_EXPORT Extrema_ExtElC(const gp_Lin& C1, const gp_Elips& C2);

  Standard_EXPORT Extrema_ExtElC(const gp_Lin& C1, const gp_Hypr& C2);

  Standard_EXPORT Extrema_ExtElC(const gp_Lin& C1, const gp_Parab& C2);

  Standard_EXPORT Extrema_ExtElC(const gp_Circ& C1, const gp_Circ& C2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool IsParallel() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N = 1) const;

  Standard_EXPORT void Points(const int N, Extrema_POnCurv& P1, Extrema_POnCurv& P2) const;

protected:
  Standard_EXPORT bool PlanarLineCircleExtrema(const gp_Lin& C1, const gp_Circ& C2);

private:
  bool            myDone;
  bool            myIsPar;
  int             myNbExt;
  double          mySqDist[6];
  Extrema_POnCurv myPoint[6][2];
};

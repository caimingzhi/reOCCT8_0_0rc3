#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_POnCurv2d.hpp>

class gp_Lin2d;
class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;

class Extrema_ExtElC2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtElC2d();

  Standard_EXPORT Extrema_ExtElC2d(const gp_Lin2d& C1, const gp_Lin2d& C2, const double AngTol);

  Standard_EXPORT Extrema_ExtElC2d(const gp_Lin2d& C1, const gp_Circ2d& C2, const double Tol);

  Standard_EXPORT Extrema_ExtElC2d(const gp_Lin2d& C1, const gp_Elips2d& C2);

  Standard_EXPORT Extrema_ExtElC2d(const gp_Lin2d& C1, const gp_Hypr2d& C2);

  Standard_EXPORT Extrema_ExtElC2d(const gp_Lin2d& C1, const gp_Parab2d& C2);

  Standard_EXPORT Extrema_ExtElC2d(const gp_Circ2d& C1, const gp_Circ2d& C2);

  Standard_EXPORT Extrema_ExtElC2d(const gp_Circ2d& C1, const gp_Elips2d& C2);

  Standard_EXPORT Extrema_ExtElC2d(const gp_Circ2d& C1, const gp_Hypr2d& C2);

  Standard_EXPORT Extrema_ExtElC2d(const gp_Circ2d& C1, const gp_Parab2d& C2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool IsParallel() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N = 1) const;

  Standard_EXPORT void Points(const int N, Extrema_POnCurv2d& P1, Extrema_POnCurv2d& P2) const;

private:
  bool              myDone;
  bool              myIsPar;
  int               myNbExt;
  double            mySqDist[8];
  Extrema_POnCurv2d myPoint[8][2];
};

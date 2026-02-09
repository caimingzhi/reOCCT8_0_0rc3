#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_POnCurv.hpp>
class gp_Pnt;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Hypr;
class gp_Parab;

class Extrema_ExtPElC
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtPElC();

  Standard_EXPORT Extrema_ExtPElC(const gp_Pnt& P,
                                  const gp_Lin& C,
                                  const double  Tol,
                                  const double  Uinf,
                                  const double  Usup);

  Standard_EXPORT void Perform(const gp_Pnt& P,
                               const gp_Lin& C,
                               const double  Tol,
                               const double  Uinf,
                               const double  Usup);

  Standard_EXPORT Extrema_ExtPElC(const gp_Pnt&  P,
                                  const gp_Circ& C,
                                  const double   Tol,
                                  const double   Uinf,
                                  const double   Usup);

  Standard_EXPORT void Perform(const gp_Pnt&  P,
                               const gp_Circ& C,
                               const double   Tol,
                               const double   Uinf,
                               const double   Usup);

  Standard_EXPORT Extrema_ExtPElC(const gp_Pnt&   P,
                                  const gp_Elips& C,
                                  const double    Tol,
                                  const double    Uinf,
                                  const double    Usup);

  Standard_EXPORT void Perform(const gp_Pnt&   P,
                               const gp_Elips& C,
                               const double    Tol,
                               const double    Uinf,
                               const double    Usup);

  Standard_EXPORT Extrema_ExtPElC(const gp_Pnt&  P,
                                  const gp_Hypr& C,
                                  const double   Tol,
                                  const double   Uinf,
                                  const double   Usup);

  Standard_EXPORT void Perform(const gp_Pnt&  P,
                               const gp_Hypr& C,
                               const double   Tol,
                               const double   Uinf,
                               const double   Usup);

  Standard_EXPORT Extrema_ExtPElC(const gp_Pnt&   P,
                                  const gp_Parab& C,
                                  const double    Tol,
                                  const double    Uinf,
                                  const double    Usup);

  Standard_EXPORT void Perform(const gp_Pnt&   P,
                               const gp_Parab& C,
                               const double    Tol,
                               const double    Uinf,
                               const double    Usup);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT bool IsMin(const int N) const;

  Standard_EXPORT const Extrema_POnCurv& Point(const int N) const;

private:
  bool            myDone;
  int             myNbExt;
  double          mySqDist[4];
  bool            myIsMin[4];
  Extrema_POnCurv myPoint[4];
};

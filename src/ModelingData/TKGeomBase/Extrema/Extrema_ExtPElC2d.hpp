#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_POnCurv2d.hpp>
class gp_Pnt2d;
class gp_Lin2d;
class gp_Circ2d;
class gp_Elips2d;
class gp_Hypr2d;
class gp_Parab2d;

class Extrema_ExtPElC2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtPElC2d();

  Standard_EXPORT Extrema_ExtPElC2d(const gp_Pnt2d& P,
                                    const gp_Lin2d& C,
                                    const double    Tol,
                                    const double    Uinf,
                                    const double    Usup);

  Standard_EXPORT void Perform(const gp_Pnt2d& P,
                               const gp_Lin2d& L,
                               const double    Tol,
                               const double    Uinf,
                               const double    Usup);

  Standard_EXPORT Extrema_ExtPElC2d(const gp_Pnt2d&  P,
                                    const gp_Circ2d& C,
                                    const double     Tol,
                                    const double     Uinf,
                                    const double     Usup);

  Standard_EXPORT void Perform(const gp_Pnt2d&  P,
                               const gp_Circ2d& C,
                               const double     Tol,
                               const double     Uinf,
                               const double     Usup);

  Standard_EXPORT Extrema_ExtPElC2d(const gp_Pnt2d&   P,
                                    const gp_Elips2d& C,
                                    const double      Tol,
                                    const double      Uinf,
                                    const double      Usup);

  Standard_EXPORT void Perform(const gp_Pnt2d&   P,
                               const gp_Elips2d& C,
                               const double      Tol,
                               const double      Uinf,
                               const double      Usup);

  Standard_EXPORT Extrema_ExtPElC2d(const gp_Pnt2d&  P,
                                    const gp_Hypr2d& C,
                                    const double     Tol,
                                    const double     Uinf,
                                    const double     Usup);

  Standard_EXPORT void Perform(const gp_Pnt2d&  P,
                               const gp_Hypr2d& C,
                               const double     Tol,
                               const double     Uinf,
                               const double     Usup);

  Standard_EXPORT Extrema_ExtPElC2d(const gp_Pnt2d&   P,
                                    const gp_Parab2d& C,
                                    const double      Tol,
                                    const double      Uinf,
                                    const double      Usup);

  Standard_EXPORT void Perform(const gp_Pnt2d&   P,
                               const gp_Parab2d& C,
                               const double      Tol,
                               const double      Uinf,
                               const double      Usup);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT bool IsMin(const int N) const;

  Standard_EXPORT const Extrema_POnCurv2d& Point(const int N) const;

private:
  bool              myDone;
  int               myNbExt;
  double            mySqDist[4];
  bool              myIsMin[4];
  Extrema_POnCurv2d myPoint[4];
};

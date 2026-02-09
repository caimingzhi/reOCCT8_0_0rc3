#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Lin2d.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
class gp_Lin2d;
class gp_Pnt2d;

class GccAna_Lin2dBisec
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccAna_Lin2dBisec(const gp_Lin2d& Lin1, const gp_Lin2d& Lin2);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbSolutions() const;

  Standard_EXPORT gp_Lin2d ThisSolution(const int Index) const;

  Standard_EXPORT void Intersection1(const int Index,
                                     double&   ParSol,
                                     double&   ParArg,
                                     gp_Pnt2d& PntSol) const;

  Standard_EXPORT void Intersection2(const int Index,
                                     double&   ParSol,
                                     double&   ParArg,
                                     gp_Pnt2d& PntSol) const;

private:
  bool                         WellDone;
  int                          NbrSol;
  NCollection_Array1<gp_Lin2d> linsol;
  NCollection_Array1<gp_Pnt2d> pntint1sol;
  NCollection_Array1<gp_Pnt2d> pntint2sol;
  NCollection_Array1<double>   par1sol;
  NCollection_Array1<double>   par2sol;
  NCollection_Array1<double>   pararg1;
  NCollection_Array1<double>   pararg2;
};

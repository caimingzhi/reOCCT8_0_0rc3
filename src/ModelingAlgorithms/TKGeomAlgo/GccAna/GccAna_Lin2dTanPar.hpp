#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Lin2d.hpp>
#include <NCollection_Array1.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class gp_Pnt2d;
class gp_Lin2d;
class GccEnt_QualifiedCirc;

class GccAna_Lin2dTanPar
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccAna_Lin2dTanPar(const gp_Pnt2d& ThePoint, const gp_Lin2d& Lin1);

  Standard_EXPORT GccAna_Lin2dTanPar(const GccEnt_QualifiedCirc& Qualified1, const gp_Lin2d& Lin1);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbSolutions() const;

  Standard_EXPORT gp_Lin2d ThisSolution(const int Index) const;

  Standard_EXPORT void WhichQualifier(const int Index, GccEnt_Position& Qualif1) const;

  Standard_EXPORT void Tangency1(const int Index,
                                 double&   ParSol,
                                 double&   ParArg,
                                 gp_Pnt2d& Pnt) const;

private:
  bool                                WellDone;
  int                                 NbrSol;
  NCollection_Array1<gp_Lin2d>        linsol;
  NCollection_Array1<GccEnt_Position> qualifier1;
  NCollection_Array1<gp_Pnt2d>        pnttg1sol;
  NCollection_Array1<double>          par1sol;
  NCollection_Array1<double>          pararg1;
};

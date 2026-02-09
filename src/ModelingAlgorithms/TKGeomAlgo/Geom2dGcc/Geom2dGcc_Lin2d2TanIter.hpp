#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Lin2d.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class Geom2dGcc_QCurve;
class GccEnt_QualifiedCirc;

class Geom2dGcc_Lin2d2TanIter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_Lin2d2TanIter(const Geom2dGcc_QCurve& Qualified1,
                                          const gp_Pnt2d&         ThePoint,
                                          const double            Param1,
                                          const double            Tolang);

  Standard_EXPORT Geom2dGcc_Lin2d2TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                          const Geom2dGcc_QCurve&     Qualified2,
                                          const double                Param2,
                                          const double                Tolang);

  Standard_EXPORT Geom2dGcc_Lin2d2TanIter(const Geom2dGcc_QCurve& Qualified1,
                                          const Geom2dGcc_QCurve& Qualified2,
                                          const double            Param1,
                                          const double            Param2,
                                          const double            Tolang);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT gp_Lin2d ThisSolution() const;

  Standard_EXPORT void WhichQualifier(GccEnt_Position& Qualif1, GccEnt_Position& Qualif2) const;

  Standard_EXPORT void Tangency1(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT void Tangency2(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

private:
  bool            WellDone;
  gp_Lin2d        linsol;
  GccEnt_Position qualifier1;
  GccEnt_Position qualifier2;
  gp_Pnt2d        pnttg1sol;
  gp_Pnt2d        pnttg2sol;
  double          par1sol;
  double          par2sol;
  double          pararg1;
  double          pararg2;
};

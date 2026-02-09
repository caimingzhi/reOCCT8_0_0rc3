#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
#include <NCollection_Array1.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class GccEnt_QualifiedCirc;
class gp_Lin2d;
class GccEnt_QualifiedLin;
class gp_Pnt2d;
class gp_Circ2d;

class GccAna_Circ2dTanOnRad
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccAna_Circ2dTanOnRad(const GccEnt_QualifiedCirc& Qualified1,
                                        const gp_Lin2d&             OnLine,
                                        const double                Radius,
                                        const double                Tolerance);

  Standard_EXPORT GccAna_Circ2dTanOnRad(const GccEnt_QualifiedLin& Qualified1,
                                        const gp_Lin2d&            OnLine,
                                        const double               Radius,
                                        const double               Tolerance);

  Standard_EXPORT GccAna_Circ2dTanOnRad(const gp_Pnt2d& Point1,
                                        const gp_Lin2d& OnLine,
                                        const double    Radius,
                                        const double    Tolerance);

  Standard_EXPORT GccAna_Circ2dTanOnRad(const GccEnt_QualifiedCirc& Qualified1,
                                        const gp_Circ2d&            OnCirc,
                                        const double                Radius,
                                        const double                Tolerance);

  Standard_EXPORT GccAna_Circ2dTanOnRad(const GccEnt_QualifiedLin& Qualified1,
                                        const gp_Circ2d&           OnCirc,
                                        const double               Radius,
                                        const double               Tolerance);

  Standard_EXPORT GccAna_Circ2dTanOnRad(const gp_Pnt2d&  Point1,
                                        const gp_Circ2d& OnCirc,
                                        const double     Radius,
                                        const double     Tolerance);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbSolutions() const;

  Standard_EXPORT gp_Circ2d ThisSolution(const int Index) const;

  Standard_EXPORT void WhichQualifier(const int Index, GccEnt_Position& Qualif1) const;

  Standard_EXPORT void Tangency1(const int Index,
                                 double&   ParSol,
                                 double&   ParArg,
                                 gp_Pnt2d& PntSol) const;

  Standard_EXPORT void CenterOn3(const int Index, double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT bool IsTheSame1(const int Index) const;

private:
  bool                                WellDone;
  int                                 NbrSol;
  NCollection_Array1<gp_Circ2d>       cirsol;
  NCollection_Array1<GccEnt_Position> qualifier1;
  NCollection_Array1<int>             TheSame1;
  NCollection_Array1<gp_Pnt2d>        pnttg1sol;
  NCollection_Array1<gp_Pnt2d>        pntcen3;
  NCollection_Array1<double>          par1sol;
  NCollection_Array1<double>          pararg1;
  NCollection_Array1<double>          parcen3;
};

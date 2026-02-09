#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
#include <NCollection_Array1.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class GccEnt_QualifiedCirc;
class GccEnt_QualifiedLin;
class gp_Pnt2d;
class gp_Circ2d;

class GccAna_Circ2d3Tan
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccAna_Circ2d3Tan(const GccEnt_QualifiedCirc& Qualified1,
                                    const GccEnt_QualifiedCirc& Qualified2,
                                    const GccEnt_QualifiedCirc& Qualified3,
                                    const double                Tolerance);

  Standard_EXPORT GccAna_Circ2d3Tan(const GccEnt_QualifiedCirc& Qualified1,
                                    const GccEnt_QualifiedCirc& Qualified2,
                                    const GccEnt_QualifiedLin&  Qualified3,
                                    const double                Tolerance);

  Standard_EXPORT GccAna_Circ2d3Tan(const GccEnt_QualifiedCirc& Qualified1,
                                    const GccEnt_QualifiedLin&  Qualified2,
                                    const GccEnt_QualifiedLin&  Qualified3,
                                    const double                Tolerance);

  Standard_EXPORT GccAna_Circ2d3Tan(const GccEnt_QualifiedLin& Qualified1,
                                    const GccEnt_QualifiedLin& Qualified2,
                                    const GccEnt_QualifiedLin& Qualified3,
                                    const double               Tolerance);

  Standard_EXPORT GccAna_Circ2d3Tan(const GccEnt_QualifiedCirc& Qualified1,
                                    const GccEnt_QualifiedCirc& Qualified2,
                                    const gp_Pnt2d&             Point3,
                                    const double                Tolerance);

  Standard_EXPORT GccAna_Circ2d3Tan(const GccEnt_QualifiedCirc& Qualified1,
                                    const GccEnt_QualifiedLin&  Qualified2,
                                    const gp_Pnt2d&             Point3,
                                    const double                Tolerance);

  Standard_EXPORT GccAna_Circ2d3Tan(const GccEnt_QualifiedLin& Qualified1,
                                    const GccEnt_QualifiedLin& Qualified2,
                                    const gp_Pnt2d&            Point3,
                                    const double               Tolerance);

  Standard_EXPORT GccAna_Circ2d3Tan(const GccEnt_QualifiedCirc& Qualified1,
                                    const gp_Pnt2d&             Point2,
                                    const gp_Pnt2d&             Point3,
                                    const double                Tolerance);

  Standard_EXPORT GccAna_Circ2d3Tan(const GccEnt_QualifiedLin& Qualified1,
                                    const gp_Pnt2d&            Point2,
                                    const gp_Pnt2d&            Point3,
                                    const double               Tolerance);

  Standard_EXPORT GccAna_Circ2d3Tan(const gp_Pnt2d& Point1,
                                    const gp_Pnt2d& Point2,
                                    const gp_Pnt2d& Point3,
                                    const double    Tolerance);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbSolutions() const;

  Standard_EXPORT gp_Circ2d ThisSolution(const int Index) const;

  Standard_EXPORT void WhichQualifier(const int        Index,
                                      GccEnt_Position& Qualif1,
                                      GccEnt_Position& Qualif2,
                                      GccEnt_Position& Qualif3) const;

  Standard_EXPORT void Tangency1(const int Index,
                                 double&   ParSol,
                                 double&   ParArg,
                                 gp_Pnt2d& PntSol) const;

  Standard_EXPORT void Tangency2(const int Index,
                                 double&   ParSol,
                                 double&   ParArg,
                                 gp_Pnt2d& PntSol) const;

  Standard_EXPORT void Tangency3(const int Index,
                                 double&   ParSol,
                                 double&   ParArg,
                                 gp_Pnt2d& PntSol) const;

  Standard_EXPORT bool IsTheSame1(const int Index) const;

  Standard_EXPORT bool IsTheSame2(const int Index) const;

  Standard_EXPORT bool IsTheSame3(const int Index) const;

private:
  bool                                WellDone;
  int                                 NbrSol;
  NCollection_Array1<gp_Circ2d>       cirsol;
  NCollection_Array1<GccEnt_Position> qualifier1;
  NCollection_Array1<GccEnt_Position> qualifier2;
  NCollection_Array1<GccEnt_Position> qualifier3;
  NCollection_Array1<int>             TheSame1;
  NCollection_Array1<int>             TheSame2;
  NCollection_Array1<int>             TheSame3;
  NCollection_Array1<gp_Pnt2d>        pnttg1sol;
  NCollection_Array1<gp_Pnt2d>        pnttg2sol;
  NCollection_Array1<gp_Pnt2d>        pnttg3sol;
  NCollection_Array1<double>          par1sol;
  NCollection_Array1<double>          par2sol;
  NCollection_Array1<double>          par3sol;
  NCollection_Array1<double>          pararg1;
  NCollection_Array1<double>          pararg2;
  NCollection_Array1<double>          pararg3;
};

#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Circ2d.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class GccEnt_QualifiedCirc;
class Geom2dGcc_QCurve;
class GccEnt_QualifiedLin;

class Geom2dGcc_Circ2d3TanIter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                           const GccEnt_QualifiedCirc& Qualified2,
                                           const Geom2dGcc_QCurve&     Qualified3,
                                           const double                Param1,
                                           const double                Param2,
                                           const double                Param3,
                                           const double                Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                           const Geom2dGcc_QCurve&     Qualified2,
                                           const Geom2dGcc_QCurve&     Qualified3,
                                           const double                Param1,
                                           const double                Param2,
                                           const double                Param3,
                                           const double                Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                           const GccEnt_QualifiedLin&  Qualified2,
                                           const Geom2dGcc_QCurve&     Qualified3,
                                           const double                Param1,
                                           const double                Param2,
                                           const double                Param3,
                                           const double                Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedCirc& Qualified1,
                                           const Geom2dGcc_QCurve&     Qualified2,
                                           const gp_Pnt2d&             Point3,
                                           const double                Param1,
                                           const double                Param2,
                                           const double                Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedLin& Qualified1,
                                           const GccEnt_QualifiedLin& Qualified2,
                                           const Geom2dGcc_QCurve&    Qualified3,
                                           const double               Param1,
                                           const double               Param2,
                                           const double               Param3,
                                           const double               Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedLin& Qualified1,
                                           const Geom2dGcc_QCurve&    Qualified2,
                                           const Geom2dGcc_QCurve&    Qualified3,
                                           const double               Param1,
                                           const double               Param2,
                                           const double               Param3,
                                           const double               Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const GccEnt_QualifiedLin& Qualified1,
                                           const Geom2dGcc_QCurve&    Qualified2,
                                           const gp_Pnt2d&            Point3,
                                           const double               Param1,
                                           const double               Param2,
                                           const double               Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const Geom2dGcc_QCurve& Qualified1,
                                           const gp_Pnt2d&         Point1,
                                           const gp_Pnt2d&         Point2,
                                           const double            Param1,
                                           const double            Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const Geom2dGcc_QCurve& Qualified1,
                                           const Geom2dGcc_QCurve& Qualified2,
                                           const gp_Pnt2d&         Point2,
                                           const double            Param1,
                                           const double            Param2,
                                           const double            Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d3TanIter(const Geom2dGcc_QCurve& Qualified1,
                                           const Geom2dGcc_QCurve& Qualified2,
                                           const Geom2dGcc_QCurve& Qualified3,
                                           const double            Param1,
                                           const double            Param2,
                                           const double            Param3,
                                           const double            Tolerance);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT gp_Circ2d ThisSolution() const;

  Standard_EXPORT void WhichQualifier(GccEnt_Position& Qualif1,
                                      GccEnt_Position& Qualif2,
                                      GccEnt_Position& Qualif3) const;

  Standard_EXPORT void Tangency1(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT void Tangency2(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT void Tangency3(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT bool IsTheSame1() const;

  Standard_EXPORT bool IsTheSame2() const;

  Standard_EXPORT bool IsTheSame3() const;

private:
  bool            WellDone;
  gp_Circ2d       cirsol;
  GccEnt_Position qualifier1;
  GccEnt_Position qualifier2;
  GccEnt_Position qualifier3;
  bool            TheSame1;
  bool            TheSame2;
  bool            TheSame3;
  gp_Pnt2d        pnttg1sol;
  gp_Pnt2d        pnttg2sol;
  gp_Pnt2d        pnttg3sol;
  double          par1sol;
  double          par2sol;
  double          par3sol;
  double          pararg1;
  double          pararg2;
  double          pararg3;
};

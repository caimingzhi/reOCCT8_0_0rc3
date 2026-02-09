#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Circ2d.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class GccEnt_QualifiedCirc;
class Geom2dGcc_QCurve;
class gp_Lin2d;
class GccEnt_QualifiedLin;
class Geom2dAdaptor_Curve;

class Geom2dGcc_Circ2d2TanOnIter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const GccEnt_QualifiedCirc& Qualified1,
                                             const Geom2dGcc_QCurve&     Qualified2,
                                             const gp_Lin2d&             OnLine,
                                             const double                Param1,
                                             const double                Param2,
                                             const double                Param3,
                                             const double                Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const GccEnt_QualifiedLin& Qualified1,
                                             const Geom2dGcc_QCurve&    Qualified2,
                                             const gp_Lin2d&            OnLine,
                                             const double               Param1,
                                             const double               Param2,
                                             const double               Param3,
                                             const double               Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const Geom2dGcc_QCurve& Qualified1,
                                             const Geom2dGcc_QCurve& Qualified2,
                                             const gp_Lin2d&         OnLine,
                                             const double            Param1,
                                             const double            Param2,
                                             const double            Param3,
                                             const double            Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const Geom2dGcc_QCurve& Qualified1,
                                             const gp_Pnt2d&         Point2,
                                             const gp_Lin2d&         OnLine,
                                             const double            Param1,
                                             const double            Param2,
                                             const double            Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const GccEnt_QualifiedCirc& Qualified1,
                                             const Geom2dGcc_QCurve&     Qualified2,
                                             const gp_Circ2d&            OnCirc,
                                             const double                Param1,
                                             const double                Param2,
                                             const double                Param3,
                                             const double                Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const GccEnt_QualifiedLin& Qualified1,
                                             const Geom2dGcc_QCurve&    Qualified2,
                                             const gp_Circ2d&           OnCirc,
                                             const double               Param1,
                                             const double               Param2,
                                             const double               Param3,
                                             const double               Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const Geom2dGcc_QCurve& Qualified1,
                                             const Geom2dGcc_QCurve& Qualified2,
                                             const gp_Circ2d&        OnCirc,
                                             const double            Param1,
                                             const double            Param2,
                                             const double            Param3,
                                             const double            Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const Geom2dGcc_QCurve& Qualified1,
                                             const gp_Pnt2d&         Point2,
                                             const gp_Circ2d&        OnCirc,
                                             const double            Param1,
                                             const double            Param2,
                                             const double            Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const GccEnt_QualifiedCirc& Qualified1,
                                             const Geom2dGcc_QCurve&     Qualified2,
                                             const Geom2dAdaptor_Curve&  OnCurv,
                                             const double                Param1,
                                             const double                Param2,
                                             const double                ParamOn,
                                             const double                Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const GccEnt_QualifiedLin& Qualified1,
                                             const Geom2dGcc_QCurve&    Qualified2,
                                             const Geom2dAdaptor_Curve& OnCurve,
                                             const double               Param1,
                                             const double               Param2,
                                             const double               ParamOn,
                                             const double               Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const Geom2dGcc_QCurve&    Qualified1,
                                             const gp_Pnt2d&            Point2,
                                             const Geom2dAdaptor_Curve& OnCurve,
                                             const double               Param1,
                                             const double               ParamOn,
                                             const double               Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOnIter(const Geom2dGcc_QCurve&    Qualified1,
                                             const Geom2dGcc_QCurve&    Qualified2,
                                             const Geom2dAdaptor_Curve& OnCurve,
                                             const double               Param1,
                                             const double               Param2,
                                             const double               ParamOn,
                                             const double               Tolerance);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT gp_Circ2d ThisSolution() const;

  Standard_EXPORT void WhichQualifier(GccEnt_Position& Qualif1, GccEnt_Position& Qualif2) const;

  Standard_EXPORT void Tangency1(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT void Tangency2(double& ParSol, double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT void CenterOn3(double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT bool IsTheSame1() const;

  Standard_EXPORT bool IsTheSame2() const;

private:
  bool            WellDone;
  gp_Circ2d       cirsol;
  GccEnt_Position qualifier1;
  GccEnt_Position qualifier2;
  bool            TheSame1;
  bool            TheSame2;
  gp_Pnt2d        pnttg1sol;
  gp_Pnt2d        pnttg2sol;
  gp_Pnt2d        pntcen;
  double          par1sol;
  double          par2sol;
  double          pararg1;
  double          pararg2;
  double          parcen3;
};

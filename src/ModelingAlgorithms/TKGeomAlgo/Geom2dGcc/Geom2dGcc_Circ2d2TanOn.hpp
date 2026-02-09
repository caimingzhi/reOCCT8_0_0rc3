#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Circ2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class Geom2dGcc_QualifiedCurve;
class Geom2dAdaptor_Curve;
class Geom2d_Point;
class GccAna_Circ2d2TanOn;
class Geom2dGcc_Circ2d2TanOnGeo;
class gp_Circ2d;
class gp_Pnt2d;

class Geom2dGcc_Circ2d2TanOn
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_Circ2d2TanOn(const Geom2dGcc_QualifiedCurve& Qualified1,
                                         const Geom2dGcc_QualifiedCurve& Qualified2,
                                         const Geom2dAdaptor_Curve&      OnCurve,
                                         const double                    Tolerance,
                                         const double                    Param1,
                                         const double                    Param2,
                                         const double                    ParamOn);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOn(const Geom2dGcc_QualifiedCurve&  Qualified1,
                                         const occ::handle<Geom2d_Point>& Point,
                                         const Geom2dAdaptor_Curve&       OnCurve,
                                         const double                     Tolerance,
                                         const double                     Param1,
                                         const double                     ParamOn);

  Standard_EXPORT Geom2dGcc_Circ2d2TanOn(const occ::handle<Geom2d_Point>& Point1,
                                         const occ::handle<Geom2d_Point>& Point2,
                                         const Geom2dAdaptor_Curve&       OnCurve,
                                         const double                     Tolerance);

  Standard_EXPORT void Results(const GccAna_Circ2d2TanOn& Circ);

  Standard_EXPORT void Results(const Geom2dGcc_Circ2d2TanOnGeo& Circ);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbSolutions() const;

  Standard_EXPORT gp_Circ2d ThisSolution(const int Index) const;

  Standard_EXPORT void WhichQualifier(const int        Index,
                                      GccEnt_Position& Qualif1,
                                      GccEnt_Position& Qualif2) const;

  Standard_EXPORT void Tangency1(const int Index,
                                 double&   ParSol,
                                 double&   ParArg,
                                 gp_Pnt2d& PntSol) const;

  Standard_EXPORT void Tangency2(const int Index,
                                 double&   ParSol,
                                 double&   ParArg,
                                 gp_Pnt2d& PntSol) const;

  Standard_EXPORT void CenterOn3(const int Index, double& ParArg, gp_Pnt2d& PntSol) const;

  Standard_EXPORT bool IsTheSame1(const int Index) const;

  Standard_EXPORT bool IsTheSame2(const int Index) const;

private:
  bool                                WellDone;
  NCollection_Array1<gp_Circ2d>       cirsol;
  int                                 NbrSol;
  NCollection_Array1<GccEnt_Position> qualifier1;
  NCollection_Array1<GccEnt_Position> qualifier2;
  NCollection_Array1<int>             TheSame1;
  NCollection_Array1<int>             TheSame2;
  NCollection_Array1<gp_Pnt2d>        pnttg1sol;
  NCollection_Array1<gp_Pnt2d>        pnttg2sol;
  NCollection_Array1<gp_Pnt2d>        pntcen;
  NCollection_Array1<double>          par1sol;
  NCollection_Array1<double>          par2sol;
  NCollection_Array1<double>          pararg1;
  NCollection_Array1<double>          pararg2;
  NCollection_Array1<double>          parcen3;
  bool                                Invert;
};

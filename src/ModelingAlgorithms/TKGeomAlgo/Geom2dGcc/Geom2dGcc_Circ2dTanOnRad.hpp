#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <gp_Circ2d.hpp>
#include <NCollection_Array1.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class Geom2dGcc_QualifiedCurve;
class Geom2dAdaptor_Curve;
class Geom2d_Point;
class GccAna_Circ2dTanOnRad;
class Geom2dGcc_Circ2dTanOnRadGeo;
class gp_Circ2d;
class gp_Pnt2d;

class Geom2dGcc_Circ2dTanOnRad
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_Circ2dTanOnRad(const Geom2dGcc_QualifiedCurve& Qualified1,
                                           const Geom2dAdaptor_Curve&      OnCurv,
                                           const double                    Radius,
                                           const double                    Tolerance);

  Standard_EXPORT Geom2dGcc_Circ2dTanOnRad(const occ::handle<Geom2d_Point>& Point1,
                                           const Geom2dAdaptor_Curve&       OnCurv,
                                           const double                     Radius,
                                           const double                     Tolerance);

  Standard_EXPORT void Results(const GccAna_Circ2dTanOnRad& Circ);

  Standard_EXPORT void Results(const Geom2dGcc_Circ2dTanOnRadGeo& Circ);

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
  NCollection_Array1<double>          par1sol;
  NCollection_Array1<double>          pararg1;
  NCollection_Array1<gp_Pnt2d>        pntcen3;
  NCollection_Array1<double>          parcen3;
};

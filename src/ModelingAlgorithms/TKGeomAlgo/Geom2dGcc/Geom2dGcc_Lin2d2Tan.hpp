#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Lin2d.hpp>
#include <NCollection_Array1.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Pnt2d.hpp>
class Geom2dGcc_QualifiedCurve;
class gp_Pnt2d;
class gp_Lin2d;
class Geom2dGcc_Lin2d2TanIter;
class Geom2dAdaptor_Curve;

class Geom2dGcc_Lin2d2Tan
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_Lin2d2Tan(const Geom2dGcc_QualifiedCurve& Qualified1,
                                      const Geom2dGcc_QualifiedCurve& Qualified2,
                                      const double                    Tolang);

  Standard_EXPORT Geom2dGcc_Lin2d2Tan(const Geom2dGcc_QualifiedCurve& Qualified1,
                                      const gp_Pnt2d&                 ThePoint,
                                      const double                    Tolang);

  Standard_EXPORT Geom2dGcc_Lin2d2Tan(const Geom2dGcc_QualifiedCurve& Qualified1,
                                      const Geom2dGcc_QualifiedCurve& Qualified2,
                                      const double                    Tolang,
                                      const double                    Param1,
                                      const double                    Param2);

  Standard_EXPORT Geom2dGcc_Lin2d2Tan(const Geom2dGcc_QualifiedCurve& Qualified1,
                                      const gp_Pnt2d&                 ThePoint,
                                      const double                    Tolang,
                                      const double                    Param1);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbSolutions() const;

  Standard_EXPORT gp_Lin2d ThisSolution(const int Index) const;

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

private:
  Standard_EXPORT bool Add(const int                      theIndex,
                           const Geom2dGcc_Lin2d2TanIter& theLin,
                           const double                   theTol,
                           const Geom2dAdaptor_Curve&     theC1,
                           const Geom2dAdaptor_Curve&     theC2);

  bool                                WellDone;
  int                                 NbrSol;
  NCollection_Array1<gp_Lin2d>        linsol;
  NCollection_Array1<GccEnt_Position> qualifier1;
  NCollection_Array1<GccEnt_Position> qualifier2;
  NCollection_Array1<gp_Pnt2d>        pnttg1sol;
  NCollection_Array1<gp_Pnt2d>        pnttg2sol;
  NCollection_Array1<double>          par1sol;
  NCollection_Array1<double>          par2sol;
  NCollection_Array1<double>          pararg1;
  NCollection_Array1<double>          pararg2;
};

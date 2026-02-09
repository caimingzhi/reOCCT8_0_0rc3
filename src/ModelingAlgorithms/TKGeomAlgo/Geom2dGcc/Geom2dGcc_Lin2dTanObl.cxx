#include <GccAna_Lin2dTanObl.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2dGcc_CurveTool.hpp>
#include <Geom2dGcc_Lin2dTanObl.hpp>
#include <Geom2dGcc_Lin2dTanOblIter.hpp>
#include <Geom2dGcc_QCurve.hpp>
#include <Geom2dGcc_QualifiedCurve.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

Geom2dGcc_Lin2dTanObl::Geom2dGcc_Lin2dTanObl(const Geom2dGcc_QualifiedCurve& Qualified1,
                                             const gp_Lin2d&                 TheLine,
                                             const double                    TolAng,
                                             const double                    Angle)
    : Paral2(false),
      linsol(1, 2),
      qualifier1(1, 2),
      pnttg1sol(1, 2),
      pntint2sol(1, 2),
      par1sol(1, 2),
      par2sol(1, 2),
      pararg1(1, 2),
      pararg2(1, 2)
{
  Geom2dAdaptor_Curve              C1    = Qualified1.Qualified();
  const occ::handle<Geom2d_Curve>& CC1   = C1.Curve();
  GeomAbs_CurveType                Type1 = C1.GetType();

  WellDone = false;
  NbrSol   = 0;
  if (Type1 == GeomAbs_Circle)
  {
    occ::handle<Geom2d_Circle> CCC1 = occ::down_cast<Geom2d_Circle>(CC1);
    gp_Circ2d                  c1(CCC1->Circ2d());
    GccEnt_QualifiedCirc       Qc1 = GccEnt_QualifiedCirc(c1, Qualified1.Qualifier());
    GccAna_Lin2dTanObl         Lin(Qc1, TheLine, Angle);
    WellDone = Lin.IsDone();
    if (WellDone)
    {
      NbrSol = Lin.NbSolutions();
      for (int i = 1; i <= NbrSol; i++)
      {
        linsol(i) = Lin.ThisSolution(i);
        Lin.Tangency1(i, par1sol(i), pararg1(i), pnttg1sol(i));
        Lin.Intersection2(i, par2sol(i), pararg2(i), pntint2sol(i));
        Lin.WhichQualifier(i, qualifier1(i));
      }
    }
  }
  else
  {
    Geom2dGcc_QCurve Qc1(C1, Qualified1.Qualifier());
    double           aFirstPar  = Geom2dGcc_CurveTool::FirstParameter(C1);
    double           aLastPar   = Geom2dGcc_CurveTool::LastParameter(C1);
    int              aNbSamples = Geom2dGcc_CurveTool::NbSamples(C1);
    double           aStep      = (aLastPar - aFirstPar) / aNbSamples;
    double           Param1     = aFirstPar;
    int              i;

    for (i = 0; i <= aNbSamples && NbrSol < 2; i++)
    {
      Geom2dGcc_Lin2dTanOblIter Lin(Qc1, TheLine, Param1, TolAng, Angle);

      if (Lin.IsDone())
      {
        if (Add(NbrSol + 1, Lin, TolAng, C1))
          NbrSol++;
      }

      Param1 += aStep;
    }

    WellDone = (NbrSol > 0);
  }
}

Geom2dGcc_Lin2dTanObl::Geom2dGcc_Lin2dTanObl(const Geom2dGcc_QualifiedCurve& Qualified1,
                                             const gp_Lin2d&                 TheLine,
                                             const double                    TolAng,
                                             const double                    Param1,
                                             const double                    Angle)
    : Paral2(false),
      linsol(1, 2),
      qualifier1(1, 2),
      pnttg1sol(1, 2),
      pntint2sol(1, 2),
      par1sol(1, 2),
      par2sol(1, 2),
      pararg1(1, 2),
      pararg2(1, 2)
{
  Geom2dAdaptor_Curve              C1    = Qualified1.Qualified();
  const occ::handle<Geom2d_Curve>& CC1   = C1.Curve();
  GeomAbs_CurveType                Type1 = C1.GetType();

  WellDone = false;
  NbrSol   = 0;
  if (Type1 == GeomAbs_Circle)
  {
    occ::handle<Geom2d_Circle> CCC1 = occ::down_cast<Geom2d_Circle>(CC1);
    gp_Circ2d                  c1(CCC1->Circ2d());
    GccEnt_QualifiedCirc       Qc1 = GccEnt_QualifiedCirc(c1, Qualified1.Qualifier());
    GccAna_Lin2dTanObl         Lin(Qc1, TheLine, Angle);
    WellDone = Lin.IsDone();
    if (WellDone)
    {
      NbrSol = Lin.NbSolutions();
      for (int i = 1; i <= NbrSol; i++)
      {
        linsol(i) = Lin.ThisSolution(i);
        Lin.Tangency1(i, par1sol(i), pararg1(i), pnttg1sol(i));
        Lin.Intersection2(i, par2sol(i), pararg2(i), pntint2sol(i));
        Lin.WhichQualifier(i, qualifier1(i));
      }
    }
  }
  else
  {
    Geom2dGcc_QCurve          Qc1(C1, Qualified1.Qualifier());
    Geom2dGcc_Lin2dTanOblIter Lin(Qc1, TheLine, TolAng, Param1, Angle);
    WellDone = Lin.IsDone();
    if (WellDone)
    {
      linsol(1) = Lin.ThisSolution();
      Lin.Tangency1(par1sol(1), pararg1(1), pnttg1sol(1));
      Lin.Intersection2(par2sol(1), pararg2(1), pntint2sol(1));
      Lin.WhichQualifier(qualifier1(1));
    }
  }
}

bool Geom2dGcc_Lin2dTanObl::IsDone() const
{
  return WellDone;
}

int Geom2dGcc_Lin2dTanObl::NbSolutions() const
{
  return NbrSol;
}

gp_Lin2d Geom2dGcc_Lin2dTanObl::ThisSolution(const int Index) const
{

  if (Index > NbrSol || Index <= 0)
  {
    throw Standard_OutOfRange();
  }
  return linsol(Index);
}

void Geom2dGcc_Lin2dTanObl::WhichQualifier(const int Index, GccEnt_Position& Qualif1) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  else
  {
    Qualif1 = qualifier1(Index);
  }
}

void Geom2dGcc_Lin2dTanObl::Tangency1(const int Index,
                                      double&   ParSol,
                                      double&   ParArg,
                                      gp_Pnt2d& PntSol) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  else
  {
    ParSol = par1sol(Index);
    ParArg = pararg1(Index);
    PntSol = pnttg1sol(Index);
  }
}

void Geom2dGcc_Lin2dTanObl::Intersection2(const int Index,
                                          double&   ParSol,
                                          double&   ParArg,
                                          gp_Pnt2d& PntSol) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  else
  {
    ParSol = par2sol(Index);
    ParArg = pararg2(Index);
    PntSol = pntint2sol(Index);
  }
}

bool Geom2dGcc_Lin2dTanObl::Add(const int                        theIndex,
                                const Geom2dGcc_Lin2dTanOblIter& theLin,
                                const double                     theTol,
                                const Geom2dAdaptor_Curve&       theC1)
{
  int      i;
  double   aPar1sol;
  double   aPar2sol;
  double   aPar1arg;
  double   aPar2arg;
  gp_Pnt2d aPnt1Sol;
  gp_Pnt2d aPnt2Sol;
  gp_Lin2d aLin = theLin.ThisSolution();

  theLin.Tangency1(aPar1sol, aPar1arg, aPnt1Sol);
  theLin.Intersection2(aPar2sol, aPar2arg, aPnt2Sol);

  for (i = 1; i < theIndex; i++)
  {
    if (std::abs(aPar1arg - pararg1(i)) <= theTol && std::abs(aPar2arg - pararg2(i)) <= theTol)
      return false;
  }

  gp_Dir2d aLinDir = aLin.Direction();
  gp_Vec2d aVTan;
  gp_Pnt2d aPoint;

  Geom2dGcc_CurveTool::D1(theC1, aPar1arg, aPoint, aVTan);

  if (std::abs(aLinDir.Crossed(gp_Dir2d(aVTan))) > theTol)
    return false;

  linsol(theIndex)     = aLin;
  par1sol(theIndex)    = aPar1sol;
  pararg1(theIndex)    = aPar1arg;
  pnttg1sol(theIndex)  = aPnt1Sol;
  par2sol(theIndex)    = aPar2sol;
  pararg2(theIndex)    = aPar2arg;
  pntint2sol(theIndex) = aPnt2Sol;

  theLin.WhichQualifier(qualifier1(theIndex));

  return true;
}

#include <GccAna_Circ2dTanCen.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_Point.hpp>
#include <Geom2dGcc_Circ2dTanCen.hpp>
#include <Geom2dGcc_Circ2dTanCenGeo.hpp>
#include <Geom2dGcc_QCurve.hpp>
#include <Geom2dGcc_QualifiedCurve.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

Geom2dGcc_Circ2dTanCen::Geom2dGcc_Circ2dTanCen(const Geom2dGcc_QualifiedCurve&  Qualified1,
                                               const occ::handle<Geom2d_Point>& PCenter,
                                               const double                     Tolerance)
    : cirsol(1, 2),
      qualifier1(1, 2),
      TheSame1(1, 2),
      pnttg1sol(1, 2),
      par1sol(1, 2),
      pararg1(1, 2)
{
  Geom2dAdaptor_Curve              C1    = Qualified1.Qualified();
  const occ::handle<Geom2d_Curve>& CC1   = C1.Curve();
  GeomAbs_CurveType                Type1 = C1.GetType();

  gp_Pnt2d pcenter(PCenter->Pnt2d());
  NbrSol = 0;
  if ((Type1 == GeomAbs_Line || Type1 == GeomAbs_Circle))
  {
    if (Type1 == GeomAbs_Circle)
    {
      occ::handle<Geom2d_Circle> CCC1 = occ::down_cast<Geom2d_Circle>(CC1);
      gp_Circ2d                  c1(CCC1->Circ2d());
      GccEnt_QualifiedCirc       Qc1(c1, Qualified1.Qualifier());
      GccAna_Circ2dTanCen        Circ(Qc1, pcenter, Tolerance);
      WellDone = Circ.IsDone();
      NbrSol   = Circ.NbSolutions();
      for (int j = 1; j <= NbrSol; j++)
      {
        cirsol(j) = Circ.ThisSolution(j);
        Circ.WhichQualifier(j, qualifier1(j));
        if (Circ.IsTheSame1(j))
        {
          TheSame1(j) = 1;
        }
        else
        {
          TheSame1(j) = 0;
        }
        Circ.Tangency1(j, par1sol(j), pararg1(j), pnttg1sol(j));
      }
    }
    else
    {
      occ::handle<Geom2d_Line> LL1 = occ::down_cast<Geom2d_Line>(CC1);
      gp_Lin2d                 l1(LL1->Lin2d());
      GccAna_Circ2dTanCen      Circ(l1, pcenter);
      WellDone = Circ.IsDone();
      NbrSol   = Circ.NbSolutions();
      for (int j = 1; j <= NbrSol; j++)
      {
        cirsol(j) = Circ.ThisSolution(j);
        Circ.WhichQualifier(j, qualifier1(j));
        if (Circ.IsTheSame1(j))
        {
          TheSame1(j) = 1;
        }
        else
        {
          TheSame1(j) = 0;
        }
        Circ.Tangency1(j, par1sol(j), pararg1(j), pnttg1sol(j));
      }
    }
  }

  else
  {
    Geom2dGcc_QCurve          Qc1(C1, Qualified1.Qualifier());
    Geom2dGcc_Circ2dTanCenGeo Circ(Qc1, pcenter, Tolerance);
    WellDone = Circ.IsDone();
    NbrSol   = Circ.NbSolutions();
    for (int j = 1; j <= NbrSol; j++)
    {
      cirsol(j)   = Circ.ThisSolution(j);
      TheSame1(j) = 0;
      Circ.Tangency1(j, par1sol(j), pararg1(j), pnttg1sol(j));
      Circ.WhichQualifier(j, qualifier1(j));
    }
  }
}

bool Geom2dGcc_Circ2dTanCen::IsDone() const
{
  return WellDone;
}

int Geom2dGcc_Circ2dTanCen::NbSolutions() const
{
  return NbrSol;
}

gp_Circ2d Geom2dGcc_Circ2dTanCen::ThisSolution(const int Index) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  return cirsol(Index);
}

void Geom2dGcc_Circ2dTanCen::WhichQualifier(const int Index, GccEnt_Position& Qualif1) const
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

void Geom2dGcc_Circ2dTanCen::Tangency1(const int Index,
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
    if (TheSame1(Index) == 0)
    {
      ParSol = par1sol(Index);
      ParArg = pararg1(Index);
      PntSol = pnttg1sol(Index);
    }
    else
    {
      throw StdFail_NotDone();
    }
  }
}

bool Geom2dGcc_Circ2dTanCen::IsTheSame1(const int Index) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  if (TheSame1(Index) == 0)
  {
    return false;
  }
  return true;
}

#include <gce_MakeLin.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

gce_MakeLin::gce_MakeLin(const gp_Ax1& A1)
{
  TheLin   = gp_Lin(A1);
  TheError = gce_Done;
}

gce_MakeLin::gce_MakeLin(const gp_Pnt& P, const gp_Dir& V)
{
  TheLin   = gp_Lin(P, V);
  TheError = gce_Done;
}

gce_MakeLin::gce_MakeLin(const gp_Pnt& P1, const gp_Pnt& P2)
{
  if (P1.Distance(P2) >= gp::Resolution())
  {
    TheLin   = gp_Lin(P1, gp_Dir(P2.XYZ() - P1.XYZ()));
    TheError = gce_Done;
  }
  else
  {
    TheError = gce_ConfusedPoints;
  }
}

gce_MakeLin::gce_MakeLin(const gp_Lin& Lin, const gp_Pnt& P)
{
  TheLin   = gp_Lin(P, Lin.Direction());
  TheError = gce_Done;
}

const gp_Lin& gce_MakeLin::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeLin::Value() - no result");
  return TheLin;
}

const gp_Lin& gce_MakeLin::Operator() const
{
  return Value();
}

gce_MakeLin::operator gp_Lin() const
{
  return Value();
}

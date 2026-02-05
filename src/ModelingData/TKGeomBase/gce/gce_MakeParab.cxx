#include <gce_MakeParab.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

gce_MakeParab::gce_MakeParab(const gp_Ax2& A2, const double Focal)
{
  if (Focal < 0.0)
  {
    TheError = gce_NullFocusLength;
  }
  else
  {
    TheParab = gp_Parab(A2, Focal);
    TheError = gce_Done;
  }
}

gce_MakeParab::gce_MakeParab(const gp_Ax1& D, const gp_Pnt& F)
{
  TheParab = gp_Parab(D, F);
  TheError = gce_Done;
}

const gp_Parab& gce_MakeParab::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeParab::Value() - no result");
  return TheParab;
}

const gp_Parab& gce_MakeParab::Operator() const
{
  return Value();
}

gce_MakeParab::operator gp_Parab() const
{
  return Value();
}

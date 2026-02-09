#include <gce_MakeDir.hpp>
#include <gp.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <StdFail_NotDone.hpp>

gce_MakeDir::gce_MakeDir(const gp_Pnt& P1, const gp_Pnt& P2)
{
  if (P1.Distance(P2) <= gp::Resolution())
  {
    TheError = gce_ConfusedPoints;
  }
  else
  {
    TheDir   = gp_Dir(P2.XYZ() - P1.XYZ());
    TheError = gce_Done;
  }
}

gce_MakeDir::gce_MakeDir(const gp_XYZ& Coord)
{
  if (Coord.Modulus() <= gp::Resolution())
  {
    TheError = gce_NullVector;
  }
  else
  {
    TheDir   = gp_Dir(Coord);
    TheError = gce_Done;
  }
}

gce_MakeDir::gce_MakeDir(const gp_Vec& V)
{
  if (V.Magnitude() <= gp::Resolution())
  {
    TheError = gce_NullVector;
  }
  else
  {
    TheDir   = gp_Dir(V);
    TheError = gce_Done;
  }
}

gce_MakeDir::gce_MakeDir(const double Xv, const double Yv, const double Zv)
{
  if (Xv * Xv + Yv * Yv + Zv * Zv <= gp::Resolution())
  {
    TheError = gce_NullVector;
  }
  else
  {
    TheDir   = gp_Dir(Xv, Yv, Zv);
    TheError = gce_Done;
  }
}

const gp_Dir& gce_MakeDir::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeDir::Value() - no result");
  return TheDir;
}

const gp_Dir& gce_MakeDir::Operator() const
{
  return Value();
}

gce_MakeDir::operator gp_Dir() const
{
  return Value();
}

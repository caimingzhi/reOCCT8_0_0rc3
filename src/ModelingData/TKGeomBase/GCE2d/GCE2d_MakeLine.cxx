#include <GCE2d_MakeLine.hpp>
#include <gce_MakeLin2d.hpp>
#include <Geom2d_Line.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>

//=========================================================================
//   Constructions of 2d geometrical elements from Geom2d.
//=========================================================================
GCE2d_MakeLine::GCE2d_MakeLine(const gp_Ax2d& A)
{
  TheError = gce_Done;
  TheLine  = new Geom2d_Line(A);
}

GCE2d_MakeLine::GCE2d_MakeLine(const gp_Lin2d& L)
{
  TheError = gce_Done;
  TheLine  = new Geom2d_Line(L);
}

GCE2d_MakeLine::GCE2d_MakeLine(const gp_Pnt2d& P, const gp_Dir2d& V)
{
  TheError = gce_Done;
  TheLine  = new Geom2d_Line(P, V);
}

GCE2d_MakeLine::GCE2d_MakeLine(const gp_Pnt2d& P1, const gp_Pnt2d& P2)
{
  gce_MakeLin2d L(P1, P2);
  TheError = L.Status();
  if (TheError == gce_Done)
  {
    TheLine = new Geom2d_Line(L.Value());
  }
}

GCE2d_MakeLine::GCE2d_MakeLine(const gp_Lin2d& Lin, const gp_Pnt2d& Point)
{
  gce_MakeLin2d L(Lin, Point);
  TheError = L.Status();
  if (TheError == gce_Done)
  {
    TheLine = new Geom2d_Line(L.Value());
  }
}

GCE2d_MakeLine::GCE2d_MakeLine(const gp_Lin2d& Lin, const double Dist)
{
  gce_MakeLin2d L(Lin, Dist);
  TheError = L.Status();
  if (TheError == gce_Done)
  {
    TheLine = new Geom2d_Line(L.Value());
  }
}

const occ::handle<Geom2d_Line>& GCE2d_MakeLine::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GCE2d_MakeLine::Value() - no result");
  return TheLine;
}

#include <GC_MakeCircle.hpp>
#include <gce_MakeCirc.hpp>
#include <Geom_Circle.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeCircle::GC_MakeCircle(const gp_Circ& C)
{
  TheError  = gce_Done;
  TheCircle = new Geom_Circle(C);
}

GC_MakeCircle::GC_MakeCircle(const gp_Ax2& A2, const double Radius)
{
  if (Radius < 0.)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    TheError  = gce_Done;
    TheCircle = new Geom_Circle(gp_Circ(A2, Radius));
  }
}

GC_MakeCircle::GC_MakeCircle(const gp_Circ& Circ, const gp_Pnt& Point)
{
  gp_Circ C = gce_MakeCirc(Circ, Point);
  TheCircle = new Geom_Circle(C);
  TheError  = gce_Done;
}

GC_MakeCircle::GC_MakeCircle(const gp_Circ& Circ, const double Dist)
{
  gce_MakeCirc C = gce_MakeCirc(Circ, Dist);
  TheError       = C.Status();
  if (TheError == gce_Done)
  {
    TheCircle = new Geom_Circle(C.Value());
  }
}

GC_MakeCircle::GC_MakeCircle(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3)
{
  gce_MakeCirc C = gce_MakeCirc(P1, P2, P3);
  TheError       = C.Status();
  if (TheError == gce_Done)
  {
    TheCircle = new Geom_Circle(C.Value());
  }
}

GC_MakeCircle::GC_MakeCircle(const gp_Pnt& Point, const gp_Dir& Norm, const double Radius)
{
  gce_MakeCirc C = gce_MakeCirc(Point, Norm, Radius);
  TheError       = C.Status();
  if (TheError == gce_Done)
  {
    TheCircle = new Geom_Circle(C.Value());
  }
}

GC_MakeCircle::GC_MakeCircle(const gp_Pnt& Point, const gp_Pnt& PtAxis, const double Radius)
{
  gce_MakeCirc C = gce_MakeCirc(Point, PtAxis, Radius);
  TheError       = C.Status();
  if (TheError == gce_Done)
  {
    TheCircle = new Geom_Circle(C.Value());
  }
}

GC_MakeCircle::GC_MakeCircle(const gp_Ax1& Axis, const double Radius)
{
  gce_MakeCirc C = gce_MakeCirc(Axis, Radius);
  TheError       = C.Status();
  if (TheError == gce_Done)
  {
    TheCircle = new Geom_Circle(C.Value());
  }
}

const occ::handle<Geom_Circle>& GC_MakeCircle::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeCircle::Value() - no result");
  return TheCircle;
}

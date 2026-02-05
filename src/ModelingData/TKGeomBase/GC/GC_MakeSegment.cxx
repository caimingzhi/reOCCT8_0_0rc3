#include <ElCLib.hpp>
#include <GC_MakeLine.hpp>
#include <GC_MakeSegment.hpp>
#include <Geom_Line.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeSegment::GC_MakeSegment(const gp_Pnt& P1, const gp_Pnt& P2)
{
  double                 dist = P1.Distance(P2);
  occ::handle<Geom_Line> L    = GC_MakeLine(P1, P2);
  TheSegment                  = new Geom_TrimmedCurve(L, 0., dist, true);
  TheError                    = gce_Done;
}

GC_MakeSegment::GC_MakeSegment(const gp_Lin& Line, const gp_Pnt& Point, const double U)
{
  double                 Ufirst = ElCLib::Parameter(Line, Point);
  occ::handle<Geom_Line> L      = new Geom_Line(Line);
  TheSegment                    = new Geom_TrimmedCurve(L, Ufirst, U, true);
  TheError                      = gce_Done;
}

GC_MakeSegment::GC_MakeSegment(const gp_Lin& Line, const gp_Pnt& P1, const gp_Pnt& P2)
{
  double                 Ufirst = ElCLib::Parameter(Line, P1);
  double                 Ulast  = ElCLib::Parameter(Line, P2);
  occ::handle<Geom_Line> L      = new Geom_Line(Line);
  TheSegment                    = new Geom_TrimmedCurve(L, Ufirst, Ulast, true);
  TheError                      = gce_Done;
}

GC_MakeSegment::GC_MakeSegment(const gp_Lin& Line, const double U1, const double U2)
{
  occ::handle<Geom_Line> L = new Geom_Line(Line);
  TheSegment               = new Geom_TrimmedCurve(L, U1, U2, true);
  TheError                 = gce_Done;
}

const occ::handle<Geom_TrimmedCurve>& GC_MakeSegment::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeSegment::Value() - no result");
  return TheSegment;
}

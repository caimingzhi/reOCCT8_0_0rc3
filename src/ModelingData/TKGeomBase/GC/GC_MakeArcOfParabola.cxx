#include <ElCLib.hpp>
#include <GC_MakeArcOfParabola.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeArcOfParabola::GC_MakeArcOfParabola(const gp_Parab& Parab,
                                           const gp_Pnt&   P1,
                                           const gp_Pnt&   P2,
                                           const bool      Sense)
{
  double                     Alpha1 = ElCLib::Parameter(Parab, P1);
  double                     Alpha2 = ElCLib::Parameter(Parab, P2);
  occ::handle<Geom_Parabola> P      = new Geom_Parabola(Parab);
  TheArc                            = new Geom_TrimmedCurve(P, Alpha1, Alpha2, Sense);
  TheError                          = gce_Done;
}

GC_MakeArcOfParabola::GC_MakeArcOfParabola(const gp_Parab& Parab,
                                           const gp_Pnt&   P,
                                           const double    Alpha,
                                           const bool      Sense)
{
  double                     Alphafirst = ElCLib::Parameter(Parab, P);
  occ::handle<Geom_Parabola> Parabola   = new Geom_Parabola(Parab);
  TheArc                                = new Geom_TrimmedCurve(Parabola, Alphafirst, Alpha, Sense);
  TheError                              = gce_Done;
}

GC_MakeArcOfParabola::GC_MakeArcOfParabola(const gp_Parab& Parab,
                                           const double    Alpha1,
                                           const double    Alpha2,
                                           const bool      Sense)
{
  occ::handle<Geom_Parabola> P = new Geom_Parabola(Parab);
  TheArc                       = new Geom_TrimmedCurve(P, Alpha1, Alpha2, Sense);
  TheError                     = gce_Done;
}

const occ::handle<Geom_TrimmedCurve>& GC_MakeArcOfParabola::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeArcOfParabola::Value() - no result");
  return TheArc;
}

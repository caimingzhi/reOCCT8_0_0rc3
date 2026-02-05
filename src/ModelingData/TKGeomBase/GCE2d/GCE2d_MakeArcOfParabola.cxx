#include <ElCLib.hpp>
#include <GCE2d_MakeArcOfParabola.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>

GCE2d_MakeArcOfParabola::GCE2d_MakeArcOfParabola(const gp_Parab2d& Parab,
                                                 const gp_Pnt2d&   P1,
                                                 const gp_Pnt2d&   P2,
                                                 const bool        Sense)
{
  double                       Alpha1 = ElCLib::Parameter(Parab, P1);
  double                       Alpha2 = ElCLib::Parameter(Parab, P2);
  occ::handle<Geom2d_Parabola> P      = new Geom2d_Parabola(Parab);
  TheArc                              = new Geom2d_TrimmedCurve(P, Alpha1, Alpha2, Sense);
  TheError                            = gce_Done;
}

GCE2d_MakeArcOfParabola::GCE2d_MakeArcOfParabola(const gp_Parab2d& Parab,
                                                 const gp_Pnt2d&   P,
                                                 const double      Alpha,
                                                 const bool        Sense)
{
  double                       Alphafirst = ElCLib::Parameter(Parab, P);
  occ::handle<Geom2d_Parabola> Parabola   = new Geom2d_Parabola(Parab);
  TheArc   = new Geom2d_TrimmedCurve(Parabola, Alphafirst, Alpha, Sense);
  TheError = gce_Done;
}

GCE2d_MakeArcOfParabola::GCE2d_MakeArcOfParabola(const gp_Parab2d& Parab,
                                                 const double      Alpha1,
                                                 const double      Alpha2,
                                                 const bool        Sense)
{
  occ::handle<Geom2d_Parabola> P = new Geom2d_Parabola(Parab);
  TheArc                         = new Geom2d_TrimmedCurve(P, Alpha1, Alpha2, Sense);
  TheError                       = gce_Done;
}

const occ::handle<Geom2d_TrimmedCurve>& GCE2d_MakeArcOfParabola::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GCE2d_MakeArcOfParabola::Value() - no result");
  return TheArc;
}

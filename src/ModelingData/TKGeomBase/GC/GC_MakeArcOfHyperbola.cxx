#include <ElCLib.hpp>
#include <GC_MakeArcOfHyperbola.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Hypr.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeArcOfHyperbola::GC_MakeArcOfHyperbola(const gp_Hypr& Hypr,
                                             const gp_Pnt&  P1,
                                             const gp_Pnt&  P2,
                                             const bool     Sense)
{
  double                      Alpha1 = ElCLib::Parameter(Hypr, P1);
  double                      Alpha2 = ElCLib::Parameter(Hypr, P2);
  occ::handle<Geom_Hyperbola> H      = new Geom_Hyperbola(Hypr);
  TheArc                             = new Geom_TrimmedCurve(H, Alpha1, Alpha2, Sense);
  TheError                           = gce_Done;
}

GC_MakeArcOfHyperbola::GC_MakeArcOfHyperbola(const gp_Hypr& Hypr,
                                             const gp_Pnt&  P,
                                             const double   Alpha,
                                             const bool     Sense)
{
  double                      Alphafirst = ElCLib::Parameter(Hypr, P);
  occ::handle<Geom_Hyperbola> H          = new Geom_Hyperbola(Hypr);
  TheArc                                 = new Geom_TrimmedCurve(H, Alphafirst, Alpha, Sense);
  TheError                               = gce_Done;
}

GC_MakeArcOfHyperbola::GC_MakeArcOfHyperbola(const gp_Hypr& Hypr,
                                             const double   Alpha1,
                                             const double   Alpha2,
                                             const bool     Sense)
{
  occ::handle<Geom_Hyperbola> H = new Geom_Hyperbola(Hypr);
  TheArc                        = new Geom_TrimmedCurve(H, Alpha1, Alpha2, Sense);
  TheError                      = gce_Done;
}

const occ::handle<Geom_TrimmedCurve>& GC_MakeArcOfHyperbola::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeArcOfHyperbola::Value() - no result");
  return TheArc;
}

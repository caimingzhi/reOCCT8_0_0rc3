#include <ElCLib.hpp>
#include <GCE2d_MakeArcOfHyperbola.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>

GCE2d_MakeArcOfHyperbola::GCE2d_MakeArcOfHyperbola(const gp_Hypr2d& Hypr,
                                                   const gp_Pnt2d&  P1,
                                                   const gp_Pnt2d&  P2,
                                                   const bool       Sense)
{
  double                        Alpha1 = ElCLib::Parameter(Hypr, P1);
  double                        Alpha2 = ElCLib::Parameter(Hypr, P2);
  occ::handle<Geom2d_Hyperbola> H      = new Geom2d_Hyperbola(Hypr);
  TheArc                               = new Geom2d_TrimmedCurve(H, Alpha1, Alpha2, Sense);
  TheError                             = gce_Done;
}

GCE2d_MakeArcOfHyperbola::GCE2d_MakeArcOfHyperbola(const gp_Hypr2d& Hypr,
                                                   const gp_Pnt2d&  P,
                                                   const double     Alpha,
                                                   const bool       Sense)
{
  double                        Alphafirst = ElCLib::Parameter(Hypr, P);
  occ::handle<Geom2d_Hyperbola> H          = new Geom2d_Hyperbola(Hypr);
  TheArc                                   = new Geom2d_TrimmedCurve(H, Alphafirst, Alpha, Sense);
  TheError                                 = gce_Done;
}

GCE2d_MakeArcOfHyperbola::GCE2d_MakeArcOfHyperbola(const gp_Hypr2d& Hypr,
                                                   const double     Alpha1,
                                                   const double     Alpha2,
                                                   const bool       Sense)
{
  occ::handle<Geom2d_Hyperbola> H = new Geom2d_Hyperbola(Hypr);
  TheArc                          = new Geom2d_TrimmedCurve(H, Alpha1, Alpha2, Sense);
  TheError                        = gce_Done;
}

const occ::handle<Geom2d_TrimmedCurve>& GCE2d_MakeArcOfHyperbola::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GCE2d_MakeArcOfHyperbola::Value() - no result");
  return TheArc;
}

#include <GC_MakeHyperbola.hpp>
#include <gce_MakeHypr.hpp>
#include <Geom_Hyperbola.hpp>
#include <gp_Ax2.hpp>
#include <gp_Hypr.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeHyperbola::GC_MakeHyperbola(const gp_Hypr& H)
{
  TheError     = gce_Done;
  TheHyperbola = new Geom_Hyperbola(H);
}

GC_MakeHyperbola::GC_MakeHyperbola(const gp_Ax2& A2,
                                   const double  MajorRadius,
                                   const double  MinorRadius)
{
  if (MajorRadius < 0. || MinorRadius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    TheError     = gce_Done;
    TheHyperbola = new Geom_Hyperbola(gp_Hypr(A2, MajorRadius, MinorRadius));
  }
}

GC_MakeHyperbola::GC_MakeHyperbola(const gp_Pnt& S1, const gp_Pnt& S2, const gp_Pnt& Center)
{
  gce_MakeHypr H = gce_MakeHypr(S1, S2, Center);
  TheError       = H.Status();
  if (TheError == gce_Done)
  {
    TheHyperbola = new Geom_Hyperbola(H.Value());
  }
}

const occ::handle<Geom_Hyperbola>& GC_MakeHyperbola::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeHyperbola::Value() - no result");
  return TheHyperbola;
}

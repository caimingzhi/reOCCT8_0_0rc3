#include <GCE2d_MakeHyperbola.hpp>
#include <gce_MakeHypr2d.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>

GCE2d_MakeHyperbola::GCE2d_MakeHyperbola(const gp_Hypr2d& H)
{
  TheError     = gce_Done;
  TheHyperbola = new Geom2d_Hyperbola(H);
}

GCE2d_MakeHyperbola::GCE2d_MakeHyperbola(const gp_Ax2d& MajorAxis,
                                         const double   MajorRadius,
                                         const double   MinorRadius,
                                         const bool     Sense)
{
  gce_MakeHypr2d H = gce_MakeHypr2d(MajorAxis, MajorRadius, MinorRadius, Sense);
  TheError         = H.Status();
  if (TheError == gce_Done)
  {
    TheHyperbola = new Geom2d_Hyperbola(H.Value());
  }
}

GCE2d_MakeHyperbola::GCE2d_MakeHyperbola(const gp_Ax22d& Axis,
                                         const double    MajorRadius,
                                         const double    MinorRadius)
{
  gce_MakeHypr2d H = gce_MakeHypr2d(Axis, MajorRadius, MinorRadius);
  TheError         = H.Status();
  if (TheError == gce_Done)
  {
    TheHyperbola = new Geom2d_Hyperbola(H.Value());
  }
}

GCE2d_MakeHyperbola::GCE2d_MakeHyperbola(const gp_Pnt2d& S1,
                                         const gp_Pnt2d& S2,
                                         const gp_Pnt2d& Center)
{
  gce_MakeHypr2d H = gce_MakeHypr2d(S1, S2, Center);
  TheError         = H.Status();
  if (TheError == gce_Done)
  {
    TheHyperbola = new Geom2d_Hyperbola(H.Value());
  }
}

const occ::handle<Geom2d_Hyperbola>& GCE2d_MakeHyperbola::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GCE2d_MakeHyperbola::Value() - no result");
  return TheHyperbola;
}

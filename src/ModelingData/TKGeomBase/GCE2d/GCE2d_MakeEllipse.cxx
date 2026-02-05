#include <GCE2d_MakeEllipse.hpp>
#include <gce_MakeElips2d.hpp>
#include <Geom2d_Ellipse.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>

GCE2d_MakeEllipse::GCE2d_MakeEllipse(const gp_Elips2d& E)
{
  TheError   = gce_Done;
  TheEllipse = new Geom2d_Ellipse(E);
}

GCE2d_MakeEllipse::GCE2d_MakeEllipse(const gp_Ax22d& Axis,
                                     const double    MajorRadius,
                                     const double    MinorRadius)
{
  gce_MakeElips2d E = gce_MakeElips2d(Axis, MajorRadius, MinorRadius);
  TheError          = E.Status();
  if (TheError == gce_Done)
  {
    TheEllipse = new Geom2d_Ellipse(E.Value());
  }
}

GCE2d_MakeEllipse::GCE2d_MakeEllipse(const gp_Ax2d& MajorAxis,
                                     const double   MajorRadius,
                                     const double   MinorRadius,
                                     const bool     Sense)
{
  gce_MakeElips2d E = gce_MakeElips2d(MajorAxis, MajorRadius, MinorRadius, Sense);
  TheError          = E.Status();
  if (TheError == gce_Done)
  {
    TheEllipse = new Geom2d_Ellipse(E.Value());
  }
}

GCE2d_MakeEllipse::GCE2d_MakeEllipse(const gp_Pnt2d& S1, const gp_Pnt2d& S2, const gp_Pnt2d& Center)
{
  gce_MakeElips2d E = gce_MakeElips2d(S1, S2, Center);
  TheError          = E.Status();
  if (TheError == gce_Done)
  {
    TheEllipse = new Geom2d_Ellipse(E.Value());
  }
}

const occ::handle<Geom2d_Ellipse>& GCE2d_MakeEllipse::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GCE2d_MakeEllipse::Value() - no result");
  return TheEllipse;
}

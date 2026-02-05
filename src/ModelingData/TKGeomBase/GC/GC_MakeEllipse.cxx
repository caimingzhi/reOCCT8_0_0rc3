#include <GC_MakeEllipse.hpp>
#include <gce_MakeElips.hpp>
#include <Geom_Ellipse.hpp>
#include <gp_Ax2.hpp>
#include <gp_Elips.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeEllipse::GC_MakeEllipse(const gp_Elips& E)
{
  TheError   = gce_Done;
  TheEllipse = new Geom_Ellipse(E);
}

GC_MakeEllipse::GC_MakeEllipse(const gp_Ax2& A2, const double MajorRadius, const double MinorRadius)
{
  if (MinorRadius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else if (MajorRadius < MinorRadius)
  {
    TheError = gce_InvertAxis;
  }
  else
  {
    TheError   = gce_Done;
    TheEllipse = new Geom_Ellipse(gp_Elips(A2, MajorRadius, MinorRadius));
  }
}

GC_MakeEllipse::GC_MakeEllipse(const gp_Pnt& S1, const gp_Pnt& S2, const gp_Pnt& Center)
{
  gce_MakeElips E = gce_MakeElips(S1, S2, Center);
  TheError        = E.Status();
  if (TheError == gce_Done)
  {
    TheEllipse = new Geom_Ellipse(E.Value());
  }
}

const occ::handle<Geom_Ellipse>& GC_MakeEllipse::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeEllipse::Value() - no result");
  return TheEllipse;
}

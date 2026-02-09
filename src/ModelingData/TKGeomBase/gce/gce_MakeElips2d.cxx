#include <gce_MakeElips2d.hpp>
#include <gp.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>

gce_MakeElips2d::gce_MakeElips2d(const gp_Pnt2d& S1, const gp_Pnt2d& S2, const gp_Pnt2d& Center)
{
  double   D1 = S1.Distance(Center);
  gp_Dir2d XAxis(gp_XY(S1.XY() - Center.XY()));
  gp_Dir2d YAxis(gp_XY(S2.XY() - Center.XY()));
  double   D2 = gp_Lin2d(Center, XAxis).Distance(S2);
  if (D1 < D2)
  {
    TheError = gce_InvertAxis;
  }
  else if (D2 < gp::Resolution())
  {
    TheError = gce_NullAxis;
  }
  else
  {
    TheElips2d = gp_Elips2d(gp_Ax22d(Center, XAxis, YAxis), D1, D2);
    TheError   = gce_Done;
  }
}

gce_MakeElips2d::gce_MakeElips2d(const gp_Ax2d& MajorAxis,
                                 const double   MajorRadius,
                                 const double   MinorRadius,
                                 const bool     Sense)
{
  if (MajorRadius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else if (MajorRadius < MinorRadius)
  {
    TheError = gce_InvertRadius;
  }
  else
  {
    TheElips2d = gp_Elips2d(MajorAxis, MajorRadius, MinorRadius, Sense);
    TheError   = gce_Done;
  }
}

gce_MakeElips2d::gce_MakeElips2d(const gp_Ax22d& A,
                                 const double    MajorRadius,
                                 const double    MinorRadius)
{
  if (MajorRadius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else if (MajorRadius < MinorRadius)
  {
    TheError = gce_InvertRadius;
  }
  else
  {
    TheElips2d = gp_Elips2d(A, MajorRadius, MinorRadius);
    TheError   = gce_Done;
  }
}

const gp_Elips2d& gce_MakeElips2d::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeElips2d::Value() - no result");
  return TheElips2d;
}

const gp_Elips2d& gce_MakeElips2d::Operator() const
{
  return Value();
}

gce_MakeElips2d::operator gp_Elips2d() const
{
  return Value();
}

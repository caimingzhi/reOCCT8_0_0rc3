#include <gce_MakeHypr2d.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>

gce_MakeHypr2d::gce_MakeHypr2d(const gp_Pnt2d& S1, const gp_Pnt2d& S2, const gp_Pnt2d& Center)
{
  gp_Dir2d XAxis(gp_XY(S1.XY() - Center.XY()));
  gp_Dir2d YAxis(gp_XY(S2.XY() - Center.XY()));
  gp_Ax22d Axis(Center, XAxis, YAxis);
  gp_Lin2d L(Center, XAxis);
  double   D1 = S1.Distance(Center);
  double   D2 = L.Distance(S2);
  if (D1 >= D2)
  {
    TheHypr2d = gp_Hypr2d(Axis, D1, D2);
    TheError  = gce_Done;
  }
  else
  {
    TheError = gce_InvertAxis;
  }
}

gce_MakeHypr2d::gce_MakeHypr2d(const gp_Ax2d& MajorAxis,
                               const double   MajorRadius,
                               const double   MinorRadius,
                               const bool     Sense)
{
  if (MajorRadius < 0.0 || MinorRadius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    TheHypr2d = gp_Hypr2d(MajorAxis, MajorRadius, MinorRadius, Sense);
    TheError  = gce_Done;
  }
}

gce_MakeHypr2d::gce_MakeHypr2d(const gp_Ax22d& A,
                               const double    MajorRadius,
                               const double    MinorRadius)
{
  if (MajorRadius < 0.0 || MinorRadius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    TheHypr2d = gp_Hypr2d(A, MajorRadius, MinorRadius);
    TheError  = gce_Done;
  }
}

const gp_Hypr2d& gce_MakeHypr2d::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeHypr2d::Value() - no result");
  return TheHypr2d;
}

const gp_Hypr2d& gce_MakeHypr2d::Operator() const
{
  return Value();
}

gce_MakeHypr2d::operator gp_Hypr2d() const
{
  return Value();
}

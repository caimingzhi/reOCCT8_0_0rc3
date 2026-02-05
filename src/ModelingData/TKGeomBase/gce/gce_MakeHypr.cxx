#include <gce_MakeHypr.hpp>
#include <gp_Ax2.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

//=========================================================================
//   Creation d une Hyperbole 3d de gp de centre <Center> et de sommets   +
//   <S1> et <S2>.                                                        +
//   <CenterS1> donne le grand axe .                                      +
//   <S1> donne le grand rayon et <S2> le petit rayon.                    +
//=========================================================================
gce_MakeHypr::gce_MakeHypr(const gp_Pnt& S1, const gp_Pnt& S2, const gp_Pnt& Center)
{
  gp_Dir XAxis(gp_XYZ(S1.XYZ() - Center.XYZ()));
  gp_Lin L(Center, XAxis);
  double D = S1.Distance(Center);
  double d = L.Distance(S2);
  if (d > D)
  {
    TheError = gce_InvertAxis;
  }
  else
  {
    gp_Dir Norm(XAxis.Crossed(gp_Dir(gp_XYZ(S2.XYZ() - Center.XYZ()))));
    TheHypr  = gp_Hypr(gp_Ax2(Center, Norm, XAxis), D, d);
    TheError = gce_Done;
  }
}

gce_MakeHypr::gce_MakeHypr(const gp_Ax2& A2, const double MajorRadius, const double MinorRadius)
{
  if (MajorRadius < MinorRadius)
  {
    TheError = gce_InvertRadius;
  }
  else if (MajorRadius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    TheHypr  = gp_Hypr(A2, MajorRadius, MinorRadius);
    TheError = gce_Done;
  }
}

const gp_Hypr& gce_MakeHypr::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeHypr::Value() - no result");
  return TheHypr;
}

const gp_Hypr& gce_MakeHypr::Operator() const
{
  return Value();
}

gce_MakeHypr::operator gp_Hypr() const
{
  return Value();
}

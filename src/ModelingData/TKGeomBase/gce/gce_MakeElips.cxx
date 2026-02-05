#include <gce_MakeElips.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Elips.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

//=========================================================================
//   Creation d une Ellipse 3d de gp a partir de son Ax2 et de son        +
//   grand rayon <MajorRadius> et son petit rayon <MinorRadius>.          +
//=========================================================================
gce_MakeElips::gce_MakeElips(const gp_Ax2& A2, const double MajorRadius, const double MinorRadius)
{
  if (MajorRadius < MinorRadius)
  {
    TheError = gce_InvertRadius;
  }
  else if (MinorRadius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    TheElips = gp_Elips(A2, MajorRadius, MinorRadius);
    TheError = gce_Done;
  }
}

//=========================================================================
//   Creation d une Ellipse 3d de gp de centre <Center> et de sommets     +
//   <S1> et <S2>.                                                        +
//   <S1> donne le grand rayon et <S2> le petit rayon.                    +
//=========================================================================

gce_MakeElips::gce_MakeElips(const gp_Pnt& S1, const gp_Pnt& S2, const gp_Pnt& Center)
{
  double D1 = S1.Distance(Center);
  if (D1 < gp::Resolution())
  {
    TheError = gce_NullAxis;
  }
  else
  {
    gp_Dir XAxis(gp_XYZ(S1.XYZ() - Center.XYZ()));
    double D2 = gp_Lin(Center, XAxis).Distance(S2);
    if (D1 < D2 || D2 < gp::Resolution())
    {
      TheError = gce_InvertAxis;
    }
    else
    {
      gp_Dir Norm(XAxis.Crossed(gp_Dir(gp_XYZ(S2.XYZ() - Center.XYZ()))));
      TheElips = gp_Elips(gp_Ax2(Center, Norm, XAxis), D1, D2);
      TheError = gce_Done;
    }
  }
}

const gp_Elips& gce_MakeElips::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeElips::Value() - no result");
  return TheElips;
}

const gp_Elips& gce_MakeElips::Operator() const
{
  return Value();
}

gce_MakeElips::operator gp_Elips() const
{
  return Value();
}

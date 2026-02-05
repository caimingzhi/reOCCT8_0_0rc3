#include <gce_MakeParab2d.hpp>
#include <gp.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>

gce_MakeParab2d::gce_MakeParab2d(const gp_Ax22d& A, const double Focal)
{
  if (Focal < 0.0)
  {
    TheError = gce_NullFocusLength;
  }
  else
  {
    TheParab2d = gp_Parab2d(A, Focal);
    TheError   = gce_Done;
  }
}

gce_MakeParab2d::gce_MakeParab2d(const gp_Ax2d& MirrorAxis, const double Focal, const bool Sense)
{
  if (Focal < 0.0)
  {
    TheError = gce_NullFocusLength;
  }
  else
  {
    TheParab2d = gp_Parab2d(MirrorAxis, Focal, Sense);
    TheError   = gce_Done;
  }
}

gce_MakeParab2d::gce_MakeParab2d(const gp_Ax2d& D, const gp_Pnt2d& F, const bool Sense)
{
  TheParab2d = gp_Parab2d(D, F, Sense);
  TheError   = gce_Done;
}

//=========================================================================
//   Creation d une Parabole 2d de gp de centre <Center> et de sommet     +
//   <S1> .                                                               +
//   <CenterS1> donne le grand axe .                                      +
//   <S1> donne la focale.                                                +
//=========================================================================

gce_MakeParab2d::gce_MakeParab2d(const gp_Pnt2d& S, const gp_Pnt2d& Center, const bool Sense)
{
  if (S.Distance(Center) >= gp::Resolution())
  {
    gp_Dir2d XAxis(gp_XY(S.XY() - Center.XY()));
    TheParab2d = gp_Parab2d(gp_Ax2d(Center, XAxis), S.Distance(Center), Sense);
    TheError   = gce_Done;
  }
  else
  {
    TheError = gce_NullAxis;
  }
}

const gp_Parab2d& gce_MakeParab2d::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeParab2d::Value() - no result");
  return TheParab2d;
}

const gp_Parab2d& gce_MakeParab2d::Operator() const
{
  return Value();
}

gce_MakeParab2d::operator gp_Parab2d() const
{
  return Value();
}

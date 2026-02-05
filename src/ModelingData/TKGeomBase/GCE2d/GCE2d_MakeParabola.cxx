#include <GCE2d_MakeParabola.hpp>
#include <gce_MakeParab2d.hpp>
#include <Geom2d_Parabola.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>

GCE2d_MakeParabola::GCE2d_MakeParabola(const gp_Parab2d& Prb)
{
  TheError    = gce_Done;
  TheParabola = new Geom2d_Parabola(Prb);
}

GCE2d_MakeParabola::GCE2d_MakeParabola(const gp_Ax2d& MirrorAxis,
                                       const double   Focal,
                                       const bool     Sense)
{
  if (Focal < 0.0)
  {
    TheError = gce_NullFocusLength;
  }
  else
  {
    TheError    = gce_Done;
    TheParabola = new Geom2d_Parabola(MirrorAxis, Focal, Sense);
  }
}

GCE2d_MakeParabola::GCE2d_MakeParabola(const gp_Ax22d& Axis, const double Focal)
{
  if (Focal < 0.0)
  {
    TheError = gce_NullFocusLength;
  }
  else
  {
    TheError    = gce_Done;
    TheParabola = new Geom2d_Parabola(Axis, Focal);
  }
}

GCE2d_MakeParabola::GCE2d_MakeParabola(const gp_Ax2d& D, const gp_Pnt2d& F, const bool Sense)
{
  TheError = gce_Done;
  gp_Parab2d para(D, F, Sense);
  TheParabola = new Geom2d_Parabola(para);
}

GCE2d_MakeParabola::GCE2d_MakeParabola(const gp_Pnt2d& S1, const gp_Pnt2d& O)
{
  gce_MakeParab2d P = gce_MakeParab2d(S1, O);
  TheError          = P.Status();
  if (TheError == gce_Done)
  {
    TheParabola = new Geom2d_Parabola(P.Value());
  }
}

const occ::handle<Geom2d_Parabola>& GCE2d_MakeParabola::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GCE2d_MakeParabola::Value() - no result");
  return TheParabola;
}

#include <GC_MakeConicalSurface.hpp>
#include <gce_MakeCone.hpp>
#include <Geom_ConicalSurface.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Cone.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <Standard_NotImplemented.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeConicalSurface::GC_MakeConicalSurface(const gp_Ax2& A2,
                                             const double  Ang,
                                             const double  Radius)
{
  if (Radius < 0.)
  {
    TheError = gce_NegativeRadius;
  }
  else if (Ang <= gp::Resolution() || Ang >= M_PI / 2. - gp::Resolution())
  {
    TheError = gce_BadAngle;
  }
  else
  {
    TheError = gce_Done;
    TheCone  = new Geom_ConicalSurface(A2, Ang, Radius);
  }
}

GC_MakeConicalSurface::GC_MakeConicalSurface(const gp_Cone& C)
{
  TheError = gce_Done;
  TheCone  = new Geom_ConicalSurface(C);
}

GC_MakeConicalSurface::GC_MakeConicalSurface(const gp_Pnt& P1,
                                             const gp_Pnt& P2,
                                             const gp_Pnt& P3,
                                             const gp_Pnt& P4)
{
  gce_MakeCone C = gce_MakeCone(P1, P2, P3, P4);
  TheError       = C.Status();
  if (TheError == gce_Done)
  {
    TheCone = new Geom_ConicalSurface(C.Value());
  }
}

GC_MakeConicalSurface::GC_MakeConicalSurface(const gp_Pnt& P1,
                                             const gp_Pnt& P2,
                                             const double  R1,
                                             const double  R2)
{
  gce_MakeCone C = gce_MakeCone(P1, P2, R1, R2);
  TheError       = C.Status();
  if (TheError == gce_Done)
  {
    TheCone = new Geom_ConicalSurface(C);
  }
}

const occ::handle<Geom_ConicalSurface>& GC_MakeConicalSurface::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeConicalSurface::Value() - no result");
  return TheCone;
}

#include <GC_MakeCylindricalSurface.hpp>
#include <GC_MakeTrimmedCylinder.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <gp_Ax1.hpp>
#include <gp_Circ.hpp>
#include <gp_Pnt.hpp>
#include <Standard_NotImplemented.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeTrimmedCylinder::GC_MakeTrimmedCylinder(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3)
{
  GC_MakeCylindricalSurface Cyl(P1, P2, P3);
  TheError = Cyl.Status();
  if (TheError == gce_Done)
  {
    TheCyl = new Geom_RectangularTrimmedSurface(Cyl.Value(),
                                                0.,
                                                2. * M_PI,
                                                0.,
                                                P2.Distance(P1),
                                                true,
                                                true);
  }
}

GC_MakeTrimmedCylinder::GC_MakeTrimmedCylinder(const gp_Circ& Circ, const double Height)
{
  GC_MakeCylindricalSurface Cyl(Circ);
  TheError = Cyl.Status();
  if (TheError == gce_Done)
  {
    TheCyl = new Geom_RectangularTrimmedSurface(Cyl.Value(), 0., 2. * M_PI, 0., Height, true, true);
  }
}

GC_MakeTrimmedCylinder::GC_MakeTrimmedCylinder(const gp_Ax1& A1,
                                               const double  Radius,
                                               const double  Height)
{
  GC_MakeCylindricalSurface Cyl(A1, Radius);
  TheError = Cyl.Status();
  if (TheError == gce_Done)
  {
    TheCyl = new Geom_RectangularTrimmedSurface(Cyl.Value(), 0., 2. * M_PI, 0., Height, true, true);
  }
}

const occ::handle<Geom_RectangularTrimmedSurface>& GC_MakeTrimmedCylinder::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeTrimmedCylinder::Value() - no result");
  return TheCyl;
}

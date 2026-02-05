#include <GC_MakeCylindricalSurface.hpp>
#include <gce_MakeCylinder.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Cylinder& C)
{
  TheError    = gce_Done;
  TheCylinder = new Geom_CylindricalSurface(C);
}

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Ax2& A2, const double Radius)
{
  if (Radius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    TheError    = gce_Done;
    TheCylinder = new Geom_CylindricalSurface(A2, Radius);
  }
}

//=========================================================================
//   Construction of a cylinder by axis <A1> et radius <Radius>.          +
//=========================================================================

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Ax1& A1, const double Radius)
{
  gce_MakeCylinder Cyl = gce_MakeCylinder(A1, Radius);
  TheError             = Cyl.Status();
  if (TheError == gce_Done)
  {
    TheCylinder = new Geom_CylindricalSurface(Cyl.Value());
  }
}

//=========================================================================
//   Construction of a cylinder by a circle <Cir>.                        +
//=========================================================================

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Circ& Circ)
{
  gp_Cylinder Cyl = gce_MakeCylinder(Circ);
  TheCylinder     = new Geom_CylindricalSurface(Cyl);
  TheError        = gce_Done;
}

//=========================================================================
//   Construction of a cylinder by tree points <P1>, <P2>, <P3>.          +
//   Two first points define the axis.                                    +
//   The third gives the radius.                                          +
//=========================================================================

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Pnt& P1,
                                                     const gp_Pnt& P2,
                                                     const gp_Pnt& P3)
{
  gce_MakeCylinder Cyl = gce_MakeCylinder(P1, P2, P3);
  TheError             = Cyl.Status();
  if (TheError == gce_Done)
  {
    TheCylinder = new Geom_CylindricalSurface(Cyl.Value());
  }
}

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Cylinder& Cyl, const double Dist)
{
  TheError    = gce_Done;
  double R    = std::abs(Cyl.Radius() - Dist);
  TheCylinder = new Geom_CylindricalSurface(Cyl);
  TheCylinder->SetRadius(R);
}

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Cylinder& Cyl, const gp_Pnt& Point)
{
  TheError = gce_Done;
  gp_Cylinder C(Cyl);
  gp_Lin      L(C.Axis());
  double      R = L.Distance(Point);
  C.SetRadius(R);
  TheCylinder = new Geom_CylindricalSurface(C);
}

const occ::handle<Geom_CylindricalSurface>& GC_MakeCylindricalSurface::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeCylindricalSurface::Value() - no result");
  return TheCylinder;
}

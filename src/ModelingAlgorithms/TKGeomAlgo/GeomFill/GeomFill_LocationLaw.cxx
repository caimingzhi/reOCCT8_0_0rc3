#include <GeomFill_LocationLaw.hpp>

#include <Adaptor3d_Curve.hpp>
#include <gp_Mat.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_LocationLaw, Standard_Transient)

bool GeomFill_LocationLaw::D1(const double,
                              gp_Mat&,
                              gp_Vec&,
                              gp_Mat&,
                              gp_Vec&,
                              NCollection_Array1<gp_Pnt2d>&,
                              NCollection_Array1<gp_Vec2d>&)
{
  throw Standard_NotImplemented("GeomFill_LocationLaw::D1");
}

bool GeomFill_LocationLaw::D2(const double,
                              gp_Mat&,
                              gp_Vec&,
                              gp_Mat&,
                              gp_Vec&,
                              gp_Mat&,
                              gp_Vec&,
                              NCollection_Array1<gp_Pnt2d>&,
                              NCollection_Array1<gp_Vec2d>&,
                              NCollection_Array1<gp_Vec2d>&)
{
  throw Standard_NotImplemented("GeomFill_LocationLaw::D2");
}

int GeomFill_LocationLaw::Nb2dCurves() const
{
  int N = TraceNumber();
  if (HasFirstRestriction())
    N++;
  if (HasLastRestriction())
    N++;

  return N;
}

bool GeomFill_LocationLaw::HasFirstRestriction() const
{
  return false;
}

bool GeomFill_LocationLaw::HasLastRestriction() const
{
  return false;
}

int GeomFill_LocationLaw::TraceNumber() const
{
  return 0;
}

GeomFill_PipeError GeomFill_LocationLaw::ErrorStatus() const
{
  return GeomFill_PipeOk;
}

void GeomFill_LocationLaw::Resolution(const int, const double, double&, double&) const
{
  throw Standard_NotImplemented("GeomFill_LocationLaw::Resolution");
}

void GeomFill_LocationLaw::SetTolerance(const double, const double) {}

bool GeomFill_LocationLaw::IsTranslation(double&) const
{
  return false;
}

bool GeomFill_LocationLaw::IsRotation(double&) const
{
  return false;
}

void GeomFill_LocationLaw::Rotation(gp_Pnt&) const
{
  throw Standard_NotImplemented("GeomFill_SectionLaw::Rotation");
}

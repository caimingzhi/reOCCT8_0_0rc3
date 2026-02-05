#include <Geom_BSplineSurface.hpp>
#include <Geom_Curve.hpp>
#include <GeomFill_SectionLaw.hpp>
#include <gp_Pnt.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_SectionLaw, Standard_Transient)

bool GeomFill_SectionLaw::D1(const double,
                             NCollection_Array1<gp_Pnt>&,
                             NCollection_Array1<gp_Vec>&,
                             NCollection_Array1<double>&,
                             NCollection_Array1<double>&)
{
  throw Standard_NotImplemented("GeomFill_SectionLaw::D1");
}

bool GeomFill_SectionLaw::D2(const double,
                             NCollection_Array1<gp_Pnt>&,
                             NCollection_Array1<gp_Vec>&,
                             NCollection_Array1<gp_Vec>&,
                             NCollection_Array1<double>&,
                             NCollection_Array1<double>&,
                             NCollection_Array1<double>&)
{
  throw Standard_NotImplemented("GeomFill_SectionLaw::D2");
}

occ::handle<Geom_BSplineSurface> GeomFill_SectionLaw::BSplineSurface() const
{
  occ::handle<Geom_BSplineSurface> BS;
  BS.Nullify();
  return BS;
}

void GeomFill_SectionLaw::SetTolerance(const double, const double)
{
  // Ne fait Rien
}

gp_Pnt GeomFill_SectionLaw::BarycentreOfSurf() const
{

  throw Standard_NotImplemented("GeomFill_SectionLaw::BarycentreOfSurf");
}

void GeomFill_SectionLaw::GetMinimalWeight(NCollection_Array1<double>&) const
{
  throw Standard_NotImplemented("GeomFill_SectionLaw::GetMinimalWeight");
}

bool GeomFill_SectionLaw::IsConstant(double& Error) const
{
  Error = 0.;
  return false;
}

occ::handle<Geom_Curve> GeomFill_SectionLaw::ConstantSection() const
{
  occ::handle<Geom_Curve> C;
  throw Standard_DomainError("GeomFill_SectionLaw::ConstantSection");
}

bool GeomFill_SectionLaw::IsConicalLaw(double& Error) const
{
  Error = 0.;
  return false;
}

occ::handle<Geom_Curve> GeomFill_SectionLaw::CirclSection(const double) const
{
  occ::handle<Geom_Curve> C;
  throw Standard_DomainError("GeomFill_SectionLaw::CirclSection");
}

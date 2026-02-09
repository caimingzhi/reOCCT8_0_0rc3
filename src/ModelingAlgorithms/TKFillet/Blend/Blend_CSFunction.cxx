

#include <Blend_CSFunction.hpp>
#include <Blend_Point.hpp>
#include <gp_Pnt.hpp>
#include <Standard_NotImplemented.hpp>

int Blend_CSFunction::NbVariables() const
{
  return 3;
}

const gp_Pnt& Blend_CSFunction::Pnt1() const
{
  return PointOnC();
}

const gp_Pnt& Blend_CSFunction::Pnt2() const
{
  return PointOnS();
}

bool Blend_CSFunction::Section(const Blend_Point&,
                               NCollection_Array1<gp_Pnt>&,
                               NCollection_Array1<gp_Vec>&,
                               NCollection_Array1<gp_Vec>&,
                               NCollection_Array1<gp_Pnt2d>&,
                               NCollection_Array1<gp_Vec2d>&,
                               NCollection_Array1<gp_Vec2d>&,
                               NCollection_Array1<double>&,
                               NCollection_Array1<double>&,
                               NCollection_Array1<double>&)
{
  return false;
}

double Blend_CSFunction::GetMinimalDistance() const
{
  throw Standard_NotImplemented("Blend_CSFunction::GetMinimalDistance");
}

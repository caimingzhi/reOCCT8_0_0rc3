

#include <Blend_Function.hpp>
#include <Blend_Point.hpp>
#include <gp_Pnt.hpp>

int Blend_Function::NbVariables() const
{
  return 4;
}

const gp_Pnt& Blend_Function::Pnt1() const
{
  return PointOnS1();
}

const gp_Pnt& Blend_Function::Pnt2() const
{
  return PointOnS2();
}

bool Blend_Function::TwistOnS1() const
{
  return false;
}

bool Blend_Function::TwistOnS2() const
{
  return false;
}

bool Blend_Function::Section(const Blend_Point&,
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

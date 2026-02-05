#include <GccInt_BParab.hpp>
#include <gp_Parab2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GccInt_BParab, GccInt_Bisec)

GccInt_BParab::GccInt_BParab(const gp_Parab2d& Parab)
{
  par = gp_Parab2d(Parab);
}

GccInt_IType GccInt_BParab::ArcType() const
{
  return GccInt_Par;
}

gp_Parab2d GccInt_BParab::Parabola() const
{
  return par;
}

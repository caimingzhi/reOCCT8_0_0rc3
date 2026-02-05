#include <GccInt_BCirc.hpp>
#include <gp_Circ2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GccInt_BCirc, GccInt_Bisec)

GccInt_BCirc::GccInt_BCirc(const gp_Circ2d& Circ)
{
  cir = gp_Circ2d(Circ);
}

GccInt_IType GccInt_BCirc::ArcType() const
{
  return GccInt_Cir;
}

gp_Circ2d GccInt_BCirc::Circle() const
{
  return cir;
}

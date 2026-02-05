#include <GccInt_BElips.hpp>
#include <gp_Elips2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GccInt_BElips, GccInt_Bisec)

GccInt_BElips::GccInt_BElips(const gp_Elips2d& Ellipse)
{
  eli = gp_Elips2d(Ellipse);
}

GccInt_IType GccInt_BElips::ArcType() const
{
  return GccInt_Ell;
}

gp_Elips2d GccInt_BElips::Ellipse() const
{
  return eli;
}

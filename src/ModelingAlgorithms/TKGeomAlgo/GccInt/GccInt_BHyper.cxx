#include <GccInt_BHyper.hpp>
#include <gp_Hypr2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GccInt_BHyper, GccInt_Bisec)

GccInt_BHyper::GccInt_BHyper(const gp_Hypr2d& Hyper)
{
  hyp = gp_Hypr2d(Hyper);
}

GccInt_IType GccInt_BHyper::ArcType() const
{
  return GccInt_Hpr;
}

gp_Hypr2d GccInt_BHyper::Hyperbola() const
{
  return hyp;
}

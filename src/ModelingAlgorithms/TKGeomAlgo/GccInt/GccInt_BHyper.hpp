#pragma once

#include <Standard.hpp>

#include <gp_Hypr2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

class GccInt_BHyper : public GccInt_Bisec
{

public:
  Standard_EXPORT GccInt_BHyper(const gp_Hypr2d& Hyper);

  Standard_EXPORT gp_Hypr2d Hyperbola() const override;

  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BHyper, GccInt_Bisec)

private:
  gp_Hypr2d hyp;
};

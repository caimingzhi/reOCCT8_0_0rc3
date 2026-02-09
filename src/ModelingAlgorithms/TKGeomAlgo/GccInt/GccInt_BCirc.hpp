#pragma once

#include <Standard.hpp>

#include <gp_Circ2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

class GccInt_BCirc : public GccInt_Bisec
{

public:
  Standard_EXPORT GccInt_BCirc(const gp_Circ2d& Circ);

  Standard_EXPORT gp_Circ2d Circle() const override;

  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BCirc, GccInt_Bisec)

private:
  gp_Circ2d cir;
};

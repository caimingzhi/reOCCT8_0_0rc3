#pragma once

#include <Standard.hpp>

#include <gp_Parab2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

class GccInt_BParab : public GccInt_Bisec
{

public:
  Standard_EXPORT GccInt_BParab(const gp_Parab2d& Parab);

  Standard_EXPORT gp_Parab2d Parabola() const override;

  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BParab, GccInt_Bisec)

private:
  gp_Parab2d par;
};

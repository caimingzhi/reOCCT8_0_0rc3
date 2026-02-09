#pragma once

#include <Standard.hpp>

#include <gp_Elips2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

class GccInt_BElips : public GccInt_Bisec
{

public:
  Standard_EXPORT GccInt_BElips(const gp_Elips2d& Ellipse);

  Standard_EXPORT gp_Elips2d Ellipse() const override;

  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BElips, GccInt_Bisec)

private:
  gp_Elips2d eli;
};

#pragma once

#include <Standard.hpp>

#include <gp_Lin2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

class GccInt_BLine : public GccInt_Bisec
{

public:
  Standard_EXPORT GccInt_BLine(const gp_Lin2d& Line);

  Standard_EXPORT gp_Lin2d Line() const override;

  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BLine, GccInt_Bisec)

private:
  gp_Lin2d lin;
};

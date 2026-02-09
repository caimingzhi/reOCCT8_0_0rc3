#pragma once

#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <GccInt_Bisec.hpp>
#include <GccInt_IType.hpp>

class GccInt_BPoint : public GccInt_Bisec
{

public:
  Standard_EXPORT GccInt_BPoint(const gp_Pnt2d& Point);

  Standard_EXPORT gp_Pnt2d Point() const override;

  Standard_EXPORT GccInt_IType ArcType() const override;

  DEFINE_STANDARD_RTTIEXT(GccInt_BPoint, GccInt_Bisec)

private:
  gp_Pnt2d pnt;
};

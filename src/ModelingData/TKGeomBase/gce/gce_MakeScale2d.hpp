#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf2d.hpp>
class gp_Pnt2d;

class gce_MakeScale2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeScale2d(const gp_Pnt2d& Point, const double Scale);

  Standard_EXPORT const gp_Trsf2d& Value() const;

  Standard_EXPORT const gp_Trsf2d& Operator() const;
  Standard_EXPORT                  operator gp_Trsf2d() const;

private:
  gp_Trsf2d TheScale2d;
};

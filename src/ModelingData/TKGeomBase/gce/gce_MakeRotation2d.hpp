#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf2d.hpp>
class gp_Pnt2d;

class gce_MakeRotation2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeRotation2d(const gp_Pnt2d& Point, const double Angle);

  Standard_EXPORT const gp_Trsf2d& Value() const;

  Standard_EXPORT const gp_Trsf2d& Operator() const;
  Standard_EXPORT                  operator gp_Trsf2d() const;

private:
  gp_Trsf2d TheRotation2d;
};

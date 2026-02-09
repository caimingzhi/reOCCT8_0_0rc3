#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_XYZ.hpp>

class Plate_D2
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_D2(const gp_XYZ& duu, const gp_XYZ& duv, const gp_XYZ& dvv);

  Standard_EXPORT Plate_D2(const Plate_D2& ref);

  friend class Plate_GtoCConstraint;
  friend class Plate_FreeGtoCConstraint;

private:
  gp_XYZ Duu;
  gp_XYZ Duv;
  gp_XYZ Dvv;
};

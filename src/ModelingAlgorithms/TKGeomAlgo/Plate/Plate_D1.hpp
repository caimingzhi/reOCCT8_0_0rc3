#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_XYZ.hpp>

class Plate_D1
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_D1(const gp_XYZ& du, const gp_XYZ& dv);

  Standard_EXPORT Plate_D1(const Plate_D1& ref);

  const gp_XYZ& DU() const;

  const gp_XYZ& DV() const;

  friend class Plate_GtoCConstraint;
  friend class Plate_FreeGtoCConstraint;

private:
  gp_XYZ Du;
  gp_XYZ Dv;
};

inline const gp_XYZ& Plate_D1::DU() const
{
  return Du;
}

inline const gp_XYZ& Plate_D1::DV() const
{
  return Dv;
}

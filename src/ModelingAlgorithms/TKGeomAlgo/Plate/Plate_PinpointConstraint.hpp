#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_XYZ.hpp>
#include <gp_XY.hpp>

//! define a constraint on the Plate
class Plate_PinpointConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_PinpointConstraint();

  Standard_EXPORT Plate_PinpointConstraint(const gp_XY&  point2d,
                                           const gp_XYZ& ImposedValue,
                                           const int     iu = 0,
                                           const int     iv = 0);

  const gp_XY& Pnt2d() const;

  const int& Idu() const;

  const int& Idv() const;

  const gp_XYZ& Value() const;

private:
  gp_XYZ value;
  gp_XY  pnt2d;
  int    idu;
  int    idv;
};

inline const gp_XY& Plate_PinpointConstraint::Pnt2d() const
{
  return pnt2d;
}

inline const int& Plate_PinpointConstraint::Idu() const
{
  return idu;
}

inline const int& Plate_PinpointConstraint::Idv() const
{
  return idv;
}

inline const gp_XYZ& Plate_PinpointConstraint::Value() const
{
  return value;
}

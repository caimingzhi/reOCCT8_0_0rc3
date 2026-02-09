#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Plate_LinearScalarConstraint.hpp>
#include <Standard_Integer.hpp>
class gp_XY;
class gp_Lin;

class Plate_LineConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_LineConstraint(const gp_XY&  point2d,
                                       const gp_Lin& lin,
                                       const int     iu = 0,
                                       const int     iv = 0);

  const Plate_LinearScalarConstraint& LSC() const;

private:
  Plate_LinearScalarConstraint myLSC;
};

inline const Plate_LinearScalarConstraint& Plate_LineConstraint::LSC() const
{
  return myLSC;
}

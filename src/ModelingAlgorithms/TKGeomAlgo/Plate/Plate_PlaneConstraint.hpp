#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Plate_LinearScalarConstraint.hpp>
#include <Standard_Integer.hpp>
class gp_XY;
class gp_Pln;

//! constraint a point to belong to a Plane
class Plate_PlaneConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_PlaneConstraint(const gp_XY&  point2d,
                                        const gp_Pln& pln,
                                        const int     iu = 0,
                                        const int     iv = 0);

  const Plate_LinearScalarConstraint& LSC() const;

private:
  Plate_LinearScalarConstraint myLSC;
};

inline const Plate_LinearScalarConstraint& Plate_PlaneConstraint::LSC() const
{
  return myLSC;
}

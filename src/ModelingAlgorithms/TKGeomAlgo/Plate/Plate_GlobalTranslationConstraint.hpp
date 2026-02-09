#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Plate_LinearXYZConstraint.hpp>
#include <gp_XY.hpp>
#include <NCollection_Sequence.hpp>

class Plate_GlobalTranslationConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_GlobalTranslationConstraint(const NCollection_Sequence<gp_XY>& SOfXY);

  const Plate_LinearXYZConstraint& LXYZC() const;

private:
  Plate_LinearXYZConstraint myLXYZC;
};

inline const Plate_LinearXYZConstraint& Plate_GlobalTranslationConstraint::LXYZC() const
{
  return myLXYZC;
}

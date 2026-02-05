#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Plate_LinearXYZConstraint.hpp>
#include <Plate_PinpointConstraint.hpp>
#include <NCollection_Sequence.hpp>

//! define m PinPointConstraint driven by m unknown
class Plate_SampledCurveConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_SampledCurveConstraint(
    const NCollection_Sequence<Plate_PinpointConstraint>& SOPPC,
    const int                                             n);

  const Plate_LinearXYZConstraint& LXYZC() const;

private:
  Plate_LinearXYZConstraint myLXYZC;
};

inline const Plate_LinearXYZConstraint& Plate_SampledCurveConstraint::LXYZC() const
{
  return myLXYZC;
}

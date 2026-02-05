#pragma once

#include <Standard.hpp>

#include <gp_XYZ.hpp>
#include <NLPlate_HGPPConstraint.hpp>
#include <Standard_Integer.hpp>
class gp_XY;

//! define a PinPoint G0 Constraint used to load a Non Linear
//! Plate
class NLPlate_HPG0Constraint : public NLPlate_HGPPConstraint
{

public:
  Standard_EXPORT NLPlate_HPG0Constraint(const gp_XY& UV, const gp_XYZ& Value);

  Standard_EXPORT void SetUVFreeSliding(const bool UVFree) override;

  Standard_EXPORT void SetIncrementalLoadAllowed(const bool ILA) override;

  Standard_EXPORT bool UVFreeSliding() const override;

  Standard_EXPORT bool IncrementalLoadAllowed() const override;

  Standard_EXPORT int ActiveOrder() const override;

  Standard_EXPORT bool IsG0() const override;

  Standard_EXPORT const gp_XYZ& G0Target() const override;

  DEFINE_STANDARD_RTTIEXT(NLPlate_HPG0Constraint, NLPlate_HGPPConstraint)

private:
  gp_XYZ myXYZTarget;
  bool   UVIsFree;
  bool   IncrementalLoadingAllowed;
};

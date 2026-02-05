#pragma once

#include <Standard.hpp>

#include <Plate_D1.hpp>
#include <Standard_Integer.hpp>
#include <NLPlate_HGPPConstraint.hpp>
class gp_XY;

//! define a PinPoint (no G0) G1 Constraint used to load a Non
//! Linear Plate
class NLPlate_HPG1Constraint : public NLPlate_HGPPConstraint
{

public:
  Standard_EXPORT NLPlate_HPG1Constraint(const gp_XY& UV, const Plate_D1& D1T);

  Standard_EXPORT void SetIncrementalLoadAllowed(const bool ILA) override;

  Standard_EXPORT void SetOrientation(const int Orient = 0) override;

  Standard_EXPORT bool IncrementalLoadAllowed() const override;

  Standard_EXPORT int ActiveOrder() const override;

  Standard_EXPORT bool IsG0() const override;

  Standard_EXPORT int Orientation() override;

  Standard_EXPORT const Plate_D1& G1Target() const override;

  DEFINE_STANDARD_RTTIEXT(NLPlate_HPG1Constraint, NLPlate_HGPPConstraint)

private:
  bool     IncrementalLoadingAllowed;
  Plate_D1 myG1Target;
  int      myOrientation;
};

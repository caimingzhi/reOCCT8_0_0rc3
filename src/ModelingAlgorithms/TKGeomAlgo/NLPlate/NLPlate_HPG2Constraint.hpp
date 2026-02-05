#pragma once

#include <Standard.hpp>

#include <Plate_D2.hpp>
#include <NLPlate_HPG1Constraint.hpp>
#include <Standard_Integer.hpp>
class gp_XY;
class Plate_D1;

//! define a PinPoint (no G0) G2 Constraint used to load a Non
//! Linear Plate
class NLPlate_HPG2Constraint : public NLPlate_HPG1Constraint
{

public:
  Standard_EXPORT NLPlate_HPG2Constraint(const gp_XY& UV, const Plate_D1& D1T, const Plate_D2& D2T);

  Standard_EXPORT int ActiveOrder() const override;

  Standard_EXPORT const Plate_D2& G2Target() const override;

  DEFINE_STANDARD_RTTIEXT(NLPlate_HPG2Constraint, NLPlate_HPG1Constraint)

private:
  Plate_D2 myG2Target;
};

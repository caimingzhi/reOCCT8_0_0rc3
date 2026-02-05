#pragma once

#include <Standard.hpp>

#include <Plate_D3.hpp>
#include <NLPlate_HPG0G2Constraint.hpp>
#include <Standard_Integer.hpp>
class gp_XY;
class gp_XYZ;
class Plate_D1;
class Plate_D2;

//! define a PinPoint G0+G3 Constraint used to load a Non Linear
//! Plate
class NLPlate_HPG0G3Constraint : public NLPlate_HPG0G2Constraint
{

public:
  Standard_EXPORT NLPlate_HPG0G3Constraint(const gp_XY&    UV,
                                           const gp_XYZ&   Value,
                                           const Plate_D1& D1T,
                                           const Plate_D2& D2T,
                                           const Plate_D3& D3T);

  Standard_EXPORT int ActiveOrder() const override;

  Standard_EXPORT const Plate_D3& G3Target() const override;

  DEFINE_STANDARD_RTTIEXT(NLPlate_HPG0G3Constraint, NLPlate_HPG0G2Constraint)

private:
  Plate_D3 myG3Target;
};

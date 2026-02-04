#pragma once


#include <Standard.hpp>

#include <Plate_D1.hpp>
#include <Standard_Integer.hpp>
#include <NLPlate_HPG0Constraint.hpp>
class gp_XY;
class gp_XYZ;

//! define a PinPoint G0+G1 Constraint used to load a Non Linear
//! Plate
class NLPlate_HPG0G1Constraint : public NLPlate_HPG0Constraint
{

public:
  Standard_EXPORT NLPlate_HPG0G1Constraint(const gp_XY&    UV,
                                           const gp_XYZ&   Value,
                                           const Plate_D1& D1T);

  Standard_EXPORT void SetOrientation(const int Orient = 0) override;

  Standard_EXPORT int ActiveOrder() const override;

  Standard_EXPORT int Orientation() override;

  Standard_EXPORT const Plate_D1& G1Target() const override;

  DEFINE_STANDARD_RTTIEXT(NLPlate_HPG0G1Constraint, NLPlate_HPG0Constraint)

private:
  Plate_D1 myG1Target;
  int      myOrientation;
};


#include <NLPlate_HPG0G3Constraint.hpp>
#include <Plate_D1.hpp>
#include <Plate_D2.hpp>
#include <Plate_D3.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NLPlate_HPG0G3Constraint, NLPlate_HPG0G2Constraint)

NLPlate_HPG0G3Constraint::NLPlate_HPG0G3Constraint(const gp_XY&    UV,
                                                   const gp_XYZ&   Value,
                                                   const Plate_D1& D1T,
                                                   const Plate_D2& D2T,
                                                   const Plate_D3& D3T)
    : NLPlate_HPG0G2Constraint(UV, Value, D1T, D2T),
      myG3Target(D3T)
{
  SetActiveOrder(3);
}

int NLPlate_HPG0G3Constraint::ActiveOrder() const
{
  if (myActiveOrder < 3)
    return myActiveOrder;
  else
    return 3;
}

const Plate_D3& NLPlate_HPG0G3Constraint::G3Target() const
{
  return myG3Target;
}

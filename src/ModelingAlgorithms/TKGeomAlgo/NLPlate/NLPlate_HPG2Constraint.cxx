#include <NLPlate_HPG2Constraint.hpp>
#include <Plate_D1.hpp>
#include <Plate_D2.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NLPlate_HPG2Constraint, NLPlate_HPG1Constraint)

NLPlate_HPG2Constraint::NLPlate_HPG2Constraint(const gp_XY&    UV,
                                               const Plate_D1& D1T,
                                               const Plate_D2& D2T)
    : NLPlate_HPG1Constraint(UV, D1T),
      myG2Target(D2T)
{
  SetActiveOrder(2);
}

int NLPlate_HPG2Constraint::ActiveOrder() const
{
  if (myActiveOrder < 2)
    return myActiveOrder;
  else
    return 2;
}

const Plate_D2& NLPlate_HPG2Constraint::G2Target() const
{
  return myG2Target;
}

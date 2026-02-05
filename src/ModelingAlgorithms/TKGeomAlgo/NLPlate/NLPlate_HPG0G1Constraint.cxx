#include <NLPlate_HPG0G1Constraint.hpp>
#include <Plate_D1.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NLPlate_HPG0G1Constraint, NLPlate_HPG0Constraint)

NLPlate_HPG0G1Constraint::NLPlate_HPG0G1Constraint(const gp_XY&    UV,
                                                   const gp_XYZ&   Value,
                                                   const Plate_D1& D1T)
    : NLPlate_HPG0Constraint(UV, Value),
      myG1Target(D1T)
{
  SetActiveOrder(1);
  myOrientation = 0;
}

void NLPlate_HPG0G1Constraint::SetOrientation(const int Orient)
{
  myOrientation = Orient;
}

int NLPlate_HPG0G1Constraint::ActiveOrder() const
{
  if (myActiveOrder < 1)
    return myActiveOrder;
  else
    return 1;
}

int NLPlate_HPG0G1Constraint::Orientation()
{
  return myOrientation;
}

const Plate_D1& NLPlate_HPG0G1Constraint::G1Target() const
{
  return myG1Target;
}

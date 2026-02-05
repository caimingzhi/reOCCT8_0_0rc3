#include <NLPlate_HPG1Constraint.hpp>
#include <Plate_D1.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NLPlate_HPG1Constraint, NLPlate_HGPPConstraint)

NLPlate_HPG1Constraint::NLPlate_HPG1Constraint(const gp_XY& UV, const Plate_D1& D1T)
    : myG1Target(D1T)
{
  SetUV(UV);
  SetActiveOrder(1);
  IncrementalLoadingAllowed = false;
  myOrientation             = 0;
}

void NLPlate_HPG1Constraint::SetIncrementalLoadAllowed(const bool ILA)
{
  IncrementalLoadingAllowed = ILA;
}

void NLPlate_HPG1Constraint::SetOrientation(const int Orient)
{
  myOrientation = Orient;
}

bool NLPlate_HPG1Constraint::IncrementalLoadAllowed() const
{
  return IncrementalLoadingAllowed;
}

int NLPlate_HPG1Constraint::ActiveOrder() const
{
  if (myActiveOrder < 1)
    return myActiveOrder;
  else
    return 1;
}

bool NLPlate_HPG1Constraint::IsG0() const
{
  return false;
}

int NLPlate_HPG1Constraint::Orientation()
{
  return myOrientation;
}

const Plate_D1& NLPlate_HPG1Constraint::G1Target() const
{
  return myG1Target;
}

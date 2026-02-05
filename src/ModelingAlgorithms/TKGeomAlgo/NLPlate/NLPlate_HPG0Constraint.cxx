#include <NLPlate_HPG0Constraint.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(NLPlate_HPG0Constraint, NLPlate_HGPPConstraint)

NLPlate_HPG0Constraint::NLPlate_HPG0Constraint(const gp_XY& UV, const gp_XYZ& Value)
    : myXYZTarget(Value)
{
  SetUV(UV);
  SetActiveOrder(0);
  UVIsFree                  = false;
  IncrementalLoadingAllowed = false;
}

void NLPlate_HPG0Constraint::SetUVFreeSliding(const bool UVFree)
{
  UVIsFree = UVFree;
}

void NLPlate_HPG0Constraint::SetIncrementalLoadAllowed(const bool ILA)
{
  IncrementalLoadingAllowed = ILA;
}

bool NLPlate_HPG0Constraint::UVFreeSliding() const
{
  return UVIsFree;
}

bool NLPlate_HPG0Constraint::IncrementalLoadAllowed() const
{
  return IncrementalLoadingAllowed;
}

int NLPlate_HPG0Constraint::ActiveOrder() const
{
  if (myActiveOrder < 0)
    return myActiveOrder;
  else
    return 0;
}

bool NLPlate_HPG0Constraint::IsG0() const
{
  return true;
}

const gp_XYZ& NLPlate_HPG0Constraint::G0Target() const
{
  return myXYZTarget;
}

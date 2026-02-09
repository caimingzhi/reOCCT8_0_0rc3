

#include <StepShape_BooleanOperand.hpp>
#include <StepShape_BooleanResult.hpp>
#include <StepShape_CsgPrimitive.hpp>
#include <StepShape_HalfSpaceSolid.hpp>
#include <StepShape_SolidModel.hpp>

StepShape_BooleanOperand::StepShape_BooleanOperand() = default;

occ::handle<StepShape_SolidModel> StepShape_BooleanOperand::SolidModel() const
{
  return theSolidModel;
}

void StepShape_BooleanOperand::SetSolidModel(const occ::handle<StepShape_SolidModel>& aSolidModel)
{
  theSolidModel = aSolidModel;
}

occ::handle<StepShape_HalfSpaceSolid> StepShape_BooleanOperand::HalfSpaceSolid() const
{
  return theHalfSpaceSolid;
}

void StepShape_BooleanOperand::SetHalfSpaceSolid(
  const occ::handle<StepShape_HalfSpaceSolid>& aHalfSpaceSolid)
{
  theHalfSpaceSolid = aHalfSpaceSolid;
}

StepShape_CsgPrimitive StepShape_BooleanOperand::CsgPrimitive() const
{
  return theCsgPrimitive;
}

void StepShape_BooleanOperand::SetCsgPrimitive(const StepShape_CsgPrimitive& aCsgPrimitive)
{
  theCsgPrimitive = aCsgPrimitive;
}

occ::handle<StepShape_BooleanResult> StepShape_BooleanOperand::BooleanResult() const
{
  return theBooleanResult;
}

void StepShape_BooleanOperand::SetBooleanResult(
  const occ::handle<StepShape_BooleanResult>& aBooleanResult)
{
  theBooleanResult = aBooleanResult;
}

void StepShape_BooleanOperand::SetTypeOfContent(const int aType)
{
  theTypeOfContent = aType;
}

int StepShape_BooleanOperand::TypeOfContent() const
{
  return theTypeOfContent;
}

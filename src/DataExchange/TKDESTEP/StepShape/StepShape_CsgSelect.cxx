

#include <StepShape_BooleanResult.hpp>
#include <StepShape_CsgPrimitive.hpp>
#include <StepShape_CsgSelect.hpp>

StepShape_CsgSelect::StepShape_CsgSelect() = default;

void StepShape_CsgSelect::SetTypeOfContent(const int aType)
{
  theTypeOfContent = aType;
}

int StepShape_CsgSelect::TypeOfContent() const
{
  return theTypeOfContent;
}

occ::handle<StepShape_BooleanResult> StepShape_CsgSelect::BooleanResult() const
{
  return theBooleanResult;
}

void StepShape_CsgSelect::SetBooleanResult(
  const occ::handle<StepShape_BooleanResult>& aBooleanResult)
{
  theBooleanResult = aBooleanResult;
  theTypeOfContent = 1;
}

StepShape_CsgPrimitive StepShape_CsgSelect::CsgPrimitive() const
{
  return theCsgPrimitive;
}

void StepShape_CsgSelect::SetCsgPrimitive(const StepShape_CsgPrimitive& aCsgPrimitive)
{
  theCsgPrimitive  = aCsgPrimitive;
  theTypeOfContent = 2;
}

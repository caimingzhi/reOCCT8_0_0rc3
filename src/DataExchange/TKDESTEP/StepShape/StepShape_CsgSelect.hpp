#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepShape_CsgPrimitive.hpp>
#include <Standard_Integer.hpp>
class StepShape_BooleanResult;

class StepShape_CsgSelect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_CsgSelect();

  Standard_EXPORT void SetTypeOfContent(const int aTypeOfContent);

  Standard_EXPORT int TypeOfContent() const;

  Standard_EXPORT occ::handle<StepShape_BooleanResult> BooleanResult() const;

  Standard_EXPORT void SetBooleanResult(const occ::handle<StepShape_BooleanResult>& aBooleanResult);

  Standard_EXPORT StepShape_CsgPrimitive CsgPrimitive() const;

  Standard_EXPORT void SetCsgPrimitive(const StepShape_CsgPrimitive& aCsgPrimitive);

private:
  occ::handle<StepShape_BooleanResult> theBooleanResult;
  StepShape_CsgPrimitive               theCsgPrimitive;
  int                                  theTypeOfContent;
};

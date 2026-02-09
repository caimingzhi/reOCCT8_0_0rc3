#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepShape_CsgPrimitive.hpp>
#include <Standard_Integer.hpp>
class StepShape_SolidModel;
class StepShape_HalfSpaceSolid;
class StepShape_BooleanResult;

class StepShape_BooleanOperand
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_BooleanOperand();

  Standard_EXPORT void SetTypeOfContent(const int aTypeOfContent);

  Standard_EXPORT int TypeOfContent() const;

  Standard_EXPORT occ::handle<StepShape_SolidModel> SolidModel() const;

  Standard_EXPORT void SetSolidModel(const occ::handle<StepShape_SolidModel>& aSolidModel);

  Standard_EXPORT occ::handle<StepShape_HalfSpaceSolid> HalfSpaceSolid() const;

  Standard_EXPORT void SetHalfSpaceSolid(
    const occ::handle<StepShape_HalfSpaceSolid>& aHalfSpaceSolid);

  Standard_EXPORT StepShape_CsgPrimitive CsgPrimitive() const;

  Standard_EXPORT void SetCsgPrimitive(const StepShape_CsgPrimitive& aCsgPrimitive);

  Standard_EXPORT occ::handle<StepShape_BooleanResult> BooleanResult() const;

  Standard_EXPORT void SetBooleanResult(const occ::handle<StepShape_BooleanResult>& aBooleanResult);

private:
  occ::handle<StepShape_SolidModel>     theSolidModel;
  occ::handle<StepShape_HalfSpaceSolid> theHalfSpaceSolid;
  StepShape_CsgPrimitive                theCsgPrimitive;
  occ::handle<StepShape_BooleanResult>  theBooleanResult;
  int                                   theTypeOfContent;
};

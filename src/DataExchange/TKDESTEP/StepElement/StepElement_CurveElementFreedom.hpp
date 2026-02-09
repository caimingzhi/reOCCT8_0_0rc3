#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

enum StepElement_EnumeratedCurveElementFreedom
{
  StepElement_XTranslation,
  StepElement_YTranslation,
  StepElement_ZTranslation,
  StepElement_XRotation,
  StepElement_YRotation,
  StepElement_ZRotation,
  StepElement_Warp,
  StepElement_None
};

class Standard_Transient;
class StepData_SelectMember;
class TCollection_HAsciiString;

class StepElement_CurveElementFreedom : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepElement_CurveElementFreedom();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  Standard_EXPORT void SetEnumeratedCurveElementFreedom(
    const StepElement_EnumeratedCurveElementFreedom aVal);

  Standard_EXPORT StepElement_EnumeratedCurveElementFreedom EnumeratedCurveElementFreedom() const;

  Standard_EXPORT void SetApplicationDefinedDegreeOfFreedom(
    const occ::handle<TCollection_HAsciiString>& aVal);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ApplicationDefinedDegreeOfFreedom() const;
};

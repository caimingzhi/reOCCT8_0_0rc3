#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

enum StepFEA_EnumeratedDegreeOfFreedom
{
  StepFEA_XTranslation,
  StepFEA_YTranslation,
  StepFEA_ZTranslation,
  StepFEA_XRotation,
  StepFEA_YRotation,
  StepFEA_ZRotation,
  StepFEA_Warp
};

class Standard_Transient;
class StepData_SelectMember;
class TCollection_HAsciiString;

class StepFEA_DegreeOfFreedom : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepFEA_DegreeOfFreedom();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  Standard_EXPORT void SetEnumeratedDegreeOfFreedom(const StepFEA_EnumeratedDegreeOfFreedom aVal);

  Standard_EXPORT StepFEA_EnumeratedDegreeOfFreedom EnumeratedDegreeOfFreedom() const;

  Standard_EXPORT void SetApplicationDefinedDegreeOfFreedom(
    const occ::handle<TCollection_HAsciiString>& aVal);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ApplicationDefinedDegreeOfFreedom() const;
};

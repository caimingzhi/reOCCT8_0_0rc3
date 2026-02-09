#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <StepDimTol_DatumReferenceModifierWithValue.hpp>
#include <StepDimTol_SimpleDatumReferenceModifierMember.hpp>

class Standard_Transient;

class StepDimTol_DatumReferenceModifier : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepDimTol_DatumReferenceModifier();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepDimTol_DatumReferenceModifierWithValue>
                  DatumReferenceModifierWithValue() const;

  Standard_EXPORT occ::handle<StepDimTol_SimpleDatumReferenceModifierMember>
                  SimpleDatumReferenceModifierMember() const;
};

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

  //! Returns a DatumReferenceModifier select type
  Standard_EXPORT StepDimTol_DatumReferenceModifier();

  //! Recognizes a DatumReferenceModifier Kind Entity that is :
  //! 1 -> DatumReferenceModifierWithValue
  //! 2 -> SimpleDatumReferenceModifierMember
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a DatumReferenceModifierWithValue (Null if another type)
  Standard_EXPORT occ::handle<StepDimTol_DatumReferenceModifierWithValue>
                  DatumReferenceModifierWithValue() const;

  //! returns Value as a SimpleDatumReferenceModifierMember (Null if another type)
  Standard_EXPORT occ::handle<StepDimTol_SimpleDatumReferenceModifierMember>
                  SimpleDatumReferenceModifierMember() const;
};

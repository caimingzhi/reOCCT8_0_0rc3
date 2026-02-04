#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepData_SelectMember;

class StepBasic_SizeSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a SizeSelect SelectType
  Standard_EXPORT StepBasic_SizeSelect();

  //! Recognizes a TrimmingSelect Kind Entity that is :
  //! 1 -> SizeMember
  //! 0 else (i.e. Real)
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns a SizeMember (POSITIVE_LENGTH_MEASURE) as preferred
  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  //! Recognizes a SelectMember as Real, named as PARAMETER_VALUE
  //! 1 -> PositiveLengthMeasure i.e. Real
  //! 0 else (i.e. Entity)
  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT void SetRealValue(const double aReal);

  //! returns Value as a Real (Null if another type)
  Standard_EXPORT double RealValue() const;
};


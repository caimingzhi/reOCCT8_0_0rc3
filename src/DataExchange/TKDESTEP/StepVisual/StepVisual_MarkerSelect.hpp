#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepData_SelectMember;
class StepVisual_MarkerMember;

class StepVisual_MarkerSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a MarkerSelect SelectType
  Standard_EXPORT StepVisual_MarkerSelect();

  //! Recognizes a MarkerSelect Kind Entity that is :
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns a new MarkerMember
  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  //! Returns 1 for a SelectMember enum, named MARKER_TYPE
  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& sm) const override;

  //! Gives access to the MarkerMember in order to get/set its value
  Standard_EXPORT occ::handle<StepVisual_MarkerMember> MarkerMember() const;
};


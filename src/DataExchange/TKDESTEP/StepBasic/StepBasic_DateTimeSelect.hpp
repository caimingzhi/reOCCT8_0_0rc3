#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_Date;
class StepBasic_LocalTime;
class StepBasic_DateAndTime;

class StepBasic_DateTimeSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a DateTimeSelect SelectType
  Standard_EXPORT StepBasic_DateTimeSelect();

  //! Recognizes a DateTimeSelect Kind Entity that is :
  //! 1 -> Date
  //! 2 -> LocalTime
  //! 3 -> DateAndTime
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Date (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_Date> Date() const;

  //! returns Value as a LocalTime (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_LocalTime> LocalTime() const;

  //! returns Value as a DateAndTime (Null if another type)
  Standard_EXPORT occ::handle<StepBasic_DateAndTime> DateAndTime() const;
};


#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Date;
class StepBasic_LocalTime;

class StepBasic_DateAndTime : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_DateAndTime();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Date>&      aDateComponent,
                            const occ::handle<StepBasic_LocalTime>& aTimeComponent);

  Standard_EXPORT void SetDateComponent(const occ::handle<StepBasic_Date>& aDateComponent);

  Standard_EXPORT occ::handle<StepBasic_Date> DateComponent() const;

  Standard_EXPORT void SetTimeComponent(const occ::handle<StepBasic_LocalTime>& aTimeComponent);

  Standard_EXPORT occ::handle<StepBasic_LocalTime> TimeComponent() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_DateAndTime, Standard_Transient)

private:
  occ::handle<StepBasic_Date>      dateComponent;
  occ::handle<StepBasic_LocalTime> timeComponent;
};

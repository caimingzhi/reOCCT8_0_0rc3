#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepBasic_Date.hpp>

class StepBasic_OrdinalDate : public StepBasic_Date
{

public:
  //! Returns a OrdinalDate
  Standard_EXPORT StepBasic_OrdinalDate();

  Standard_EXPORT void Init(const int aYearComponent, const int aDayComponent);

  Standard_EXPORT void SetDayComponent(const int aDayComponent);

  Standard_EXPORT int DayComponent() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_OrdinalDate, StepBasic_Date)

private:
  int dayComponent;
};


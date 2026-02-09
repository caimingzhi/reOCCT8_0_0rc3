#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

class StepBasic_Date : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_Date();

  Standard_EXPORT void Init(const int aYearComponent);

  Standard_EXPORT void SetYearComponent(const int aYearComponent);

  Standard_EXPORT int YearComponent() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_Date, Standard_Transient)

private:
  int yearComponent;
};

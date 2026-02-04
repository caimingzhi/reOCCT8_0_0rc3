#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

//! Added for Dimensional Tolerances
class StepShape_PrecisionQualifier : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_PrecisionQualifier();

  Standard_EXPORT void Init(const int precision_value);

  Standard_EXPORT int PrecisionValue() const;

  Standard_EXPORT void SetPrecisionValue(const int precision_value);

  DEFINE_STANDARD_RTTIEXT(StepShape_PrecisionQualifier, Standard_Transient)

private:
  int thePrecisionValue;
};


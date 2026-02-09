#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

class StepShape_ToleranceValue : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_ToleranceValue();

  Standard_EXPORT void Init(const occ::handle<Standard_Transient>& lower_bound,
                            const occ::handle<Standard_Transient>& upper_bound);

  Standard_EXPORT occ::handle<Standard_Transient> LowerBound() const;

  Standard_EXPORT void SetLowerBound(const occ::handle<Standard_Transient>& lower_bound);

  Standard_EXPORT occ::handle<Standard_Transient> UpperBound() const;

  Standard_EXPORT void SetUpperBound(const occ::handle<Standard_Transient>& upper_bound);

  DEFINE_STANDARD_RTTIEXT(StepShape_ToleranceValue, Standard_Transient)

private:
  occ::handle<Standard_Transient> theLowerBound;
  occ::handle<Standard_Transient> theUpperBound;
};

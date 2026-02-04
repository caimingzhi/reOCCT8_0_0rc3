#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Unit.hpp>
#include <Standard_Transient.hpp>
class StepBasic_MeasureValueMember;

class StepBasic_MeasureWithUnit : public Standard_Transient
{

public:
  //! Returns a MeasureWithUnit
  Standard_EXPORT StepBasic_MeasureWithUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_MeasureValueMember>& aValueComponent,
                            const StepBasic_Unit&                            aUnitComponent);

  Standard_EXPORT void SetValueComponent(const double aValueComponent);

  Standard_EXPORT double ValueComponent() const;

  Standard_EXPORT occ::handle<StepBasic_MeasureValueMember> ValueComponentMember() const;

  Standard_EXPORT void SetValueComponentMember(
    const occ::handle<StepBasic_MeasureValueMember>& val);

  Standard_EXPORT void SetUnitComponent(const StepBasic_Unit& aUnitComponent);

  Standard_EXPORT StepBasic_Unit UnitComponent() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_MeasureWithUnit, Standard_Transient)

private:
  occ::handle<StepBasic_MeasureValueMember> valueComponent;
  StepBasic_Unit                            unitComponent;
};


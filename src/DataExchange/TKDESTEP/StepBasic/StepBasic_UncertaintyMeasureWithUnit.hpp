#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_MeasureWithUnit.hpp>
class TCollection_HAsciiString;
class StepBasic_MeasureValueMember;
class StepBasic_Unit;

class StepBasic_UncertaintyMeasureWithUnit : public StepBasic_MeasureWithUnit
{

public:
  //! Returns a UncertaintyMeasureWithUnit
  Standard_EXPORT StepBasic_UncertaintyMeasureWithUnit();

  Standard_EXPORT void Init(const occ::handle<StepBasic_MeasureValueMember>& aValueComponent,
                            const StepBasic_Unit&                            aUnitComponent,
                            const occ::handle<TCollection_HAsciiString>&     aName,
                            const occ::handle<TCollection_HAsciiString>&     aDescription);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_UncertaintyMeasureWithUnit, StepBasic_MeasureWithUnit)

private:
  occ::handle<TCollection_HAsciiString> name;
  occ::handle<TCollection_HAsciiString> description;
};


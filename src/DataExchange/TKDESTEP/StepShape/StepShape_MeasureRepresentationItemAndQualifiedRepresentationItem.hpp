#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ValueQualifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <Standard_Integer.hpp>
class StepBasic_MeasureWithUnit;
class TCollection_HAsciiString;
class StepBasic_MeasureValueMember;
class StepBasic_Unit;
class StepShape_ValueQualifier;

class StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem
    : public StepRepr_RepresentationItem
{

public:
  Standard_EXPORT StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                      aName,
    const occ::handle<StepBasic_MeasureValueMember>&                  aValueComponent,
    const StepBasic_Unit&                                             aUnitComponent,
    const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers);

  Standard_EXPORT void SetMeasure(const occ::handle<StepBasic_MeasureWithUnit>& Measure);

  Standard_EXPORT occ::handle<StepBasic_MeasureWithUnit> Measure() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> Qualifiers() const;

  Standard_EXPORT int NbQualifiers() const;

  Standard_EXPORT void SetQualifiers(
    const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers);

  Standard_EXPORT StepShape_ValueQualifier QualifiersValue(const int num) const;

  Standard_EXPORT void SetQualifiersValue(const int                       num,
                                          const StepShape_ValueQualifier& aqualifier);

  DEFINE_STANDARD_RTTIEXT(StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem,
                          StepRepr_RepresentationItem)

private:
  occ::handle<StepBasic_MeasureWithUnit>                     myMeasure;
  occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> theQualifiers;
};

#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_ReprItemAndMeasureWithUnit.hpp>
class StepShape_QualifiedRepresentationItem;

//! Base class for complex types (MEASURE_REPRESENTATION_ITEM, MEASURE_WITH_UNIT,
//! QUALIFIED_REPRESENTATION_ITEM REPRESENTATION_ITEM,
//! LENGTH_MEASURE_WITH_UNIT/PLANE_ANGLE_MEASURE_WITH_UNIT).
class StepRepr_ReprItemAndMeasureWithUnitAndQRI : public StepRepr_ReprItemAndMeasureWithUnit
{

public:
  Standard_EXPORT StepRepr_ReprItemAndMeasureWithUnitAndQRI();

  Standard_EXPORT void Init(const occ::handle<StepBasic_MeasureWithUnit>&             aMWU,
                            const occ::handle<StepRepr_RepresentationItem>&           aRI,
                            const occ::handle<StepShape_QualifiedRepresentationItem>& aQRI);

  Standard_EXPORT void SetQualifiedRepresentationItem(
    const occ::handle<StepShape_QualifiedRepresentationItem>& aQRI);

  Standard_EXPORT occ::handle<StepShape_QualifiedRepresentationItem>
                  GetQualifiedRepresentationItem() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_ReprItemAndMeasureWithUnitAndQRI,
                          StepRepr_ReprItemAndMeasureWithUnit)

private:
  occ::handle<StepShape_QualifiedRepresentationItem> myQualifiedRepresentationItem;
};

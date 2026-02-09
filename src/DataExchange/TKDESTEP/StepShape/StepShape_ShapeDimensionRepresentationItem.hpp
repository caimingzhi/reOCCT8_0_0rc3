#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepRepr_CompoundRepresentationItem;
class StepRepr_DescriptiveRepresentationItem;
class StepRepr_MeasureRepresentationItem;
class StepGeom_Placement;

class StepShape_ShapeDimensionRepresentationItem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_ShapeDimensionRepresentationItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepRepr_CompoundRepresentationItem> CompoundRepresentationItem()
    const;

  Standard_EXPORT occ::handle<StepRepr_DescriptiveRepresentationItem>
                  DescriptiveRepresentationItem() const;

  Standard_EXPORT occ::handle<StepRepr_MeasureRepresentationItem> MeasureRepresentationItem() const;

  Standard_EXPORT occ::handle<StepGeom_Placement> Placement() const;
};

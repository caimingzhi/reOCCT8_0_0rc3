#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepGeom_GeometricRepresentationItem;
class StepRepr_MappedItem;
class StepRepr_Representation;
class StepShape_TopologicalRepresentationItem;

class StepVisual_StyledItemTarget : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_StyledItemTarget();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepGeom_GeometricRepresentationItem> GeometricRepresentationItem()
    const;

  Standard_EXPORT occ::handle<StepRepr_MappedItem> MappedItem() const;

  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  Standard_EXPORT occ::handle<StepShape_TopologicalRepresentationItem>
                  TopologicalRepresentationItem() const;
};

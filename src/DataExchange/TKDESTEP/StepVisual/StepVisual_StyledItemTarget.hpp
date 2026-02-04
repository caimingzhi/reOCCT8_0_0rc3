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

  //! Returns a StyledItemTarget select type
  Standard_EXPORT StepVisual_StyledItemTarget();

  //! Recognizes a StyledItemTarget Kind Entity that is :
  //! 1 -> GeometricRepresentationItem
  //! 2 -> MappedItem
  //! 3 -> Representation
  //! 4 -> TopologicalRepresentationItem
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a GeometricRepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_GeometricRepresentationItem> GeometricRepresentationItem()
    const;

  //! returns Value as a MappedItem (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_MappedItem> MappedItem() const;

  //! returns Value as a Representation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_Representation> Representation() const;

  //! returns Value as a TopologicalRepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepShape_TopologicalRepresentationItem>
                  TopologicalRepresentationItem() const;
};

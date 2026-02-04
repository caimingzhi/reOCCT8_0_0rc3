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

  //! Returns a ShapeDimensionRepresentationItem select type
  Standard_EXPORT StepShape_ShapeDimensionRepresentationItem();

  //! Recognizes a ShapeDimensionRepresentationItem Kind Entity that is :
  //! 1 -> CompoundRepresentationItem
  //! 2 -> DescriptiveRepresentationItem
  //! 3 -> MeasureRepresentationItem
  //! 4 -> Placement
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a CompoundRepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_CompoundRepresentationItem> CompoundRepresentationItem()
    const;

  //! returns Value as a DescriptiveRepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_DescriptiveRepresentationItem>
                  DescriptiveRepresentationItem() const;

  //! returns Value as a MeasureRepresentationItem (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_MeasureRepresentationItem> MeasureRepresentationItem() const;

  //! returns Value as a Placement (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Placement> Placement() const;
};

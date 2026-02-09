#include <StepShape_ShapeDimensionRepresentation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_ShapeDimensionRepresentation, StepShape_ShapeRepresentation)

StepShape_ShapeDimensionRepresentation::StepShape_ShapeDimensionRepresentation() = default;

void StepShape_ShapeDimensionRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>&                                      theName,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& theItems,
  const occ::handle<StepRepr_RepresentationContext>& theContextOfItems)
{
  StepRepr_Representation::Init(theName, theItems, theContextOfItems);
}

void StepShape_ShapeDimensionRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>&                                        theName,
  const occ::handle<NCollection_HArray1<StepShape_ShapeDimensionRepresentationItem>>& theItems,
  const occ::handle<StepRepr_RepresentationContext>& theContextOfItems)
{
  StepRepr_Representation::Init(theName, nullptr, theContextOfItems);
  itemsAP242 = theItems;
}

void StepShape_ShapeDimensionRepresentation::SetItemsAP242(
  const occ::handle<NCollection_HArray1<StepShape_ShapeDimensionRepresentationItem>>& theItems)
{
  itemsAP242 = theItems;
}

occ::handle<NCollection_HArray1<StepShape_ShapeDimensionRepresentationItem>>
  StepShape_ShapeDimensionRepresentation::ItemsAP242() const
{
  return itemsAP242;
}

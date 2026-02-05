#pragma once

#include <Standard.hpp>

#include <StepShape_ShapeDimensionRepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_ShapeRepresentation.hpp>

//! Representation of STEP entity ShapeDimensionRepresentation
class StepShape_ShapeDimensionRepresentation : public StepShape_ShapeRepresentation
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_ShapeDimensionRepresentation();

  //! Initialize all fields AP214
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                      theName,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& theItems,
    const occ::handle<StepRepr_RepresentationContext>& theContextOfItems);

  //! Initialize all fields AP242
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                        theName,
    const occ::handle<NCollection_HArray1<StepShape_ShapeDimensionRepresentationItem>>& theItems,
    const occ::handle<StepRepr_RepresentationContext>& theContextOfItems);

  Standard_EXPORT void SetItemsAP242(
    const occ::handle<NCollection_HArray1<StepShape_ShapeDimensionRepresentationItem>>& theItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepShape_ShapeDimensionRepresentationItem>>
                  ItemsAP242() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_ShapeDimensionRepresentation, StepShape_ShapeRepresentation)
private:
  occ::handle<NCollection_HArray1<StepShape_ShapeDimensionRepresentationItem>> itemsAP242;
};

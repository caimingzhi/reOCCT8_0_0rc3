#include <StepRepr_CharacterizedRepresentation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_CharacterizedRepresentation, StepRepr_Representation)

StepRepr_CharacterizedRepresentation::StepRepr_CharacterizedRepresentation() = default;

void StepRepr_CharacterizedRepresentation::Init(
  const occ::handle<TCollection_HAsciiString>&                                      theName,
  const occ::handle<TCollection_HAsciiString>&                                      theDescription,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& theItems,
  const occ::handle<StepRepr_RepresentationContext>& theContextOfItems)
{
  myDescription = theDescription;
  StepRepr_Representation::Init(theName, theItems, theContextOfItems);
}

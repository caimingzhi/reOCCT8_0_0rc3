#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>
class TCollection_HAsciiString;
class StepRepr_RepresentationContext;

class StepRepr_CharacterizedRepresentation : public StepRepr_Representation
{

public:
  Standard_EXPORT StepRepr_CharacterizedRepresentation();

  //! Returns a CharacterizedRepresentation
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theName,
    const occ::handle<TCollection_HAsciiString>& theDescription,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& theItems,
    const occ::handle<StepRepr_RepresentationContext>& theContextOfItems);

  void SetDescription(const occ::handle<TCollection_HAsciiString>& theDescription)
  {
    myDescription = theDescription;
  }

  occ::handle<TCollection_HAsciiString> Description() const { return myDescription; }

  DEFINE_STANDARD_RTTIEXT(StepRepr_CharacterizedRepresentation, StepRepr_Representation)

private:
  occ::handle<TCollection_HAsciiString> myDescription;
};

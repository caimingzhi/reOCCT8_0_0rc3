

#include <StepVisual_CompositeText.hpp>
#include <StepVisual_TextOrCharacter.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CompositeText, StepGeom_GeometricRepresentationItem)

StepVisual_CompositeText::StepVisual_CompositeText() = default;

void StepVisual_CompositeText::Init(
  const occ::handle<TCollection_HAsciiString>&                        aName,
  const occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>>& aCollectedText)
{

  collectedText = aCollectedText;

  StepRepr_RepresentationItem::Init(aName);
}

void StepVisual_CompositeText::SetCollectedText(
  const occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>>& aCollectedText)
{
  collectedText = aCollectedText;
}

occ::handle<NCollection_HArray1<StepVisual_TextOrCharacter>> StepVisual_CompositeText::
  CollectedText() const
{
  return collectedText;
}

StepVisual_TextOrCharacter StepVisual_CompositeText::CollectedTextValue(const int num) const
{
  return collectedText->Value(num);
}

int StepVisual_CompositeText::NbCollectedText() const
{
  return collectedText->Length();
}
